/*
 * TIMER0.c
 *
 * Created: 1/15/2022 8:47:43 PM
 *  Author: Abdelrhman Elsawy
 */ 

#include "TIMER2.h"
#include "TIMER2_ERR_HANDLE.h"
#include "TIMER2_Config.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../LIB/atmega32.h"
#include "../../LIB/BIT_Math.h"

// initialize variables that used in ISR 
static uint16_t volatile compare;
static uint16_t volatile counter;
static uint8_t delay_state = DELAY_AVAILABLE ;
static void (*delayCallBack)(void);

// function to initialize timer0 
uint8_t TIMER2_u8Init (void)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;			
	CLR_BIT(TCCR2_REG, WGM20);			// Set compare mode
	SET_BIT(TCCR2_REG, WGM21);
	SET_BIT(SREG_REG, I_BIT);			// Enable interrupt
	SET_BIT(TIMSK_REG, OCIE2);
	TCNT2_REG = 0 ;	
	// error checking 
	if ( GET_BIT(TCCR2_REG, WGM20) == LOW && GET_BIT(TCCR2_REG, WGM21) == HIGH && GET_BIT(SREG_REG, I_BIT) == HIGH && GET_BIT(TIMSK_REG, OCIE2) == HIGH	)	
		u8ErrorState = STD_TYPES_OK ;
	else 
		u8ErrorState = Timer2_Init_Error ;
		
	return u8ErrorState ;   
}

// function to make timer0 start counting 
uint8_t TIMER2_u8Start (void)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	OCR2_REG = ( uint8_t )( F_CPU_E / PRESCALER );				// initiAL value of compare reg
	CLR_BIT(TCCR2_REG, CS20);									// set clock bits
	CLR_BIT(TCCR2_REG, CS21);
	SET_BIT(TCCR2_REG, CS22);
	// error checking 
	if ( GET_BIT(TCCR0_REG, CS20) == LOW && GET_BIT(TCCR0_REG, CS21) == LOW && GET_BIT(TCCR0_REG,CS22) == HIGH)
		u8ErrorState = STD_TYPES_OK ;
	else
		u8ErrorState = Timer2_Start_Error ;
		
	return u8ErrorState ;
}

// function to make timer0 stop counting 
uint8_t TIMER2_u8Stop (void)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	CLR_BIT(TCCR2_REG, CS20);					// stop clock 
	CLR_BIT(TCCR2_REG, CS21);
	CLR_BIT(TCCR2_REG, CS22);
	CLR_BIT(TIMSK_REG, OCIE2);					// disable interrupt 
	// error checking 
	if ( GET_BIT(TCCR0_REG, CS20) == LOW && GET_BIT(TCCR0_REG, CS21) == LOW && GET_BIT(TCCR0_REG,CS22) == LOW && GET_BIT(TIMSK_REG,OCIE2) == LOW )
		u8ErrorState = STD_TYPES_OK ;
	else
		u8ErrorState = Timer2_Start_Error ;
		
	return u8ErrorState ;
}

// function to make delay and call function after it 
uint8_t TIMER2_u8ISRDelay_ms(uint16_t delay, void (*fnCallBack)(void))
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	// error checking 
	if(delay_state == DELAY_UNAVAILABLE)
	{
		u8ErrorState = TIMER2_ISRDelay_Error ;
	}
	else
	{
		delay_state = DELAY_UNAVAILABLE ;		
		compare = delay;
		if(fnCallBack != NULL)
		{
			delayCallBack = fnCallBack;
			TIMER2_u8Init();
			TIMER2_u8Start();
			u8ErrorState = STD_TYPES_OK ;
		}
		else
		{
			u8ErrorState = TIMER2_ISRDelay_Error;
		}
	}
	return u8ErrorState ;
}

// function to make delay
uint8_t TIMER2_u8PollingDelay_ms(uint16_t delay)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	// error checking 
	if( delay_state == DELAY_UNAVAILABLE )
	{
		u8ErrorState = Timer2_PollingDelay_Error ;
	}
	else
	{
		delay_state = DELAY_UNAVAILABLE ;
		counter = 0;						
		compare = delay;
		TIMER2_u8Init();
		TIMER2_u8Start();					
		while (counter <= compare);			
		TIMER2_u8Stop();
		delay_state = DELAY_AVAILABLE;
		u8ErrorState = STD_TYPES_OK ;
	}
	return u8ErrorState ;
}

// ISR 
void __vector_4(void)
{
	counter++;            // increment counter to compare with delay 
	if(counter == compare && delayCallBack != NULL)				// if delay finished and there function address to call  
	{
		counter = 0;
		CLR_BIT(TIMSK_REG, OCIE2);							// reset interrupt 
		delay_state = DELAY_AVAILABLE ;
		delayCallBack();									// call the function 	
	}
}