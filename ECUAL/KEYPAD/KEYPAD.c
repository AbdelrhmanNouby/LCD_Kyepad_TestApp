/*
 * KEYPAD.c
 *
 * Created: 1/19/2022
 * Author : Abdelrhman Elsawy
 */

#include "KEYPAD_interface.h"

uint8_t u8Stat = KEYPAD_NO_PRESSED_KEY ;

// function to initialize keypad 
uint8_t KEYPAD_u8Init(void)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	/*step 1 : config Col pins as output*/
	// check if DIO return Error
	if ( DIO_u8SetPinDirection(COL_PORT,COL_PIN0,OUTPUTPIN) != STD_TYPES_OK )
		u8ErrorState = KEYPAD_Init_Error ;
	else if ( DIO_u8SetPinDirection(COL_PORT,COL_PIN1,OUTPUTPIN) != STD_TYPES_OK )
		u8ErrorState = KEYPAD_Init_Error ;	
	else if ( DIO_u8SetPinDirection(COL_PORT,COL_PIN2,OUTPUTPIN) != STD_TYPES_OK )
		u8ErrorState = KEYPAD_Init_Error ;
	/*step 2 : config Rows pins as inputs , pull ups*/
	// check if DIO return Error
	else if ( DIO_u8SetPinDirection(ROW_PORT,ROW_PIN0,INPUTPIN_PULLUP) != STD_TYPES_OK )
		u8ErrorState = KEYPAD_Init_Error ;
	else if ( DIO_u8SetPinDirection(ROW_PORT,ROW_PIN1,INPUTPIN_PULLUP) != STD_TYPES_OK )
		u8ErrorState = KEYPAD_Init_Error ;
	else if ( DIO_u8SetPinDirection(ROW_PORT,ROW_PIN2,INPUTPIN_PULLUP) != STD_TYPES_OK )
		u8ErrorState = KEYPAD_Init_Error ;
	/*step 3 : Initialize Col pins -> HIGH*/
	// check if DIO return Error
	else if ( DIO_u8SetPinData(COL_PORT,COL_PIN0,HIGH) != STD_TYPES_OK )
		u8ErrorState = KEYPAD_Init_Error ;
	else if ( DIO_u8SetPinData(COL_PORT,COL_PIN1,HIGH) != STD_TYPES_OK )
		u8ErrorState = KEYPAD_Init_Error ;
	else if ( DIO_u8SetPinData(COL_PORT,COL_PIN2,HIGH) != STD_TYPES_OK )
		u8ErrorState = KEYPAD_Init_Error ;
	return u8ErrorState ;
}

