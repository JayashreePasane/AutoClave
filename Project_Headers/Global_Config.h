/*
 * Global_Config.h
 *
 *  Created on: Dec 24, 2016
 *      Author: 
 */

#ifndef GLOBAL_CONFIG_H_
#define GLOBAL_CONFIG_H_

/*Digital IO configuration macros*/
typedef enum {
	DIGITAL_IO_ID_DOOR,
	DIGITAL_IO_ID_WTR_LL,
	DIGITAL_IO_ID_WTR_HL,
	DIGITAL_IO_ID_BAND,
	DIGITAL_IO_ID_BOILER,
	DIGITAL_IO_ID_XX1,
	DIGITAL_IO_ID_HT_PUMP,
	DIGITAL_IO_ID_DRY_SOL,
	DIGITAL_IO_ID_AIRVENT_SOL,
	DIGITAL_IO_ID_CW_SOL,
	DIGITAL_IO_ID_BUZ,
	DIGITAL_IO_COUNT
}DIGITAL_IO_ID_en;

#define PORT_CONFIG_MASK			0x777 /*Includes bitmasks for PCR: MUX,DSE,ODE,PFE,SRE,PE,PS*/
#define PORT_CONFIG_MUX_POS			0x08
#define PORT_CONFIG_MUX_MSK			(0x07 << PORT_CONFIG_MODE_POS)
#define PORT_CONFIG_MUX_GPIO		(0x01 << PORT_CONFIG_MUX_POS)
#define PORT_CONFIG_OPENDRAIN_POS	0x05
#define PORT_CONFIG_OPENDRAIN_MSK	(0x01 << PORT_CONFIG_OPENDRAIN_POS)
#define PORT_CONFIG_PULL_UP			0x03
#define PORT_CONFIG_PULL_DOWN		0x02
#define PORT_PCR_INPUT				0x0100
#define PORT_PCR_LK					0x8000
#define PORT_PCR_ANALOG				0
#define PORT_PCR_INT_PULL			0x03

/*Key handler configuration macros*/
#define KEYS_COUNT			4
#define KEY_DEBNCE_SAMPLES 	3

/*ADC handler configuration*/
#define ADC_SENSORS			4
#define ADC_SAMPLE_COUNT	5

/*Display port configuration*/
#define DISP_CTRL_CD		0 /*Command or data selection pin*/
#define DISP_CTRL_WR		1 /*Write or read selection pin*/
#define DISP_DATA_0			2
#define DISP_DATA_1			3
#define DISP_DATA_2			4
#define DISP_DATA_3			5
#define DISP_DATA_4BIT_PORT	GPIO_PDOR_REG(PTD_BASE_PTR)
#define DISP_DATA_POS		2
#define DIPS_CHARS_PER_ROW	16


/*Timer configuration*/
/*Higher the count, higher is the time required to resolve all timers*/
#define TIMERS_COUNT		3


/*Task configuration*/
#define TASK_PRIORITY_10ms	10
#define TASK_STACK_10ms		1200
#define TASK_SLICE_10ms		10
void Task_10ms(uint32_t task_init_data);


#define TASK_PRIORITY_100ms	20
#define TASK_STACK_100ms	1200
#define TASK_SLICE_100ms		100
void Task_100ms(uint32_t task_init_data);


#define TASK_PRIORITY_500ms	30
#define TASK_STACK_500ms	1200
#define TASK_SLICE_500ms		500
void Task_500ms(uint32_t task_init_data);

/*Timeout for the welcome screen message*/
#define SPLASH_TIMEOUT	1000

#if 0
#define APP_DELAY(x)	_time_delay_ticks(1);
#else
#define APP_DELAY(x)	{volatile uint32_t del = x*100; while(del--);}
#endif
/*Delay in displaying cycle count when settings key is pressed*/
#define CYCLE_CNT_DISP_DELAY	15
#define BUZZER_DELAY			2

/*Display default strings*/
#define DISP_CYCLE_CNT			"CYCLE CNT:  %.4d"
#define DISP_MODE_121_FAST		"121 FAST    %.4s"
#define DISP_MODE_121_WRAP		"121 WRAP    %.4s"
#define DISP_MODE_134_FAST		"134 FAST    %.4s"
#define DISP_MODE_134_WRAP		"134 WRAP    %.4s"


#endif /* GLOBAL_CONFIG_H_ */
