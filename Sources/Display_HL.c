/*
 * Display_HL.c
 *
 *  Created on: Jan 15, 2017
 *      Author: 
 */


#include "Cpu.h"
#include "Status.h"
#include "Global_Config.h"
#include "Digital_IO.h"
#include "mqxlite.h"
#include "Display_HL.h"

static void LCD_IO_Reset(void);
static void LCD_Reset(void);
static void LCD_SendCmd(uint8_t val);
static void LCD_SendData(uint8_t val);
static void Display_WriteData(char * str, uint8_t line);

extern const Digital_IO_Config_st Display_IO[6];

/*Buffers for display data*/
char Display_Buffer[2][16];

/*Function to initialize the IO pins used for Display driver*/
status_en Display_Init(void)
{
	/*Enable port clock*/
	SIM_SCGC5 |= 0x3e00;/*Enable clock to all ports PORTA, PORTB, PORTC, PORTD, PORTE*/
	
	Digital_IO_PORT_Init(Display_IO, (sizeof(Display_IO) / sizeof(Digital_IO_Config_st)));
	
	return STATUS_SUCCESS;
}

/*LCD functions*/
static void LCD_Reset(void)
{
   LCD_IO_Reset();
   _time_delay_ticks(1);
   LCD_SendCmd(0x33);
   LCD_SendCmd(0x33);  /* LCD reset */
   LCD_SendCmd(0x32);
   _time_delay_ticks(1);
   LCD_SendCmd(0x01);
   LCD_SendCmd(0x28);  /*4bit 2 * 16 mode*/
   LCD_SendCmd(0x06);   /*shift right automatically*/
   _time_delay_ticks(1);
   LCD_SendCmd(0x0c);   /*Display on cursor off*/
   _time_delay_ticks(1);
   LCD_SendCmd(0x01);   /*clear*/
   _time_delay_ticks(1);
	LCD_SendCmd(0x80);
	LCD_SendData(0x00);
	_time_delay_ticks(2);
}

static void LCD_SendCmd(uint8_t val)
{
	uint8_t data = (val & 0xf0) >> 4;
	uint8_t mask = 0x01;
	/*Set output with most significant nibble*/
	/*Clear data pins*/
	LCD_IO_Reset();
	
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_0].pin);
	data = data >> 1;
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_1].pin);
	data = data >> 1;
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_2].pin);
	data = data >> 1;
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_3].pin);
	/*delay to settle the data*/
	APP_DELAY(1);
	/*Reset RS(Cmd/Data) bit*/
	*Display_IO[DISP_CTRL_CD].port_data &= ~(0x01 << Display_IO[DISP_CTRL_CD].pin);
	APP_DELAY(1);
	/*Set RL(Rd/Wr) bit*/
	*Display_IO[DISP_CTRL_WR].port_data |= (0x01 << Display_IO[DISP_CTRL_WR].pin);
	APP_DELAY(1);
	*Display_IO[DISP_CTRL_WR].port_data &= ~(0x01 << Display_IO[DISP_CTRL_WR].pin);
	
	/*Lower nibble*/
	data = (val & 0x0f);
	mask = 0x01;
	LCD_IO_Reset();
	
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_0].pin);
	data = data >> 1;
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_1].pin);
	data = data >> 1;
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_2].pin);
	data = data >> 1;
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_3].pin);
	/*delay to settle the data*/
	APP_DELAY(1);
	/*Reset RS(Cmd/Data) bit*/
	*Display_IO[DISP_CTRL_CD].port_data &= ~(0x01 << Display_IO[DISP_CTRL_CD].pin);
	APP_DELAY(1);
	/*Set RL(Rd/Wr) bit*/
	*Display_IO[DISP_CTRL_WR].port_data |= (0x01 << Display_IO[DISP_CTRL_WR].pin);
	APP_DELAY(1);
	*Display_IO[DISP_CTRL_WR].port_data &= ~(0x01 << Display_IO[DISP_CTRL_WR].pin);
}

static void LCD_SendData(uint8_t val)
{
	uint8_t data = (val & 0xf0) >> 4;
	uint8_t mask = 0x01;
	/*Set output with most significant nibble*/
	/*Clear data pins*/
	LCD_IO_Reset();
	
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_0].pin);
	data = data >> 1;
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_1].pin);
	data = data >> 1;
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_2].pin);
	data = data >> 1;
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_3].pin);
	/*delay to settle the data*/
	APP_DELAY(1);
	/*Set RS(Cmd/Data) bit*/
	*Display_IO[DISP_CTRL_CD].port_data |= (0x01 << Display_IO[DISP_CTRL_CD].pin);
	APP_DELAY(1);
	/*Set RL(Rd/Wr) bit*/
	*Display_IO[DISP_CTRL_WR].port_data |= (0x01 << Display_IO[DISP_CTRL_WR].pin);
	APP_DELAY(1);
	*Display_IO[DISP_CTRL_WR].port_data &= ~(0x01 << Display_IO[DISP_CTRL_WR].pin);
	
	/*Lower nibble*/
	data = (val & 0x0f);
	mask = 0x01;
	LCD_IO_Reset();
	
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_0].pin);
	data = data >> 1;
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_1].pin);
	data = data >> 1;
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_2].pin);
	data = data >> 1;
	DISP_DATA_4BIT_PORT |= ((mask & data) << Display_IO[DISP_DATA_3].pin);
	/*delay to settle the data*/
	APP_DELAY(1);
	/*Reset RS(Cmd/Data) bit*/
	*Display_IO[DISP_CTRL_CD].port_data |= (0x01 << Display_IO[DISP_CTRL_CD].pin);
	APP_DELAY(1);
	/*Set RL(Rd/Wr) bit*/
	*Display_IO[DISP_CTRL_WR].port_data |= (0x01 << Display_IO[DISP_CTRL_WR].pin);
	APP_DELAY(1);
	*Display_IO[DISP_CTRL_WR].port_data &= ~(0x01 << Display_IO[DISP_CTRL_WR].pin);
}

static void LCD_IO_Reset(void)
{
	uint32_t i;
	for(i=0;i<(sizeof(Display_IO) / sizeof(Digital_IO_Config_st)); i++)
	{
		*Display_IO[i].port_data &= ~(0x01 << Display_IO[i].pin);
	}
}

static void Display_WriteData(char * str, uint8_t line)
{
	uint32_t char_count = 0;
	if(line == 1)
	{
		LCD_SendCmd(0x80);
	}
	else if(line == 2)
	{
		LCD_SendCmd(0xc0);
	}
	
	while((*str) && (char_count < DIPS_CHARS_PER_ROW)){
		LCD_SendData(*str);
		str++;
		char_count++;
	}
}

void Display_String(char * str, uint8_t line)
{
	uint32_t char_count = 0;
	if(!((line == 1) || (line == 2)))
	{
		return;
	}
	
	while((*str) && (char_count < DIPS_CHARS_PER_ROW)){
		Display_Buffer[line - 1][char_count] = *str;
		str++;
		char_count++;
	}
}

void Display_Reset(void)
{
	LCD_Reset();
}

void Display_Refresh(void)
{
	Display_WriteData(Display_Buffer[0], 1);
	Display_WriteData(Display_Buffer[1], 2);
}

