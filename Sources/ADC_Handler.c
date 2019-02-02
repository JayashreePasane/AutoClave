/*
 *
 * AdcHandler.c
 * Description:
 * Implementation of adc measurement logic, API for accessing adc from
 * application use case like temperature, pressure.
 * 
 *  Created on: Dec 18, 2016
 *      Author: 
 */
#include "Cpu.h"
#include "Status.h"
#include "Digital_IO.h"
#include "ADC_Handler.h"
#include "Global_Config.h"

extern const ADC_Config_st ADC_Config[ADC_SENSORS];
/*Buffer to hold adc samples. The last sample holds the debounced value*/
uint32_t Adc_Samples[ADC_SENSORS][ADC_SAMPLE_COUNT+1];

/*Hardware peripheral initialization function*/
status_en Adc_init(void)
{
	uint32_t i;
	/*Initialize IO pin and the ADC peripheral.*/
	ADC_MemMapPtr ptr_adc_base;
	
	/*Enable port clock*/
	SIM_SCGC5 |= 0x3e00;/*Enable clock to all ports PORTA, PORTB, PORTC, PORTD, PORTE*/
	/*Enable clock for ADC0*/
	SIM_SCGC6 |= 0x08000000;
	
	ptr_adc_base = (ADC_MemMapPtr )ADC_Config[0].ADC_Base;
			
	/*Configure the channel number for continuous conversion*/
	ptr_adc_base->CFG2 = 0;
	/*Clock div=0, Mode= 3(16-bit) Input clock = Bus clock*/
	ptr_adc_base->CFG1 = (ADC_CFG1_ADIV(0x00) | ADC_CFG1_ADLSMP_MASK | 
			  ADC_CFG1_MODE(0x02) |
			  ADC_CFG1_ADICLK(0x00));
	ptr_adc_base->SC2 = 0;
	ptr_adc_base->SC3 = 0;
	ptr_adc_base->SC2 = 0;
	
	for(i=0;i<ADC_SENSORS; i++)
	{
		/*Configure the pin alternate functions*/
		if(ADC_Config[i].pin_config.port_base != NULL)
		{
			*ADC_Config[i].pin_config.pin_pcr = ADC_Config[i].pin_config.pin_config;
		}
	}
	return STATUS_SUCCESS;
}

void AdcPoll(void)
{
	uint32_t i,j,adc_val;
	static uint32_t sensor_id = 0, Adc_sample = 0;
	
	/*Start ADC conversion and store the result*/
	ADC_SC1_REG((ADC_MemMapPtr )ADC_Config[sensor_id].ADC_Base,0) = (uint32_t)ADC_Config[sensor_id].channel;
	/*Wait for conversion complete*/
	while(!(ADC_SC1_REG((ADC_MemMapPtr )ADC_Config[sensor_id].ADC_Base,0) & ADC_SC1_COCO_MASK));
	adc_val = ADC_R_REG((ADC_MemMapPtr )ADC_Config[sensor_id].ADC_Base,0);
	
	Adc_Samples[sensor_id][Adc_sample] = adc_val;
	sensor_id = (sensor_id + 1) % ADC_SENSORS;
	/*Update next sample index if all sensors are sampled*/
	if(sensor_id == 0)
	{
		Adc_sample = (Adc_sample + 1) % ADC_SAMPLE_COUNT;
		/*Find average value of all sensor readings*/
		if(Adc_sample == 0)
		{
			for(i = 0; i<ADC_SENSORS; i++)
			{
				adc_val = 0;
				for(j=0;j<ADC_SAMPLE_COUNT;j++)
				{
					adc_val += Adc_Samples[i][j];
				}
				Adc_Samples[i][ADC_SAMPLE_COUNT] = adc_val / ADC_SAMPLE_COUNT;
			}
		}
	}
}

uint32_t Adc_Get(uint32_t sensor)
{
	if(sensor < ADC_SENSORS)
	{
		return Adc_Samples[sensor][ADC_SAMPLE_COUNT];
	}
	else
	{
		return 0;
	}
}

