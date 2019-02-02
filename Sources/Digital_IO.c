/*
 * Digital_IO.c
 *
 * Implements drivers and API for initializing IO pins as digital input or output
 *  Created on: Dec 18, 2016
 *      Author: 
 */

#include "Cpu.h"
#include "Status.h"
#include "Global_Config.h"
#include "Digital_IO.h"


extern const Digital_IO_Config_st Digital_IO_Pins[DIGITAL_IO_COUNT];
status_en Digital_IO_Init(void)
{
	uint32_t i;
	
	/*Enable port clock*/
	SIM_SCGC5 |= 0x3e00;/*Enable clock to all ports PORTA, PORTB, PORTC, PORTD, PORTE*/
	/* Configure direction */
	for(i=0; i<DIGITAL_IO_COUNT; i++)
	{
		/*Clear direction field*/
		*Digital_IO_Pins[i].port_dir &= ~(0x01 << Digital_IO_Pins[i].pin);
		/*configure input/output configuration*/
		*Digital_IO_Pins[i].port_config &= ~(PORT_CONFIG_MASK);
		switch(Digital_IO_Pins[i].config)
		{
		case DIGITAL_IO_INPUT_PULL_UP:
			*Digital_IO_Pins[i].port_config |= (PORT_CONFIG_PULL_UP | PORT_CONFIG_MUX_GPIO); 
			/*Assuming that direction input is 0 and output is 1*/
			*Digital_IO_Pins[i].port_dir &= ~(0x01 << Digital_IO_Pins[i].pin);
			break;
		case DIGITAL_IO_INPUT_PULL_DOWN:
			*Digital_IO_Pins[i].port_config |= (PORT_CONFIG_PULL_DOWN | PORT_CONFIG_MUX_GPIO);
			/*Assuming that direction input is 0 and output is 1*/
			*Digital_IO_Pins[i].port_dir &= ~(0x01 << Digital_IO_Pins[i].pin);
			break;
		case DIGITAL_IO_INPUT_TRISTATE:
			*Digital_IO_Pins[i].port_config |= (PORT_PCR_INPUT | PORT_CONFIG_MUX_GPIO);
			/*Assuming that direction input is 0 and output is 1*/
			*Digital_IO_Pins[i].port_dir &= ~(0x01 << Digital_IO_Pins[i].pin);
			break;
		case DIGITAL_IO_OUTPUT_PUSHPULL:
			*Digital_IO_Pins[i].port_config |= (PORT_CONFIG_MUX_GPIO);
			/*Assuming that direction input is 0 and output is 1*/
			*Digital_IO_Pins[i].port_dir |= (0x01 << Digital_IO_Pins[i].pin);
			break;
		case DIGITAL_IO_OUTPUT_OPENDRAIN:
			*Digital_IO_Pins[i].port_config |= (PORT_CONFIG_OPENDRAIN_MSK | PORT_CONFIG_MUX_GPIO);
			/*Assuming that direction input is 0 and output is 1*/
			*Digital_IO_Pins[i].port_dir |= (0x01 << Digital_IO_Pins[i].pin);
			break;
		default:
			break;
		}
		/*Set the initial value if not invalid*/
		if(Digital_IO_Pins[i].default_level != DIGITAL_IO_LEVEL_INVALID)
		{
			if(Digital_IO_Pins[i].default_level)
			{
				*Digital_IO_Pins[i].port_data |= (Digital_IO_Pins[i].default_level < Digital_IO_Pins[i].pin);
			}
			else
			{
				*Digital_IO_Pins[i].port_data &= ~(Digital_IO_Pins[i].default_level < Digital_IO_Pins[i].pin);
			}
		}
	}
	return STATUS_SUCCESS;
}

status_en Digital_IO_PORT_Init(const Digital_IO_Config_st * ptr_config, uint32_t size)
{
	uint32_t i;
	
	/*Enable port clock*/
	SIM_SCGC5 |= 0x3e00;/*Enable clock to all ports PORTA, PORTB, PORTC, PORTD, PORTE*/
	/* Configure direction */
	for(i=0; i<size; i++)
	{
		/*Clear direction field*/
		*ptr_config[i].port_dir &= ~(0x01 << ptr_config[i].pin);
		/*Assuming that direction input is bitfield 0 and output is bitfield 1*/
		*ptr_config[i].port_dir |= (0x01 << ptr_config[i].pin);
		/*configure input/output configuration*/
		*ptr_config[i].port_config &= ~(PORT_CONFIG_MASK);
		switch(ptr_config[i].config)
		{
		case DIGITAL_IO_INPUT_PULL_UP:
			*ptr_config[i].port_config |= (PORT_CONFIG_PULL_UP | PORT_CONFIG_MUX_GPIO); 
			break;
		case DIGITAL_IO_INPUT_PULL_DOWN:
			*ptr_config[i].port_config |= (PORT_CONFIG_PULL_DOWN | PORT_CONFIG_MUX_GPIO);			
			break;
		case DIGITAL_IO_OUTPUT_PUSHPULL:
			*ptr_config[i].port_config |= (PORT_CONFIG_MUX_GPIO);
			break;
		case DIGITAL_IO_OUTPUT_OPENDRAIN:
			*ptr_config[i].port_config |= (PORT_CONFIG_OPENDRAIN_MSK | PORT_CONFIG_MUX_GPIO);
			break;
		default:
			break;
		}
		/*Set the initial value if not invalid*/
		if(ptr_config[i].default_level != DIGITAL_IO_LEVEL_INVALID)
		{
			*ptr_config[i].port_data |= (ptr_config[i].default_level < ptr_config[i].pin);
		}
	}
	return STATUS_SUCCESS;
}

Digital_IO_Level_en Digital_IO_Get(uint32_t pin)
{
	Digital_IO_Config_st * port_ptr;
	Digital_IO_Level_en state = DIGITAL_IO_LEVEL_INVALID;
	if(pin < DIGITAL_IO_COUNT)
	{
		port_ptr = &Digital_IO_Pins[pin];
		state = (Digital_IO_Level_en)(((*port_ptr->port_data) & (0x01 << port_ptr->pin)) >> port_ptr->pin); 
	}
	return state;
}

status_en Digital_IO_Set(uint32_t pin, Digital_IO_Level_en level)
{
	Digital_IO_Config_st * port_ptr;
	status_en state = STATUS_FAIL;
	if(pin < DIGITAL_IO_COUNT)
	{
		port_ptr = &Digital_IO_Pins[pin];
		if(port_ptr->direction == DIGITAL_IO_DIR_OUTPUT)
		{
			if(level == DIGITAL_IO_LEVEL_HIGH)
			{
				*port_ptr->port_data |= (0x01 << port_ptr->pin); 
			}
			else
			{
				*port_ptr->port_data &= ~(0x01 << port_ptr->pin);
			}
			state = STATUS_SUCCESS;
		}
	}
	return state;
}
