/*
 * LCD.c
 *
 * Created: 1/19/2022
 * Author : Abdelrhman Elsawy
 */

#include "LCD.h"

uint8_t LCD_State = FIRST_NIBBLE ;
uint8_t init_State = FIRST_COMMAND ;
uint8_t delay_finished = HIGH ;

uint8_t LCD_u8Init(void) 
{	
	TIMER2_u8Init();
	uint8_t u8Errorstate = STD_TYPES_OK ;
	if ( DIO_u8SetPinDirection( RS_PORT , RS_PIN , OUTPUTPIN ) != STD_TYPES_OK )
		u8Errorstate = LCD_Init_Error ;
	if ( DIO_u8SetPinDirection( RW_PORT , RW_PIN , OUTPUTPIN ) != STD_TYPES_OK )
		u8Errorstate = LCD_Init_Error ;
	if ( DIO_u8SetPinDirection( E_PORT , E_PIN , OUTPUTPIN ) != STD_TYPES_OK )
		u8Errorstate = LCD_Init_Error ;
	if ( DIO_u8SetPinDirection( D4_PORT , D4_PIN , OUTPUTPIN ) != STD_TYPES_OK )
		u8Errorstate = LCD_Init_Error ;
	if ( DIO_u8SetPinDirection( D5_PORT , D5_PIN , OUTPUTPIN ) != STD_TYPES_OK )
		u8Errorstate = LCD_Init_Error ;
	if ( DIO_u8SetPinDirection( D6_PORT , D6_PIN , OUTPUTPIN ) != STD_TYPES_OK )
		u8Errorstate = LCD_Init_Error ;
	if ( DIO_u8SetPinDirection( D7_PORT , D7_PIN , OUTPUTPIN ) != STD_TYPES_OK )
		u8Errorstate = LCD_Init_Error ;		
   switch ( init_State )
   {
    case FIRST_COMMAND :	 
    {  		
		if ( LCD_u8SendCommand(0x33) == FINISHED )
		{
			init_State = SECOND_COMMAND ;
			u8Errorstate = LCD_Init_Error ;
		}
		break;
    }
	case SECOND_COMMAND :
	{
		if ( LCD_u8SendCommand(0x32) == FINISHED )
		{
			init_State = THIRD_COMMAND ;
			u8Errorstate = LCD_Init_Error ;
		}
		break;
	}
	case THIRD_COMMAND :
	{
		if ( LCD_u8SendCommand(LCD_MODE_4BIT_2LINES) == FINISHED )
		{
			u8Errorstate = LCD_Init_Error ;
			init_State = FOURTH_COMMAND ;
		}
		break;
	}
	case FOURTH_COMMAND :
	{
		if ( LCD_u8SendCommand(LCD_DISP_ON) == FINISHED )
		{
			u8Errorstate = LCD_Init_Error ;
			init_State = FIFTH_COMMAND ;
		}	
		break;
	}
	case FIFTH_COMMAND :
	{
		if ( LCD_u8SendCommand(LCD_ENTRY_MODE) == FINISHED )
		{
			u8Errorstate = LCD_Init_Error ;
			init_State = SIXTH_COMMAND;
		}	
		break;
	}
	case SIXTH_COMMAND :
	{
		if ( LCD_u8SendCommand(LCD_CLEAR) == FINISHED )
		{
			u8Errorstate = LCD_Init_Error ;
			init_State = FINISHED ;
		}
		break;	
	} 
	case FINISHED :
	{
		u8Errorstate = FINISHED ;
		init_State = FIRST_COMMAND ;
		break;
	}	
   }
   return u8Errorstate ;
}

