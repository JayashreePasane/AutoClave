/*
 * Application.c
 *
 *  Created on: Jan 15, 2017
 *      Author: 
 */
#include "Cpu.h"
#include "Status.h"
#include "Global_Config.h"
#include "Display_HL.h"
#include "Digital_IO.h"
#include "ADC_Handler.h"
#include "Keyhandler.h"
#include "Application.h"
#include "Timer.h"
#include <stdio.h>

/*Open airvent solenoid*/
#define AIRVENT_SOL_ON	Digital_IO_Set((uint32_t)DIGITAL_IO_ID_AIRVENT_SOL, DIGITAL_IO_LEVEL_HIGH)
#define AIRVENT_SOL_OFF	Digital_IO_Set((uint32_t)DIGITAL_IO_ID_AIRVENT_SOL, DIGITAL_IO_LEVEL_LOW)

/*Dry solenoid*/
#define DRYSOL_ON Digital_IO_Set((uint32_t)DIGITAL_IO_ID_DRY_SOL, DIGITAL_IO_LEVEL_HIGH)
#define DRYSOL_OFF Digital_IO_Set((uint32_t)DIGITAL_IO_ID_DRY_SOL, DIGITAL_IO_LEVEL_LOW)

/*Stop buzzer*/
#define BUZZ_ON Digital_IO_Set((uint32_t)DIGITAL_IO_ID_BUZ, DIGITAL_IO_LEVEL_HIGH)
#define BUZZ_OFF Digital_IO_Set((uint32_t)DIGITAL_IO_ID_BUZ, DIGITAL_IO_LEVEL_LOW)

/*Band heater*/
#define BHEATER_ON Digital_IO_Set((uint32_t)DIGITAL_IO_ID_BAND, DIGITAL_IO_LEVEL_HIGH)
#define BHEATER_OFF Digital_IO_Set((uint32_t)DIGITAL_IO_ID_BAND, DIGITAL_IO_LEVEL_LOW)

/*Door closed*/
#define DOOR_STATE Digital_IO_Get((uint32_t)DIGITAL_IO_ID_DOOR)

typedef enum
{
	APP_IDLE,
	APP_WAIT_FOR_START,
	APP_START,
	APP_DISP_DEL,
	APP_PURGE,
	APP_PRE_HEAT1,
	APP_PRE_HEAT2,
	APP_PRE_HEAT_COOL,
	APP_PRE_STER,
	APP_STERILIZATION,
	APP_DRY,
	APP_FINISH,
	APP_STOP,
	APP_ERR,
	APP_INVALID	
}APP_State_en;

typedef enum
{
	APP_MODE_INVALID,
	APP_MODE_121_FAST,
	APP_MODE_121_WRAP,
	APP_MODE_134_FAST,
	APP_MODE_134_WRAP,
	APP_MODES
}APP_Mode_en;

typedef enum
{
	ERROR_ID_INVALID,
	ERROR_ID_1,			/*Pressure out of range during sterilization*/
	ERROR_ID_2,			/*Temperature out of range during sterilization*/
	ERROR_ID_3,			/*Previous Cycle was stopped in middle*/
	ERROR_ID_4,			/*Temperature Out of Range..(1 - 174)*/
	ERROR_ID_5,			/*Door Opened during Cycle Run*/
	ERROR_ID_6,			/*Time error to reach 80degrees in chamber*/
	ERROR_ID_7,			/*pressure couldn't reach .5bar in time during purge*/
	ERROR_ID_8,			/*Pre sterilization couldnt reach respective pressures in time*/
	ERROR_ID_9,			/*Writing On RAM Error*/
	ERROR_ID_10,		/*Reading From RAM Error*/
	ERROR_ID_Count
	
}ERROR_ID_en;

