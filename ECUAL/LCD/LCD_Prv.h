/*
 * LCD_Prv.h
 *
 * Created: 1/22/2022 
 *  Author: Abdelrhman Elsawy
 */ 


#ifndef LCD_PRV_H_
#define LCD_PRV_H_

#define LCD_MODE_8BIT_2LINES		0x38
#define LCD_MODE_4BIT_2LINES		0x28
#define LCD_MOVE_DISP_RIGHT			0X1C
#define LCD_MOVE_DISP_LEFT			0X18
#define LCD_MOVE_CURSOR_RIGHT		0X14
#define LCD_MOVE_CURSOR_LEFT		0X10
#define LCD_DISP_OFF				0X08
#define LCD_DISP_ON		  			0X0C
#define LCD_DISP_ON_CURSOR_ON		0X0E
#define LCD_DISP_ON_CURSOR_BLINK	0X0F
#define LCD_BEGIN_AT_FIRST_RAW		0X80
#define LCD_BEGIN_AT_SECOND_RAW		0XC0
#define LCD_CLEAR					0X01
#define LCD_ENTRY_MODE				0X06

#endif /* LCD_PRV_H_ */