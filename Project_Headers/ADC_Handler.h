/*
 * ADC_Handler.h
 *
 *  Created on: Jan 8, 2017
 *      Author: 
 */

#ifndef ADC_HANDLER_H_
#define ADC_HANDLER_H_

typedef enum {
	ADC_SINGLE_ENDED,
	ADC_DIFFERENTIAL
}ADC_Type_en;

typedef struct {
	uint32_t * ADC_Base;
	uint32_t channel;
	ADC_Type_en ADC_Type;
	IO_Pin_st pin_config;
}ADC_Config_st;

status_en Adc_init(void);
void AdcPoll(void);
uint32_t Adc_Get(uint32_t sensor);

uint32_t Pressure_Get(void);
uint32_t Temperature_Get(void);



#endif /* ADC_HANDLER_H_ */
