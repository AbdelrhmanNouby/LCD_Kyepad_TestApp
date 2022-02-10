/*
 * LCD_Keypad.c
 *
 * Created: 2/9/2022 
 * Author : Abdelrhman Elsawy
 */ 

#include "../ECUAL/KEYPAD/KEYPAD_interface.h"
#include "../ECUAL/LCD/LCD.h"

int main(void)
{
	UART_u8Init();
	KEYPAD_u8Init();
	uint8_t KEYPAD_State = KEYPAD_NO_PRESSED_KEY ;
	uint8_t flag = LOW ;
    while (1)
    {
		KEYPAD_u8GetPressedKey(&KEYPAD_State);
		if ( flag == LOW )
		{
			if ( LCD_u8Init() == FINISHED )
				flag = HIGH ;				
			UART_u8SendByte('i');
		}
		else 
		{
			if (( KEYPAD_State > 0) && ( KEYPAD_State < 10 ))
			{
				while ( LCD_u8SendData( KEYPAD_State + '0' ) != FINISHED )
					UART_u8SendByte('d');
			}
		}
    }
}