static void RecallMode(void);
static void DisplayMode(void);
static void UpdateMode(APP_Mode_en mode);
static void DisplayCycleCount(void);
static void Handle_Errors(void);
static void LastStepModulation(uint32_t temp, uint32_t pres);
void Buzzer_On(void);
void Buzzer_Off(void);
void Heater_On(void);
void Heater_Off(void);

APP_State_en APP_State = APP_IDLE, APP_prev_state = APP_MODE_INVALID;
APP_Mode_en APP_Mode = APP_MODE_INVALID;
volatile ERROR_ID_en Error_ID = ERROR_ID_INVALID;
static uint32_t Disp_del_count = 0;
/*Mode specific target pressure, temperature, sterilization time and dry cycle time*/
static uint32_t Target_P; Target_T, Ster_Time, Dry_Time;
void Application(void)
{
	char disp_arr[17];
	uint32_t temperature, pressure;
	/*Get temperature and pressure*/
	temperature = Temperature_Get();
	pressure = Pressure_Get();
	/*Update Line1 */
	sprintf(disp_arr, "Tmp:%.3d"".%.1d Ps:%.1d"".%.1d", (int)(temperature/100), (int)((temperature%100)/10), 
			(int)(pressure/10), (int)(pressure % 10));
	Display_String(disp_arr, 1);
	/*Application state machine*/
	switch(APP_Mode)
	{
	case APP_MODE_INVALID:
		/*Consider as the beginning*/
		/*Read previously stored mode here*/
		RecallMode();
		
		break;
	case APP_MODE_121_FAST:
		
		break;
	case APP_MODE_121_WRAP:
		break;
	case APP_MODE_134_FAST:
		break;
	case APP_MODE_134_WRAP:
		break;
	default:
		APP_State = APP_MODE_INVALID;
		break;
	}
	
	switch(APP_State)
	{
	case APP_IDLE:
		AIRVENT_SOL_ON;
		pressure = Pressure_Get();
		/*Open airvent solenoid if pressure high*/
		if(pressure <= 1)
		{
			if(DOOR_STATE == DIGITAL_IO_LEVEL_LOW)
			{
				Display_String("Open the door   ", 2);
				
			}
			else
			{
				APP_State = APP_WAIT_FOR_START;
				RecallMode();
			}
		}
		APP_prev_state = APP_IDLE;
		break;
	case APP_WAIT_FOR_START:
		/*If door is opened get ready to purge*/
		/*Look for key presses*/
		DisplayMode();
		if(Keyhandler_Get(KEY_START_STOP))
		{
			APP_State = APP_START;
		}
		else if(Keyhandler_Get(KEY_MODE))
		{
			APP_Mode = (APP_Mode_en)(((uint32_t)APP_Mode + 1) % ((uint32_t)APP_MODES));
			DisplayMode();
		}
		else if(Keyhandler_Get(KEY_SETTINGS))
		{
			/*Read flash and display cycle count*/
			DisplayCycleCount();
			Disp_del_count = CYCLE_CNT_DISP_DELAY;
			APP_State = APP_DISP_DEL;
		}
		APP_prev_state = APP_WAIT_FOR_START;
		break;
	case APP_START:
		if(DOOR_STATE == DIGITAL_IO_LEVEL_LOW)
		{
			APP_State = APP_PURGE;
			DisplayMode();
		}
		else
		{
			Display_String("Close the door  ",2);
		}
		APP_prev_state = APP_START;
		break;
	case APP_DISP_DEL:
		if(Disp_del_count > 0)
		{
			Disp_del_count--;
		}
		else
		{
			APP_State = APP_prev_state;
		}
		break;
	case APP_PURGE:
		/*Wait till door is closed*/
		if(DOOR_STATE == DIGITAL_IO_LEVEL_LOW)
		{
			DisplayMode();
			if(APP_prev_state != APP_PURGE)
			{
				Buzzer_On();
			}
			
			DRYSOL_OFF;
			BHEATER_ON;
			/*Continue till temperature reaches 80degC*/
			/*after reaching threshold close air vent*/
			if(temperature > 8000)
			{
				AIRVENT_SOL_OFF;
				/*Start purge*/
				APP_State = APP_PRE_HEAT1;
			}
			else
			{
				AIRVENT_SOL_ON;
			}

		}
		else
		{
			Error_ID = ERROR_ID_5;
		}
		APP_prev_state = APP_PURGE;
		break;
		
	case APP_PRE_HEAT1:
		/*Heater on till pressure reaches 1 bar*/
		AIRVENT_SOL_OFF;
		DRYSOL_OFF;
		BHEATER_ON;
		BUZZ_OFF;
		DisplayMode();
		
		if(pressure >= 10)
		{
			BHEATER_OFF;
			AIRVENT_SOL_ON;
			APP_State = APP_PRE_HEAT_COOL;
		}

		APP_prev_state = APP_PRE_HEAT1;
		break;
	case APP_PRE_HEAT_COOL:
		/*Wait till pressure comes down to 0.2bar*/
		DisplayMode();
		if(pressure <= 2)
		{
			if(APP_prev_state == APP_PRE_HEAT1)
			{
				APP_State = APP_PRE_HEAT2;
			}
			else if(APP_prev_state == APP_PRE_HEAT2)
			{
				APP_State = APP_PRE_STER;
			}
			else
			{
				APP_State = APP_STOP;
			}
		}
		break;
	case APP_PRE_HEAT2:
		/*Heater on till pressure reaches 1 bar*/
		AIRVENT_SOL_OFF;
		DRYSOL_OFF;
		BHEATER_ON;
		DisplayMode();
		
		if(pressure >= 10)
		{
			BHEATER_OFF;
			AIRVENT_SOL_ON;
			APP_State = APP_PRE_HEAT_COOL;
		}
		APP_prev_state = APP_PRE_HEAT2;
		break;
	case APP_PRE_STER:
		/*Wait till pressure reaches required level for selected mode
		 * 121 FAST/WRAP = 1.1
		 * 134 FAST/WRAP = 2.0
		 * */
		AIRVENT_SOL_OFF;
		DRYSOL_OFF;
		DisplayMode();
		LastStepModulation(temperature, pressure);
		switch(APP_Mode)
		{
		case APP_MODE_121_FAST:
		case APP_MODE_121_WRAP:
			if(pressure >= Target_P)
			{
				APP_State = APP_STERILIZATION;
			}
			break;
		case APP_MODE_134_FAST:
		case APP_MODE_134_WRAP:
			if(pressure >= Target_P)
			{
				APP_State = APP_STERILIZATION;
			}
			break;
		}
		APP_prev_state = APP_PRE_STER;
		break;
	case APP_STERILIZATION:
		DisplayMode();
		/*Start sterilization timer*/
		if(APP_prev_state != APP_STERILIZATION)
		{
			Timer_Start(0, (Ster_Time * 60 * 1000), NULL);
		}
		
		/*Monitor temperature and pressure*/
		LastStepModulation(temperature, pressure);
		
		/*Timeout check*/
		if(Timer_GetState(0) != TIMER_RUNNING)
		{
			APP_State = APP_DRY;
		}
		APP_prev_state = APP_STERILIZATION;
		break;
	case APP_DRY:
		DisplayMode();
		/*Start dry cycle timer*/
		if(APP_prev_state != APP_DRY)
		{
			BHEATER_OFF;
			DRYSOL_ON;
			Timer_Start(0, (Dry_Time * 60 * 1000), NULL);
		}
		
		/*Timeout check*/
		if(Timer_GetState(0) != TIMER_RUNNING)
		{
			APP_State = APP_FINISH;
		}
		APP_prev_state = APP_DRY;
		break;
	case APP_FINISH:
		DisplayMode();
		if(APP_prev_state != APP_FINISH)
		{
			Buzzer_On();
		}
		else
		{
			APP_State = APP_STOP;
		}
		APP_prev_state = APP_FINISH;
		break;
	case APP_STOP:
		AIRVENT_SOL_ON;
		BHEATER_OFF;
		DisplayMode();
		APP_prev_state = APP_STOP;
		break;
	case APP_ERR:
		if(APP_prev_state != APP_ERR)
		{
			Buzzer_On();
			sprintf(disp_arr, "Error_ID : %.4d ",Error_ID);
			Display_String(disp_arr, 2);
		}
		else
		{
			BUZZ_OFF;
		}
		
		/*Switch off, heater and turn on air vents*/
		BHEATER_OFF;
		AIRVENT_SOL_ON;
		DRYSOL_ON;
		
		APP_prev_state = APP_ERR;
		break;
	}

	Display_Refresh();
	Handle_Errors();
	if(Error_ID != ERROR_ID_INVALID)
	{
		APP_State = APP_ERR;
	}
	/*To stop the process*/
	if(Keyhandler_Get(KEY_START_STOP))
	{
		if(APP_prev_state >= APP_START)
		{
			APP_State = APP_IDLE;
		}
	}
}

