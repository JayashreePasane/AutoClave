/*
 * Display_HL.h
 *
 *  Created on: Jan 15, 2017
 *      Author: 
 */

#ifndef DISPLAY_HL_H_
#define DISPLAY_HL_H_

status_en Display_Init(void);
void Display_String(char * str, uint8_t line);
void Display_Reset(void);
void Display_Refresh(void);

#endif /* DISPLAY_HL_H_ */