uint8_t LCD_u8SendCommand(uint8_t command)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	uint8_t bit ;
	switch ( LCD_State )
	{
	case FIRST_NIBBLE :
	{
		if ( u8ErrorState == STD_TYPES_OK )
		{
			bit = GET_BIT(command, 4);
			u8ErrorState = DIO_u8SetPinData(D4_PORT,D4_PIN,bit);			
		}
		if ( u8ErrorState == STD_TYPES_OK )
		{
			bit = GET_BIT(command, 5);
			u8ErrorState = DIO_u8SetPinData(D5_PORT,D5_PIN,bit);
		}

		if ( u8ErrorState == STD_TYPES_OK )
		{
			bit = GET_BIT(command, 6);
			u8ErrorState = DIO_u8SetPinData(D6_PORT,D6_PIN,bit);
		}
		if ( u8ErrorState == STD_TYPES_OK )
		{
			bit = GET_BIT(command, 7);
			u8ErrorState = DIO_u8SetPinData(D7_PORT,D7_PIN,bit);
		}
		if ( u8ErrorState == STD_TYPES_OK )
		{
			u8ErrorState = DIO_u8SetPinData(RS_PORT,RS_PIN,LOW);
		}
		if ( u8ErrorState == STD_TYPES_OK )
		{
			u8ErrorState = DIO_u8SetPinData(RW_PORT,RW_PIN,LOW);
		}
		if ( u8ErrorState == STD_TYPES_OK )
		{
			u8ErrorState = DIO_u8SetPinData(E_PORT,E_PIN,HIGH);
		}
		if (( delay_finished ) && ( u8ErrorState == STD_TYPES_OK ))
		{
			u8ErrorState = TIMER2_u8ISRDelay_ms(3,Change_LCD_State);
			delay_finished = LOW ;
		}
		break;
	}
	case SECOND_NIBBLE :
	{	
		if ( u8ErrorState == STD_TYPES_OK )
		{
			bit = GET_BIT(command, 0);
			u8ErrorState = DIO_u8SetPinData(D4_PORT,D4_PIN,bit);
		}
		if ( u8ErrorState == STD_TYPES_OK )
		{
			bit = GET_BIT(command, 1);
			u8ErrorState = DIO_u8SetPinData(D5_PORT,D5_PIN,bit);
		}
		if ( u8ErrorState == STD_TYPES_OK )
		{
			bit = GET_BIT(command, 2);
			u8ErrorState = DIO_u8SetPinData(D6_PORT,D6_PIN,bit);
		}
		if ( u8ErrorState == STD_TYPES_OK )
		{
			bit = GET_BIT(command, 3);
			u8ErrorState = DIO_u8SetPinData(D7_PORT,D7_PIN,bit);
		}
		if ( u8ErrorState == STD_TYPES_OK )
		{
			u8ErrorState = DIO_u8SetPinData(RS_PORT,RS_PIN,LOW);
		}
		if ( u8ErrorState == STD_TYPES_OK )
		{
			u8ErrorState = DIO_u8SetPinData(RW_PORT,RW_PIN,LOW);
		}
		if ( u8ErrorState == STD_TYPES_OK )
		{
			u8ErrorState = DIO_u8SetPinData(E_PORT,E_PIN,HIGH);
		}
		if (( delay_finished ) && ( u8ErrorState == STD_TYPES_OK ))
		{
			u8ErrorState = TIMER2_u8ISRDelay_ms(3,Change_LCD_State);
			delay_finished = LOW ;
		}
		break;
	}
	case FINISHED :
	{
		if (( delay_finished ) && ( u8ErrorState == STD_TYPES_OK ))
		{
			u8ErrorState = TIMER2_u8ISRDelay_ms(1,Change_LCD_State);
			delay_finished = LOW ;
			u8ErrorState = FINISHED ;
		}
		break;
	}
	}
	return u8ErrorState ;
}

uint8_t LCD_u8SendData(uint8_t data) 
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	uint8_t bit ;
	switch ( LCD_State )
	{
		case FIRST_NIBBLE :
		{
			if ( u8ErrorState == STD_TYPES_OK )
			{
				bit = GET_BIT(data, 4);
				u8ErrorState = DIO_u8SetPinData(D4_PORT,D4_PIN,bit);
			}
			if ( u8ErrorState == STD_TYPES_OK )
			{
				bit = GET_BIT(data, 5);
				u8ErrorState = DIO_u8SetPinData(D5_PORT,D5_PIN,bit);
			}
			if ( u8ErrorState == STD_TYPES_OK )
			{
				bit = GET_BIT(data, 6);
				u8ErrorState = DIO_u8SetPinData(D6_PORT,D6_PIN,bit);
			}
			if ( u8ErrorState == STD_TYPES_OK )
			{
				bit = GET_BIT(data, 7);
				u8ErrorState = DIO_u8SetPinData(D7_PORT,D7_PIN,bit);
			}
			if ( u8ErrorState == STD_TYPES_OK )
			{
				u8ErrorState = DIO_u8SetPinData(RS_PORT,RS_PIN,HIGH);
			}
			if ( u8ErrorState == STD_TYPES_OK )
			{
				u8ErrorState = DIO_u8SetPinData(RW_PORT,RW_PIN,LOW);
			}
			if ( u8ErrorState == STD_TYPES_OK )
			{
				u8ErrorState = DIO_u8SetPinData(E_PORT,E_PIN,HIGH);
			}
			if (( delay_finished ) && ( u8ErrorState == STD_TYPES_OK ))
			{
				u8ErrorState = TIMER2_u8ISRDelay_ms(3,Change_LCD_State);
				delay_finished = LOW ;
			}
			break ;
		}
		case SECOND_NIBBLE :
		{
			if ( u8ErrorState == STD_TYPES_OK )
			{
				bit = GET_BIT(data, 0);
				u8ErrorState = DIO_u8SetPinData(D4_PORT,D4_PIN,bit);
			}
			if ( u8ErrorState == STD_TYPES_OK )
			{
				bit = GET_BIT(data, 1);
				u8ErrorState = DIO_u8SetPinData(D5_PORT,D5_PIN,bit);
			}
			if ( u8ErrorState == STD_TYPES_OK )
			{
				bit = GET_BIT(data, 2);
				u8ErrorState = DIO_u8SetPinData(D6_PORT,D6_PIN,bit);
			}
			if ( u8ErrorState == STD_TYPES_OK )
			{
				bit = GET_BIT(data, 3);
				u8ErrorState = DIO_u8SetPinData(D7_PORT,D7_PIN,bit);
			}
			if ( u8ErrorState == STD_TYPES_OK )
			{
				u8ErrorState = DIO_u8SetPinData(RS_PORT,RS_PIN,HIGH);
			}
			if ( u8ErrorState == STD_TYPES_OK )
			{
				u8ErrorState = DIO_u8SetPinData(RW_PORT,RW_PIN,LOW);
			}
			if ( u8ErrorState == STD_TYPES_OK )
			{
				u8ErrorState = DIO_u8SetPinData(E_PORT,E_PIN,HIGH);
			}
			if (( delay_finished ) && ( u8ErrorState == STD_TYPES_OK ))
			{
				u8ErrorState = TIMER2_u8ISRDelay_ms(3,Change_LCD_State);
				delay_finished = LOW ;
			}
			break;
		}
		case FINISHED :
		{
			if (( delay_finished ) && ( u8ErrorState == STD_TYPES_OK ))
			{
				u8ErrorState = TIMER2_u8ISRDelay_ms(1,Change_LCD_State);
				delay_finished = LOW ;
				u8ErrorState = FINISHED ;
			}
			break;
		}
	}
	return u8ErrorState ;
}

