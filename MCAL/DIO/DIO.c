/*
 * DIO.c
 *
 * Created: 1/9/2022 10:18:29 PM
 *  Author: Abdelrhman Elsawy
 */ 

#include "../../LIB/Typedef.h"
#include "../../LIB/atmega32.h"
#include "../../LIB/BIT_Math.h"
#include "DIO.h"
#include "DIO_ERR_HANDLE.h"

// function to set direction of port 
uint8_t DIO_u8SetPortDirection( uint8_t port, uint8_t dir )
{
	uint8_t u8ErrorState = STD_TYPES_OK;
	switch (port)
	{
  	  case PORTA:
		switch (dir)
		{
			case INPUTPORT:
			// for input tristate mode ({DDRx, PORTx} = {0x00,0x00})
			DDRA_REG = PORT_LOW;
			SET_BIT(SFIOR_REG,PUD_BIT);
			break;
			
			case INPUTPORT_PULLUP:
			// for input PULLUP mode ( {DDRx, PORTx,PUD} =  {0b0,0x00,0xff} )
			CLR_BIT(SFIOR_REG,PUD_BIT);
			DDRA_REG =  PORT_LOW;
			PORTA_REG = PORT_HIGH;
			break;
			
			case OUTPUTPORT:
			// for input tristate mode ( DDRx = 0xff )
			DDRA_REG = PORT_HIGH;
			break
			;
			default:
			// If the input state is not one of the above cases return error state NOK
			u8ErrorState = SetPortDirection_Error ;
		}
		break;
		
  	  case PORTB:
		switch (dir)
		{
			case INPUTPORT:
			// for input tristate mode ({DDRx, PORTx} = {0x00,0x00})
			DDRB_REG = PORT_LOW;
			SET_BIT(SFIOR_REG,PUD_BIT);
			break;
			
			case INPUTPORT_PULLUP:
			// for input PULLUP mode ( {DDRx, PORTx,PUD} =  {0b0,0x00,0xff} )
			CLR_BIT(SFIOR_REG,PUD_BIT);
			DDRB_REG =  PORT_LOW;
			PORTB_REG = PORT_HIGH;
			break;
			
			case OUTPUTPORT:
			// for input tristate mode ( DDRx = 0xff )
			DDRB_REG = PORT_HIGH;
			break
			;
			default:
			// If the input state is not one of the above cases return error state NOK
			u8ErrorState = SetPortDirection_Error ;
		}
		break;
	
	  case PORTC:
		switch (dir)
		{
			case INPUTPORT:
			// for input tristate mode ({DDRx, PORTx} = {0x00,0x00})
			DDRC_REG = PORT_LOW;
			SET_BIT(SFIOR_REG,PUD_BIT);
			break;
			
			case INPUTPORT_PULLUP:
			// for input PULLUP mode ( {DDRx, PORTx,PUD} =  {0b0,0x00,0xff} )
			CLR_BIT(SFIOR_REG,PUD_BIT);
			DDRC_REG =  PORT_LOW;
			PORTC_REG = PORT_HIGH;
			break;
			
			case OUTPUTPORT:
			// for input tristate mode ( DDRx = 0xff )
			DDRC_REG = PORT_HIGH;
			break
			;
			default:
			// If the input state is not one of the above cases return error state NOK
			u8ErrorState = SetPortDirection_Error ;
		}
		break;
	
	  case PORTD:
		switch (dir)
		{
			case INPUTPORT:
			// for input tristate mode ({DDRx, PORTx} = {0x00,0x00})
			DDRD_REG = PORT_LOW;
			SET_BIT(SFIOR_REG,PUD_BIT);
			break;
			
			case INPUTPORT_PULLUP:
			// for input PULLUP mode ( {DDRx, PORTx,PUD} =  {0b0,0x00,0xff} )
			CLR_BIT(SFIOR_REG,PUD_BIT);
			DDRD_REG =  PORT_LOW;
			PORTD_REG = PORT_HIGH;
			break;
			
			case OUTPUTPORT:
			// for input tristate mode ( DDRx = 0xff )
			DDRD_REG = PORT_HIGH;
			break
			;
			default:
			// If the input state is not one of the above cases return error state NOK
			u8ErrorState = SetPortDirection_Error ;
		}
		break;
	
	  default:
	  // If the input port is not one of the above cases return error state NOK
      u8ErrorState = SetPortDirection_Error ;
	}
	return u8ErrorState;
}

