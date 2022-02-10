/*
 * LCD.h
 *
 * Created: 1/19/2022
 * Author : Abdelrhman Elsawy
 */

#ifndef LCD_H_
#define LCD_H_

#include "../../LIB/Typedef.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/TIMER2/TIMER2.h"
#include "../../LIB/BIT_Math.h"
#include "LCD_cfg.h"
#include "LCD_ERR_Handle.h"
#include "LCD_Prv.h"
#include "../../MCAL/UART/UART.h"

#define FIRST_NIBBLE     0
#define SECOND_NIBBLE	 1
#define FINISHED		 0xFF


#define FIRST_COMMAND		0
#define SECOND_COMMAND		1
#define THIRD_COMMAND		2
#define FOURTH_COMMAND		3
#define FIFTH_COMMAND		4
#define SIXTH_COMMAND		5



uint8_t LCD_u8Init(void);
uint8_t LCD_u8SendCommand(uint8_t command);
uint8_t LCD_u8SendData(uint8_t data);
uint8_t LCD_u8SendNumber(uint16_t num);
uint8_t LCD_u8SendString(uint8_t *str);
uint8_t LCD_u8SetPosition(uint8_t row, uint8_t col);
uint8_t LCD_u8ClearScreen(void);
uint8_t LCD_u8MoveCursorLeft(void);
uint8_t LCD_u8MoveCursorRight(void);
void Change_LCD_State(void);


#endif /* LCD_H_ */
