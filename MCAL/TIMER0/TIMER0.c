/*
 * TIMER0.c
 *
 * Created: 1/15/2022 8:47:43 PM
 *  Author: Abdelrhman Elsawy
 */ 

#include "TIMER0.h"
#include "TIMER0_ERR_HANDLE.h"
#include "TIMER0_Config.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../LIB/atmega32.h"
#include "../../LIB/BIT_Math.h"

// initialize variables that used in ISR 
static uint16_t volatile compare;
static uint16_t volatile counter;
static uint8_t delay_state = DELAY_AVAILABLE ;
static void (*delayCallBack)(void);

// function to initialize timer0 
uint8_t TIMER0_u8Init (void)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;			
	CLR_BIT(TCCR0_REG, WGM00);			// Set compare mode
	SET_BIT(TCCR0_REG, WGM01);
	SET_BIT(SREG_REG, I_BIT);			// Enable interrupt
	SET_BIT(TIMSK_REG, OCIE0);	
	// error checking 
	if ( GET_BIT(TCCR0_REG, WGM00) == LOW && GET_BIT(TCCR0_REG, WGM01) == HIGH && GET_BIT(SREG_REG, I_BIT) == HIGH && GET_BIT(TIMSK_REG, OCIE0) == HIGH	)	
		u8ErrorState = STD_TYPES_OK ;
	else 
		u8ErrorState = Timer0_Init_Error ;
		
	return u8ErrorState ;   
}

// function to make timer0 start counting 
uint8_t TIMER0_u8Start (void)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	OCR0_REG = ( uint8_t )( F_CPU_E / PRESCALER );				// initiAL value of compare reg
	SET_BIT(TCCR0_REG, CS00);									// set clock bits
	SET_BIT(TCCR0_REG, CS01);
	CLR_BIT(TCCR0_REG, CS02);
	// error checking 
	if ( GET_BIT(TCCR0_REG, CS00) == HIGH && GET_BIT(TCCR0_REG, CS01) == HIGH && GET_BIT(TCCR0_REG,CS02) == LOW)
		u8ErrorState = STD_TYPES_OK ;
	else
		u8ErrorState = Timer0_Start_Error ;
		
	return u8ErrorState ;
}

// function to make timer0 stop counting 
uint8_t TIMER0_u8Stop (void)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	CLR_BIT(TCCR0_REG, CS00);					// stop clock 
	CLR_BIT(TCCR0_REG, CS01);
	CLR_BIT(TCCR0_REG, CS02);
	CLR_BIT(TIMSK_REG, OCIE0);					// disable interrupt 
	// error checking 
	if ( GET_BIT(TCCR0_REG, CS00) == LOW && GET_BIT(TCCR0_REG, CS01) == LOW && GET_BIT(TCCR0_REG,CS02) == LOW && GET_BIT(TIMSK_REG,OCIE0) == LOW )
		u8ErrorState = STD_TYPES_OK ;
	else
		u8ErrorState = Timer0_Start_Error ;
		
	return u8ErrorState ;
}

// function to make delay and call function after it 
uint8_t TIMER0_u8ISRDelay_ms(uint16_t delay, void (*fnCallBack)(void))
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	// error checking 
	if(delay_state == DELAY_UNAVAILABLE)
	{
		u8ErrorState = TIMER0_ISRDelay_Error ;
	}
	else
	{
		delay_state = DELAY_UNAVAILABLE ;		
		compare = delay;
		if(fnCallBack != NULL)
		{
			delayCallBack = fnCallBack;
			TIMER0_u8Init();
			TIMER0_u8Start();
			u8ErrorState = STD_TYPES_OK ;
		}
		else
		{
			u8ErrorState = TIMER0_ISRDelay_Error;
		}
	}
	return u8ErrorState ;
}

// function to make delay
uint8_t TIMER0_u8PollingDelay_ms(uint16_t delay)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	// error checking 
	if( delay_state == DELAY_UNAVAILABLE )
	{
		u8ErrorState = Timer0_PollingDelay_Error ;
	}
	else
	{
		delay_state = DELAY_UNAVAILABLE ;
		counter = 0;						
		compare = delay;
		TIMER0_u8Init();
		TIMER0_u8Start();					
		while (counter <= compare);			
		TIMER0_u8Stop();
		delay_state = DELAY_AVAILABLE;
		u8ErrorState = STD_TYPES_OK ;
	}
	return u8ErrorState ;
}

// ISR 
void __vector_10(void)
{
	counter++;            // increment counter to compare with delay 
	if(counter == compare && delayCallBack != NULL)				// if delay finished and there function address to call  
	{
		counter = 0;
		CLR_BIT(TIMSK_REG, OCIE0);							// reset interrupt 
		delay_state = DELAY_AVAILABLE ;
		delayCallBack();									// call the function 
	}
}