static void Handle_Errors(void)
{
	uint32_t temperature, pressure;
	/*Get temperature and pressure*/
	temperature = Temperature_Get();
	pressure = Pressure_Get();
	/*Door opened*/
	switch(APP_State)
	{
	case APP_STERILIZATION:
		if(temperature > (Target_T + 500))
		{
			Error_ID = ERROR_ID_2;/*Temperature out of range*/
		}
		if(pressure > (Target_P + 5))
		{
			Error_ID = ERROR_ID_1;/*Pressure out of range*/
		}
	case APP_PURGE:
	case APP_PRE_HEAT1:
	case APP_PRE_HEAT2:
	case APP_PRE_STER:
	case APP_DRY:
		if(DOOR_STATE == DIGITAL_IO_LEVEL_HIGH)
		{
			Error_ID = ERROR_ID_5;
		}
		break;	
	default:
		break;
	}
}

static void UpdateMode(APP_Mode_en mode)
{
	switch(mode)
	{
	case APP_MODE_121_FAST:
		Display_String("121 FAST    STOP", 2);
		APP_Mode = mode;
		break;
	case APP_MODE_121_WRAP:
		Display_String("121 WRAP    STOP", 2);
		APP_Mode = mode;
		break;
	case APP_MODE_134_FAST:
		Display_String("134 FAST    STOP", 2);
		APP_Mode = mode;
		break;
	case APP_MODE_134_WRAP:
		Display_String("134 WRAP    STOP", 2);
		APP_Mode = mode;
		break;
	default:
		Display_String("121 FAST    STOP", 2);
		APP_Mode = APP_MODE_121_FAST;
		break;
	}
}