// function to set direction of pin 
uint8_t DIO_u8SetPinDirection (uint8_t port ,uint8_t pin ,uint8_t dir)
{
  uint8_t u8ErrorState = STD_TYPES_OK;
  if ( pin <= PORT_PINS )
  {
	/*Check which port */
	switch ( port )
	{
		case PORTA:
			/*Check which Direction the user wants the pin to be in */
			switch (dir)
			{
				case INPUTPIN:
				// for input tristate mode ({DDxn, PORTxn} = 0b00)
				CLR_BIT(DDRA_REG,pin);
				CLR_BIT(PORTA_REG,pin);
				break;
				
		 		case INPUTPIN_PULLUP:
				// for input PULLUP mode ({DDxn, PORTxn,PUD} = 0b010)
				CLR_BIT(SFIOR_REG,PUD_BIT);
				CLR_BIT(DDRA_REG,pin);
				SET_BIT(PORTA_REG,pin);
				break;
				
				case OUTPUTPIN:
				// for OUTPUT mode ({DDxn, PORTxn} = 0b1x)
				SET_BIT(DDRA_REG,pin);
				break;
				
				default:
				// If the input state is not one of the above cases return error state NOK
				u8ErrorState= SetPinDirection_Error;
				}
				break;
			
		case PORTB:
			/*Check if the inputs are in the right range*/
			switch (dir)
			{
				case INPUTPIN:
				// for input tristate mode ({DDxn, PORTxn} = 0b00)
				CLR_BIT(DDRB_REG,pin);
				CLR_BIT(PORTB_REG,pin);
				break;
				
				case INPUTPIN_PULLUP:
				// for input PULLUP mode ({DDxn, PORTxn,PUD} = 0b010)
				CLR_BIT(SFIOR_REG,PUD_BIT);
				CLR_BIT(DDRB_REG,pin);
				SET_BIT(PORTB_REG,pin);
				break;
					
				case OUTPUTPIN:
				// for OUTPUT mode ({DDxn, PORTxn} = 0b1x)
				SET_BIT(DDRB_REG,pin);
				break;
					
				default:
				// If the input state is not one of the above cases return error state NOK
				u8ErrorState = SetPinDirection_Error;
			}
			break;
				
		case PORTC:
			switch (dir)
			{
				case INPUTPIN:
				// for input tristate mode ({DDxn, PORTxn} = 0b00)
				CLR_BIT(DDRC_REG,pin);
				CLR_BIT(PORTC_REG,pin);
				break;
		
				case INPUTPIN_PULLUP:
				// for input PULLUP mode ({DDxn, PORTxn,PUD} = 0b010)
				CLR_BIT(SFIOR_REG,PUD_BIT);
				CLR_BIT(DDRC_REG,pin);
				SET_BIT(PORTC_REG,pin);
				break;
				
				case OUTPUTPIN:
				// for OUTPUT mode ({DDxn, PORTxn} = 0b1x)
				SET_BIT(DDRC_REG,pin);
				break;
				
				default:	
				// If the input state is not one of the above cases return error state NOK
				u8ErrorState = SetPinDirection_Error ;
			}
			break;
			
		case PORTD:
			switch (dir)
			{
				case INPUTPIN:
				// for input tristate mode ({DDxn, PORTxn} = 0b00)
				CLR_BIT(DDRD_REG,pin);
				CLR_BIT(PORTA_REG,pin);
				break;
				
				case INPUTPIN_PULLUP:
				// for input PULLUP mode ({DDxn, PORTxn,PUD} = 0b010)
				CLR_BIT(SFIOR_REG,PUD_BIT);
				CLR_BIT(DDRD_REG,pin);
				SET_BIT(PORTD_REG,pin);
				break;
				
				case OUTPUTPIN:
				// for OUTPUT mode ({DDxn, PORTxn} = 0b1x)
				SET_BIT(DDRD_REG,pin);
				break;
				
				default:
				// If the input state is not one of the above cases return error state NOK
				u8ErrorState= SetPinDirection_Error ;
			}
			break;
			
			default:
			// If the input port is not one of the above cases return error state NOK
			u8ErrorState = SetPinDirection_Error ;
	}
  }
  else
  	u8ErrorState = SetPinDirection_Error ;
 	
  return u8ErrorState;
}

// function to assign value to port
uint8_t DIO_u8SetPortData(uint8_t port, uint8_t data)
{ 
	uint8_t u8ErrorState = STD_TYPES_OK ;
	switch(port)
	{
		// check which port and assign value to this port 
		case PORTA:
			PORTA_REG = data;
			break;
			
		case PORTB:
			PORTB_REG = data;
			break;
			
		case PORTC:
			PORTC_REG = data;
			break;
		
		case PORTD:
			PORTD_REG = data;
			break;
	
		default:
		u8ErrorState = SetPortData_Error ;
	}
	return u8ErrorState ;
}

