/*
 * Timer.h
 *
 *  Created on: Jan 22, 2017
 *      Author: 
 */

#ifndef TIMER_H_
#define TIMER_H_

typedef enum
{
	TIMER_IDLE,			/*When the timer is not started*/
	TIMER_RUNNING,		/*Timer started and ticking*/
	TIMER_PAUSE,		/*Timer paused in the middle*/
	TIMER_STOPPED,		/*Timer stopped forcibly*/
	TIMER_INVALID		/*Invalid*/
}Timer_state_en;

/*Function pointer type for timeout execution*/
typedef void (*timeout_fn)(void);
/*Structure to represent software timers*/
typedef struct 
{
	uint32_t init_stamp;	/*Time counter value when timer was started*/
	uint32_t req_time;		/*Requested time in milliseconds*/
	uint32_t cur_count;
	timeout_fn timeout;
	Timer_state_en state;
}Timer_st;

status_en Timer_HL_init(void);
status_en Timer_Start(uint32_t index, uint32_t time, timeout_fn func);
status_en Timer_Stop(uint32_t index);
Timer_state_en Timer_GetState(uint32_t index);
void Timer_Job(void);
uint32_t Timer_Get(uint32_t timer_index);
uint32_t Timer_Remaining(uint32_t timer_index);
#endif /* TIMER_H_ */