static void DisplayMode(void)
{
	char * str;
	char * mode_str;
	char disp_buff[17];
#if 1
	uint32_t val;
	char loc_buff[4];
#endif
	switch(APP_Mode)
	{
	case APP_MODE_121_FAST:
		str = DISP_MODE_121_FAST;
		break;
	case APP_MODE_121_WRAP:
		str = DISP_MODE_121_FAST;
		break;
	case APP_MODE_134_FAST:
		str = DISP_MODE_121_FAST;
		break;
	case APP_MODE_134_WRAP:
		str = DISP_MODE_121_FAST;
		break;
	default:
		break;
	}
	
	switch(APP_prev_state)
	{
	case APP_IDLE:
	case APP_STOP:
	case APP_WAIT_FOR_START:
	case APP_START:
#if 0
		val = Timer_Remaining(0) / (60*1000);
		sprintf(loc_buff, "%.4d",(int)val+1);
		mode_str = loc_buff;
#else
		mode_str = "STOP";
#endif
		break;
	case APP_PURGE:
		mode_str = "PURG";
		break;
	case APP_PRE_HEAT1:
		mode_str = "PRG1";
		break;
	case APP_PRE_HEAT2:
		mode_str = "PRG2";
		break;
	case APP_PRE_STER:
		mode_str = "PSTR";
		break;
	case APP_STERILIZATION:
		/*mode_str = "STER";*/
		val = Timer_Remaining(0) / (60*1000);
		sprintf(loc_buff, "%.4d",(int)val+1);
		mode_str = loc_buff;
		break;
	case APP_DRY:
		mode_str = "DRY ";
		break;
	default:
		mode_str = "    ";
		break;
	}
	
	sprintf(disp_buff, str, mode_str);
	Display_String(disp_buff, 2);
}

