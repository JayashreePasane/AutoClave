/*
 * Keyhandler.c
 * 
 * Description:
 * File implements all interfaces and threads responsible for polling and debouncing key press/release actions.
 * Configures hardware pins with direction and pull up properties, configures timers if required and does everything
 * that is specific to microcontroller or board.
 *
 * Configurations:
 * KEYS_COUNT - Macro that defines the number of buttons
 * KEY_DEBNCE_TIME - Macro defines the time/count for key debounce
 *  
 * 
 *  Created on: Dec 11, 2016
 *      Author: 
 */

#include "Cpu.h"
#include "Global_Config.h"
#include "Keyhandler.h"

extern const keyhandler_conf_st key_list[KEYS_COUNT];
/* Global variable definition */
byte key_status[(KEYS_COUNT/32) + ((KEYS_COUNT % 32)?1:0)][KEY_DEBNCE_SAMPLES + 1];

/* Local variable declaration*/
static uint32_t sample_index = 0;
static status_en keyhandler_hw_init(void)
{
	status_en status = STATUS_SUCCESS;
	uint32_t i;
	/*Enable port clock*/
	SIM_SCGC5 |= 0x3e00;/*Enable clock to all ports PORTA, PORTB, PORTC, PORTD, PORTE*/
	for(i=0; i<KEYS_COUNT; i++)
	{
		GPIO_PDDR_REG(key_list[i].port_base) &= ~(0x01 << key_list[i].bit_pos);
		*key_list[i].pin_pcr = key_list[i].pin_config;
	}
	return status;
}
status_en Keyhandler_init(void)
{
	status_en status = STATUS_SUCCESS;
	
	status = keyhandler_hw_init();
	if(status != STATUS_SUCCESS)
	{
		
	}
	return status;
}

static bool key_debounce(uint32_t key)
{
	uint32_t bitpos = key % 32;
	uint32_t indx = ((uint32_t)key)/32;
	uint32_t bitmask = 0x01 << bitpos;
	uint32_t integrity,sample, i;
	sample = key_status[indx][0] & bitmask;
	integrity = 0;
	for(i=1;i<KEY_DEBNCE_SAMPLES; i++)
	{
		integrity |= (sample ^ (key_status[indx][i] & bitmask));
	}
	
	if(integrity == 0)
	{
		if(sample & bitmask)
		{
			key_status[indx][KEY_DEBNCE_SAMPLES] |= bitmask;
		}
		else
		{
			key_status[indx][KEY_DEBNCE_SAMPLES] &= (~bitmask);
		}
	}
	return ((key_status[indx][KEY_DEBNCE_SAMPLES] & bitmask) >> bitpos);
}

status_en Keyhandler_poll(void)
{
	byte indx;
	status_en status = STATUS_SUCCESS;
	for(indx = 0; indx < KEYS_COUNT; indx++)
	{
		key_status[indx/32][sample_index] &= ~(0x01 << (indx % 32));
		key_status[indx/32][sample_index] |= ((GPIO_PDIR_REG(key_list[indx].port_base) >> key_list[indx].bit_pos) << (indx % 32));
	}
	sample_index = (sample_index + 1) % KEY_DEBNCE_SAMPLES;
	if(sample_index == 0)
	{
		for(indx = 0; indx < KEYS_COUNT; indx++)
		{
			key_debounce(indx);
		}
	}
	return status;
}

bool Keyhandler_Get(uint32_t key)
{
	uint32_t bitpos = key % 32;
	if(key < KEYS_COUNT)
	{
		return (!((key_status[key/32][KEY_DEBNCE_SAMPLES] & (0x01 << bitpos)) >> bitpos));
	}
	else
	{
		return FALSE;
	}
}
