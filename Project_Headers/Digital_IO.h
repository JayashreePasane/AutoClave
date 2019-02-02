/*
 * Digital_IO.h
 *
 *  Created on: Dec 24, 2016
 *      Author: 
 */

#ifndef DIGITAL_IO_H_
#define DIGITAL_IO_H_

typedef enum {
	DIGITAL_IO_DIR_INPUT,
	DIGITAL_IO_DIR_OUTPUT,
	DIGITAL_IO_DIR_INVALID
}Digital_IO_dir_en;

typedef enum {
	DIGITAL_IO_INPUT_TRISTATE,
	DIGITAL_IO_INPUT_PULL_UP,
	DIGITAL_IO_INPUT_PULL_DOWN,
	DIGITAL_IO_OUTPUT_PUSHPULL,
	DIGITAL_IO_OUTPUT_OPENDRAIN
}Digital_IO_config_en;

typedef enum {
	DIGITAL_IO_LEVEL_LOW,
	DIGITAL_IO_LEVEL_HIGH,
	DIGITAL_IO_LEVEL_INVALID
}Digital_IO_Level_en;

typedef struct
{
	GPIO_MemMapPtr port_base;		/**< GPIO port base address */
	uint32_t bit_pos;				/**< Key bit position */
	volatile uint32_t* pin_pcr;		/**< Pin control register pointer */
	volatile uint32_t pin_config;	/**< Ping control register value to be configured */
}IO_Pin_st;

typedef struct
{
	uint32_t * port_config;
	uint32_t * port_dir;
	uint32_t * port_data;
	uint32_t pin;
	Digital_IO_dir_en direction;
	Digital_IO_config_en config;
	Digital_IO_Level_en default_level;
}Digital_IO_Config_st;

status_en Digital_IO_Init(void);
status_en Digital_IO_PORT_Init(const Digital_IO_Config_st * ptr_config, uint32_t size);
Digital_IO_Level_en Digital_IO_Get(uint32_t pin);
status_en Digital_IO_Set(uint32_t pin, Digital_IO_Level_en level);


#endif /* DIGITAL_IO_H_ */
