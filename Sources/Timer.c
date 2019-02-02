/*
 * Timer.c
 *
 *  Created on: Jan 22, 2017
 *      Author: 
 *      
 *  Description:
 *  File implements software timer routines and counts using hardware timer as reference.
 */

#include "Cpu.h"
#include "Status.h"
#include "Global_Config.h"
#include "Timer.h"
PE_ISR(TU3_Interrupt);

#define TIMER_GRANULARITY	500 /*Timer interrupt generated for this number of milliseconds*/

/*Array of timers required for the system*/
static Timer_st Timers[TIMERS_COUNT];

/*Counter counts for every 500ms since timer is loaded with count equivalent to 500ms*/
static uint32_t time_counter = 0, prev_counter = 0, overflow_counter = 0, prev_overflow_count = 0; 
status_en Timer_HL_init(void)
{
	/*Disable gating for periodic timer PIT*/
	/* SIM_SCGC6: PIT=1 */
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

	/*Enable clock*/
	PIT_MCR = 0x00U;
	/*PIT3*/
	/*Clear control register*/
	PIT_TCTRL3 = 0x00U;
	/*Clear flag*/
	PIT_TFLG3 = PIT_TFLG_TIF_MASK;
	/*Set up load register*/
	PIT_LDVAL3 = PIT_LDVAL_TSV(0x009FFFFF);
	
	/*Configure interrupt*/
	NVICIP33 = NVIC_IP_PRI33(0x80);
	NVICISER1 |= NVIC_ISER_SETENA(0x02);
	PIT_TCTRL3 = (PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);
	/*Start timer*/
	PIT_TCTRL3 |= PIT_TCTRL_TEN_MASK;
	return STATUS_SUCCESS;
}


PE_ISR(TU3_Interrupt)
{
	/*Clear the interrupt flag*/
	PIT_TFLG3 = PIT_TFLG_TIF_MASK;
	/*Set up load register*/
	PIT_LDVAL3 = PIT_LDVAL_TSV(0x009FFFFF);
	if((time_counter+1) < time_counter)
	{
		overflow_counter++;
	}
	time_counter = time_counter + 1;
}

status_en Timer_Start(uint32_t index, uint32_t time, timeout_fn func)
{
	status_en stat = STATUS_SUCCESS;
	if(index < TIMERS_COUNT)
	{
		if(Timers[index].state != TIMER_RUNNING)
		{
			Timers[index].init_stamp = time_counter * TIMER_GRANULARITY;
			Timers[index].req_time = time;
			Timers[index].cur_count = 0;
			Timers[index].state = TIMER_RUNNING;
			Timers[index].timeout = func;
		}
	}
	else
	{
		stat = STATUS_FAIL;
	}
	return stat;
}

status_en Timer_Stop(uint32_t index)
{
	status_en stat = STATUS_SUCCESS;
	if(index < TIMERS_COUNT)
	{
		Timers[index].state = TIMER_STOPPED;
	}
	else
	{
		stat = STATUS_INVALID_INPUT;		
	}
	return stat;
}

Timer_state_en Timer_GetState(uint32_t index)
{
	if(index < TIMERS_COUNT)
	{
		return Timers[index].state;
	}
	else
	{
		return TIMER_INVALID;
	}
}

void Timer_Job(void)
{
	static uint32_t timer_index = 0;
	if(timer_index < TIMERS_COUNT)
	{
		if(Timers[timer_index].state == TIMER_RUNNING)
		{
			if(time_counter < prev_counter)
			{
				Timers[timer_index].cur_count += ((0xffffffff - prev_counter) + time_counter)*TIMER_GRANULARITY; 
			}
			else
			{
				Timers[timer_index].cur_count += (time_counter - prev_counter)*TIMER_GRANULARITY;
			}
			if(Timers[timer_index].cur_count >= Timers[timer_index].req_time)
			{
				Timers[timer_index].state = TIMER_IDLE;
				if(Timers[timer_index].timeout != NULL)
				{
					Timers[timer_index].timeout();
				}
			}
		}
		timer_index++;
	}
	else
	{
		timer_index = 0;
	}
	prev_counter = time_counter;
}

uint32_t Timer_Get(uint32_t timer_index)
{
	uint32_t ret_val = 0;
	if(timer_index < TIMERS_COUNT)
	{
		if(Timers[timer_index].state == TIMER_RUNNING)
		{
			ret_val = Timers[timer_index].cur_count;
		}
	}
	return ret_val;
}

uint32_t Timer_Remaining(uint32_t timer_index)
{
	uint32_t ret_val = 0;
	if(timer_index < TIMERS_COUNT)
	{
		ret_val = (Timers[timer_index].req_time - Timers[timer_index].cur_count);
	}
	return ret_val;
}