// function to check which key is pressed 
uint8_t KEYPAD_u8GetPressedKey(uint8_t* KeyPressed)
{
	uint8_t u8ErrorState = STD_TYPES_OK;
	uint8_t u8ReturnVal ;
	uint8_t col_indx;
	uint8_t row_indx;
	uint8_t Pin_State;
	uint8_t u8KEYPAD_Arr[KEYPAD_ROWS][KEYPAD_COL] = KEYPAD_VALUES ;

	if ( KeyPressed != NULL )
	{
		switch ( u8Stat )
		{	
		  case KEYPAD_NO_PRESSED_KEY :
		  {
			for ( col_indx = COL_S ; col_indx < COL_E ; col_indx++ )
			{
				/*select column and output low*/
				if ( DIO_u8SetPinData( COL_PORT , col_indx , LOW ) != STD_TYPES_OK )				// check if DIO return Error 
					u8ErrorState = KEYPAD_GetPressedKey_Error ;
				for ( row_indx = ROW_S ; row_indx < ROW_E ; row_indx++ )
				{
					if ( DIO_u8GetPinData( ROW_PORT , row_indx , &Pin_State ) != STD_TYPES_OK )	    	// check if DIO return Error 
						u8ErrorState = KEYPAD_GetPressedKey_Error ;
					if( Pin_State == 0 ) /*if true -> PB is pressed*/
					{
						u8ReturnVal =  u8KEYPAD_Arr[row_indx-ROW_S][col_indx-COL_S];												
					}
				}
				if ( DIO_u8SetPinData( COL_PORT,col_indx , HIGH ) != STD_TYPES_OK )		        	// check if DIO return Error 
					u8ErrorState = KEYPAD_GetPressedKey_Error ;
			}
			if ( u8ReturnVal != KEYPAD_NO_PRESSED_KEY )
			{
				u8Stat = KEYPAD_DEBOUNCING ;
				if ( TIMER0_u8ISRDelay_ms( 10 , ChangeState ) != STD_TYPES_OK )						// check if TIMER0 return Error 
						u8ErrorState = KEYPAD_GetPressedKey_Error ;
			}
			break ; 
	 	  }
		  case KEYPAD_DEBOUNCING :
		  {
			uint8_t old_value = u8ReturnVal ; 
			for ( col_indx = COL_S ; col_indx < COL_E ; col_indx++ )
			{
				/*select column and output low*/
				if ( DIO_u8SetPinData( COL_PORT , col_indx , LOW ) != STD_TYPES_OK )				// check if DIO return Error
				u8ErrorState = KEYPAD_GetPressedKey_Error ;
				for ( row_indx = ROW_S ; row_indx < ROW_E ; row_indx++ )
				{
					if ( DIO_u8GetPinData( ROW_PORT , row_indx , &Pin_State ) != STD_TYPES_OK )	    	// check if DIO return Error
						u8ErrorState = KEYPAD_GetPressedKey_Error ;
					if( Pin_State == 0 ) /*if true -> PB is pressed*/
					{
						u8ReturnVal =  u8KEYPAD_Arr[row_indx-ROW_S][col_indx-COL_S];
					}
				}
				if ( DIO_u8SetPinData( COL_PORT,col_indx , HIGH ) != STD_TYPES_OK )		        	// check if DIO return Error
					u8ErrorState = KEYPAD_GetPressedKey_Error ;
			}	
			if (( u8Stat == KEYPAD_PRESSED ) && ( u8ReturnVal == old_value ))
			{
				*KeyPressed = u8ReturnVal;			
			}
			else
			{
				*KeyPressed = KEYPAD_DEBOUNCING ;
			}
			break ;
		  }
		  case KEYPAD_PRESSED :
		  {
			u8ReturnVal = KEYPAD_NO_PRESSED_KEY  ;
			for ( col_indx = COL_S ; col_indx < COL_E ; col_indx++ )
			{
				/*select column and output low*/
				if ( DIO_u8SetPinData( COL_PORT , col_indx , LOW ) != STD_TYPES_OK )				// check if DIO return Error
				u8ErrorState = KEYPAD_GetPressedKey_Error ;
				for ( row_indx = ROW_S ; row_indx < ROW_E ; row_indx++ )
				{
					if ( DIO_u8GetPinData( ROW_PORT , row_indx , &Pin_State ) != STD_TYPES_OK )	    	// check if DIO return Error
						u8ErrorState = KEYPAD_GetPressedKey_Error ;
					if( Pin_State == 0 ) /*if true -> PB is pressed*/
					{
						u8ReturnVal =  u8KEYPAD_Arr[row_indx-ROW_S][col_indx-COL_S];
					}
				}
				if ( DIO_u8SetPinData( COL_PORT,col_indx , HIGH ) != STD_TYPES_OK )		        	// check if DIO return Error
					u8ErrorState = KEYPAD_GetPressedKey_Error ;
			}	
			*KeyPressed = KEYPAD_NO_PRESSED_KEY ;
			if ( u8ReturnVal == KEYPAD_NO_PRESSED_KEY )
			{
				u8Stat = KEYPAD_NO_PRESSED_KEY ;
			}
			break ;
		  }
		  default :
			break ;
		}
	}
	else
	{
		u8ErrorState = KEYPAD_GetPressedKey_Error ;
	}
	return u8ErrorState;
}

void ChangeState (void)
{
	u8Stat = KEYPAD_PRESSED ;
}