/*
 * Tasks.c
 *
 *  Created on: Jan 8, 2017
 *      Author: 
 */

#include "task_template_list.h"
#include "mqx_tasks.h"
#include "Status.h"
#include "Digital_IO.h"
#include "ADC_Handler.h"
#include "Keyhandler.h"
#include "Display_HL.h"
#include "Application.h"
#include "Global_Config.h"
#include "Timer.h"

/*Stop buzzer*/
#define BUZZ_ON Digital_IO_Set((uint32_t)DIGITAL_IO_ID_BUZ, DIGITAL_IO_LEVEL_HIGH)
#define BUZZ_OFF Digital_IO_Set((uint32_t)DIGITAL_IO_ID_BUZ, DIGITAL_IO_LEVEL_LOW)

/* Define tasks used in the system
 * Tasks will be periodic tasks. 
 * Design expectation is to execute each task at the timeout specified
 * in their configuration.
 * */
#define TASK_TEMPLATE_LIST_END         {0, 0, 0, 0, 0, 0, 0}
/* Task number                      */  
/* Entry point                      */  
/* Stack size                       */  
/* Task priority                    */  
/* Task name                        */  
/* Task attributes                  */  
/* Task parameter                   */

const TASK_TEMPLATE_STRUCT MQX_template_list[] =
{
  /* Task: Task1 */
  {
  /* Task number                      */  TASK1_TASK,
  /* Entry point                      */  (TASK_FPTR)Task_10ms,
  /* Stack size                       */  TASK1_TASK_STACK_SIZE,
  /* Task priority                    */  8U,
  /* Task name                        */  "task1",
  /* Task attributes                  */  (MQX_AUTO_START_TASK),
  /* Task parameter                   */  (uint32_t)(0)
  },
  /* Task: Task2 */
  {
  /* Task number                      */  TASK2_TASK,
  /* Entry point                      */  (TASK_FPTR)Task_100ms,
  /* Stack size                       */  TASK2_TASK_STACK_SIZE,
  /* Task priority                    */  8U,
  /* Task name                        */  "task2",
  /* Task attributes                  */  (MQX_AUTO_START_TASK),
  /* Task parameter                   */  (uint32_t)(0)
  },
  /* Task: Task3 */
  {
  /* Task number                      */  TASK3_TASK,
  /* Entry point                      */  (TASK_FPTR)Task_500ms,
  /* Stack size                       */  TASK3_TASK_STACK_SIZE,
  /* Task priority                    */  8U,
  /* Task name                        */  "task3",
  /* Task attributes                  */  (MQX_AUTO_START_TASK),
  /* Task parameter                   */  (uint32_t)(0)
  },
  TASK_TEMPLATE_LIST_END
};


void Task_10ms(uint32_t task_init_data)
{
	while(1)
	{
		AdcPoll();
		Keyhandler_poll();
		Timer_Job();
		_time_delay_ticks(8);
	}
}

void Task_100ms(uint32_t task_init_data)
{
	/*Open airvent solenoid*/
	Digital_IO_Set((uint32_t)DIGITAL_IO_ID_AIRVENT_SOL, DIGITAL_IO_LEVEL_HIGH);
	/*Stop buzzer*/
	Digital_IO_Set((uint32_t)DIGITAL_IO_ID_BUZ, DIGITAL_IO_LEVEL_LOW);
	/*Display welcome application*/
	Display_Reset();
	Display_Reset();
	Display_Reset();
	BUZZ_ON;
	Display_String(" PHOS MEDICORE  ",1);
	Display_String(" NAVEE-13  V0.0 ",2);
	Display_Refresh();
#if 0
	Timer_Start(0, 5*60*1000);
#endif
	/*Wait for the splash screen timeout*/
	_time_delay_ticks(SPLASH_TIMEOUT);
	BUZZ_OFF;
	while(1)
	{
		Application();
		
		_time_delay_ticks(90);
	}
}

void Task_500ms(uint32_t task_init_data)
{
	while(1)
	{
		_time_delay_ticks(500);
	}
}