static void DisplayCycleCount(void)
{
	char buffer[17];
	uint32_t cycles = 0;
	switch(APP_Mode)
	{
	case APP_MODE_121_FAST:
		cycles = 1;
		break;
	case APP_MODE_121_WRAP:
		cycles = 1;
		break;
	case APP_MODE_134_FAST:
		cycles = 1;
		break;
	case APP_MODE_134_WRAP:
		cycles = 1;
		break;
	default:
		break;
	}
	sprintf(buffer, DISP_CYCLE_CNT, cycles);
	Display_String(buffer, 2);
}


static void RecallMode(void)
{
	//TODO: Add flash read call here
	APP_Mode = APP_MODE_121_FAST;
	
	switch(APP_Mode)
	{
	case APP_MODE_121_FAST:
		Display_String("121 FAST    STOP", 2);
		Target_P = 11;
		Target_T = 12100;
		Ster_Time = 18;/*in minutes*/
		Dry_Time = 5;
		break;
	case APP_MODE_121_WRAP:
		Display_String("121 WRAP    STOP", 2);
		Target_P = 11;
		Target_T = 12100;
		Ster_Time = 18;/*in minutes*/
		Dry_Time = 15;
		break;
	case APP_MODE_134_FAST:
		Display_String("134 FAST    STOP", 2);
		Target_P = 20;
		Target_T = 13400;
		Ster_Time = 6;/*in minutes*/
		Dry_Time = 5;
		break;
	case APP_MODE_134_WRAP:
		Display_String("134 WRAP    STOP", 2);
		Target_P = 20;
		Target_T = 13400;
		Ster_Time = 6;/*in minutes*/
		Dry_Time = 5;
		break;
	default:
		APP_Mode = APP_MODE_121_FAST;
		break;
	}
}

static void LastStepModulation(uint32_t temp, uint32_t pres)
{
	static uint32_t prev_temp = 0, prev_pres = 0;
	if(((pres < Target_P) && (temp < Target_T))&&((pres > (Target_P - 5)) || (temp > (Target_T - 100))))
	{
		{
			if((Digital_IO_Get((uint32_t)DIGITAL_IO_ID_BAND)) && (Timer_GetState(2) == TIMER_IDLE))
			{
				BHEATER_OFF;
				Timer_Start(2, 3000, Heater_On);
			}
			else if((!Digital_IO_Get((uint32_t)DIGITAL_IO_ID_BAND)) && (Timer_GetState(2) == TIMER_IDLE))
			{
				BHEATER_ON;
				Timer_Start(2, 1000, Heater_Off);
			}
		}
	}
	else if((pres <= (Target_P - 5)) && (temp <= (Target_T - 100)))
	{
		BHEATER_ON;
	}
	else
	{
		BHEATER_OFF;
	}
	prev_temp = temp;
	prev_pres = pres;
}

void Buzzer_On(void)
{
	Timer_Start(1, 1000, Buzzer_Off);
	BUZZ_ON;
}

void Buzzer_Off(void)
{
	BUZZ_OFF;
}

void Heater_On(void)
{
	BHEATER_ON;
}

void Heater_Off(void)
{
	BHEATER_OFF;
}