// function to assign value to pin
uint8_t DIO_u8SetPinData(uint8_t port, uint8_t pin, uint8_t data)
{
  uint8_t u8ErrorState = STD_TYPES_OK ;
  // check if true pin number passed to the function 
  if ( pin <= PORT_PINS )
  {
	switch(port)
	{
		// check which port and assign value to pin in this port 
		case PORTA:
			if((data == LOW)||(data == HIGH))
				ASSIGN_BIT(PORTA_REG,pin,data);
				
			else
				u8ErrorState = SetPinData_Error ;	
			break;	
		
		case PORTB:
			if((data == LOW)||(data == HIGH))
				ASSIGN_BIT(PORTB_REG,pin,data);
		
			else
				u8ErrorState = SetPinData_Error ;	
			break;	
			
		case PORTC:
			if((data == LOW)||(data == HIGH))
				ASSIGN_BIT(PORTC_REG,pin,data);
			
			else
				u8ErrorState = SetPinData_Error ;	
			break;	
			
		case PORTD:
			if((data == LOW)||(data == HIGH))
				ASSIGN_BIT(PORTD_REG,pin,data);
		
			else
				u8ErrorState = SetPinData_Error ;	
			break;
		
		default:
			u8ErrorState = SetPinData_Error ;
	}
  }
  else
  {
	  u8ErrorState = SetPinData_Error ;	
  }
	return u8ErrorState ;
}

// function to read value on port
uint8_t DIO_u8GetPortData(uint8_t port, uint8_t* data)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	// check which port is selected and read data from it 
	switch(port)
	{
		case PORTA:
			*data = PINA_REG;
			break;
			
		case PORTB:
			*data = PINB_REG;
			break;
			
		case PORTC:
			*data = PINC_REG;
			break;
			
		case PORTD:
			*data = PIND_REG;
			break;
			
		default:
			u8ErrorState = GetPortData_Error ;
	}
	return u8ErrorState ;
}

// function to read value on pin
uint8_t DIO_u8GetPinData(uint8_t port, uint8_t pin, uint8_t* data)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
    // check if true pin number passed to the function 
	if ( pin <= PORT_PINS )
	{
		// check which port is selected and read data from it's pin  
		switch(port)
		{
			case PORTA:
				*data = GET_BIT(PINA_REG, pin);
				break;
			
			case PORTB:
				*data = GET_BIT(PINB_REG, pin);
				break;
			
			case PORTC:
				*data = GET_BIT(PINC_REG, pin);
				break;
			
			case PORTD:
				*data = GET_BIT(PIND_REG, pin);
				break;
			
			default:
				u8ErrorState =  GetPinData_Error ;
		}
	}
	else 
	{
		u8ErrorState =  GetPinData_Error ;	
	}
	return u8ErrorState ;
}

// function to toggle port state 
uint8_t DIO_u8TogglePortData(uint8_t port)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	// check which port is selected and read data from it
	switch(port)
	{
		case PORTA:
			PORTA_REG = ~PORTA_REG;
			break;
		
		case PORTB:
			PORTB_REG = ~PORTB_REG;
			break;
		
		case PORTC:
			PORTC_REG = ~PORTC_REG;
			break;
		
		case PORTD:
			PORTD_REG = ~PORTD_REG;
			break;
		
		default:
			u8ErrorState = TogglePortData_Error ;
	}
	return u8ErrorState ;
}

// function to toggle pin state 
uint8_t DIO_u8TogglePinData(uint8_t port, uint8_t pin)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
    // check if true pin number passed to the function 	
	if ( pin <= PORT_PINS )
	{
		// check which port is selected and toggle it's pin state 
		switch(port)
		{
			case PORTA:
				Toggle_BIT(PORTA_REG, pin);
				break;
			
			case PORTB:
				Toggle_BIT(PORTB_REG, pin);
				break;
			
			case PORTC:
				Toggle_BIT(PORTC_REG, pin);
				break;
		
			case PORTD:
				Toggle_BIT(PORTD_REG, pin);
				break;
			
			default:
				u8ErrorState =  TogglePinData_Error ;
		}
	}
	else 
	{
		u8ErrorState =  TogglePinData_Error ;	
	}
	return u8ErrorState ;
}
