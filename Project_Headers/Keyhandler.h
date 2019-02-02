/*
 * keyhandler.h
 *
 *  Created on: Dec 17, 2016
 *      Author: 
 */

#ifndef KEYHANDLER_H_
#define KEYHANDLER_H_

#include "Status.h"


typedef struct keyhandler_conf
{
	GPIO_MemMapPtr port_base;		/**< GPIO port base address */
	uint32_t bit_pos;				/**< Key bit position */
	volatile uint32_t* pin_pcr;		/**< Pin control register pointer */
	volatile uint32_t pin_config;	/**< Ping control register value to be configured */
	
}keyhandler_conf_st;

typedef enum
{
	KEY_MODE,
	KEY_START_STOP,
	KEY_SETTINGS,
	KEY_WATER_LEVEL,
	KEY_INVALID
}Key_ID_en;



status_en Keyhandler_init(void);
status_en Keyhandler_poll(void);
bool Keyhandler_Get(uint32_t key);

#endif /* KEYHANDLER_H_ */