uint8_t LCD_u8SendString(uint8_t *str)
{
	uint8_t u8ErrorState = STD_TYPES_OK;
	if(str == NULL)
	{
		u8ErrorState = LCD_SendString_Error ;
	}
	else
	{
		uint8_t* iterator = str ;
		while ( *iterator != '\0' && u8ErrorState == STD_TYPES_OK)
		{
			u8ErrorState = LCD_u8SendData( *iterator ) ;
			iterator++;
		}	
	}
	return u8ErrorState ;
}

uint8_t LCD_u8SendNumber(uint16_t num)
{
	uint16_t u16ConvertedNum = 1 ;
	uint8_t u8Errorstate = STD_TYPES_OK ;
	if ( num == 0 )
	{
		 if ( LCD_u8SendData('0') != STD_TYPES_OK )
				u8Errorstate = LCD_SendNumber_Error ;
	}
	else 
	{
		while ( num > 0 )
		{
			u16ConvertedNum = ( u16ConvertedNum	 * 10 ) + ( num % 10 );
			num /= 10 ;
		}
	
		while( u16ConvertedNum > 1 )
		{
			if ( LCD_u8SendData(( u16ConvertedNum % 10 ) + '0' ) != STD_TYPES_OK )
				u8Errorstate = LCD_SendNumber_Error ;
			u16ConvertedNum /= 10 ;
		}
	}
	return u8Errorstate ;
}

uint8_t LCD_u8SetPosition(uint8_t row, uint8_t col)
{	
	uint8_t u8Errorstate = STD_TYPES_OK;
	if(col > MAX_COL)
	{
		u8Errorstate = LCD_SetPosition_Error ;
	}
	else
	{
		switch (row)
		{
			case ROW1:
				col |= LCD_BEGIN_AT_FIRST_RAW ;
				break ;
			case ROW2:
				col |= LCD_BEGIN_AT_SECOND_RAW ;
				break;
			default:
				u8Errorstate = LCD_SetPosition_Error ;
				break;
		}
	}
	if ( u8Errorstate == STD_TYPES_OK )
	{
		u8Errorstate = LCD_u8SendCommand(col);
	}
	return u8Errorstate ;
}

uint8_t LCD_u8ClearScreen(void)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	if ( LCD_u8SendCommand(LCD_CLEAR) != STD_TYPES_OK )
			u8ErrorState = LCD_ClearScreen_Error ;
			
	return u8ErrorState ;
}

uint8_t LCD_u8MoveCursorLeft(void)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	if ( LCD_u8SendCommand(LCD_MOVE_CURSOR_LEFT) != STD_TYPES_OK )
			u8ErrorState = LCD_MoveCursorLeft_Error ;
	
	return u8ErrorState ;
}

uint8_t LCD_u8MoveCursorRight(void)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	if ( LCD_u8SendCommand(LCD_MOVE_CURSOR_RIGHT) != STD_TYPES_OK )
			u8ErrorState = LCD_MoveCursorLeft_Error ;

	return u8ErrorState ;	
}

void Change_LCD_State(void)
{
	switch ( LCD_State )
	{
		case FIRST_NIBBLE :
			LCD_State = SECOND_NIBBLE ;
			delay_finished = HIGH ;
			DIO_u8SetPinData(E_PORT,E_PIN,LOW);
			break;
		case SECOND_NIBBLE :
			LCD_State = FINISHED ;
			delay_finished = HIGH ;
			DIO_u8SetPinData(E_PORT,E_PIN,LOW);
			break;
		case FINISHED :
			LCD_State = FIRST_NIBBLE ;
			delay_finished = HIGH ;
			TIMER2_u8Stop();
			break;
	}
	
}