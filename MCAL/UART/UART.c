/*
 * UART.c
 *
 * Created: 1/24/2022
 * Author : Abdelrhman Elsawy
 */

#include "UART.h"

/* 
 * Description : initialize UART Communication 
 * Arguments   : void
 * return      : UART_Init_Error or STD_TYPES_OK in uint8_t    
 */
uint8_t UART_u8Init()
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	/*Receive enable config*/
	SET_BIT(UCSRB_REG,RXEN_BIT);
	if ( GET_BIT(UCSRB_REG,RXEN_BIT) == 0 )	
		 u8ErrorState = UART_Init_Error ;
		 
	/*Send enable config*/
	SET_BIT(UCSRB_REG,TXEN_BIT);
	if ( GET_BIT(UCSRB_REG,TXEN_BIT) == 0 )
		u8ErrorState = UART_Init_Error ;
		 
	/*Load configuration values in UCSrC Register*/
	/*Set URSEL to access UCSRC Reg*/
	SET_BIT(UCSRC_REG,URSEL_BIT);
	if ( GET_BIT(UCSRB_REG,URSEL_BIT) == 0 )
		u8ErrorState = UART_Init_Error ;
		
	/*ASynchronization mode*/				  
	CLR_BIT(UCSRC_REG,UMSEL_BIT);
	if ( GET_BIT(UCSRB_REG,UMSEL_BIT) != 0 )
		u8ErrorState = UART_Init_Error ;
		
	/*Parity Mode config*/
	UCSRC_REG|=(UART_PARITY<<4);
		 
	/*Stop Bits config*/
	ASSIGN_BIT(UCSRC_REG,USBS_BIT,UART_STOP_BIT_NO);
		 
	/*Character size config*/
	if (UART_SYMPOL_SIZE != UART_9_BITS)
	{
		 /*config char size(5,6,7,8)*/
		 UCSRC_REG |= (UART_SYMPOL_SIZE<<1);
	}
	else if (UART_SYMPOL_SIZE == UART_9_BITS)
	{
		 /*9 bit Mode*/
		 UCSRC_REG |= (UART_8_BITS<<1);
		 SET_BIT(UCSRB_REG,UCSZ2_BIT);			 
	}
	/*end of char size check*/
			 
	/*Baud Rate Value Config*/
	// URSEL BIT must be 0 to can write on UBRR Register
	CLR_BIT(UCSRC_REG,URSEL_BIT);
	if ( GET_BIT(UCSRB_REG,URSEL_BIT) != 0 )
		u8ErrorState = UART_Init_Error ;
	// set the  baud rate 	
	UBRRH_REG = 0 ;
	UBRRL_REG = UART_BAUDRATE;
	
	return u8ErrorState ;
}

/* 
 * Description : Send character by UART Communication 
 * Arguments   : Char you need to send 
 * return      : UART_SendByte_Error or STD_TYPES_OK in uint8_t    
 */
uint8_t UART_u8SendByte(uint8_t data)
{
	uint8_t u8ErrorState ;
	/*wait while previous sending is complete*/
	while ( (GET_BIT(UCSRA_REG,UDRE_BIT)) == 0 );
	/*send byte*/
	UDR_REG = data ;
	if ( UDR_REG != data )
		u8ErrorState = UART_SendByte_Error ;
	return u8ErrorState ;
}

/* 
 * Description : Receive character by UART Communication 
 * Arguments   : pointer to Char to save the received char 
 * return      : UART_ReceiveByte_Error or STD_TYPES_OK in uint8_t    
 */
uint8_t UART_u8ReceiveByte(uint8_t * data)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	// pointer passed to function not equal NULL
	if ( data == NULL )
		u8ErrorState = UART_ReceiveByte_Error ;
	else
	{
		/*wait while previous transition is complete*/
		while ( (GET_BIT(UCSRA_REG,RXC_BIT)) == 0 );
		/*send byte*/
		*data = UDR_REG  ;
	}
	return u8ErrorState ;
}

/* 
 * Description : Receive character by UART Communication 
 * Arguments   : pointer to string you want to send it 
 * return      : UART_SendString_Error or STD_TYPES_OK in uint8_t    
 */
uint8_t UART_u8SendString(uint8_t *str)
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	// send characters until find the NULL
	while(*str != '\0')
	{
		// send character by charcter
		if ( UART_u8SendByte(*str) != STD_TYPES_OK )
			u8ErrorState = UART_SendString_Error ;
		str++;
	}
	return u8ErrorState ;
}

/* 
 * Description : Receive character by UART Communication 
 * Arguments   : pointer to string to save string in it  
 * return      : UART_ReceiveString_Error or STD_TYPES_OK in uint8_t    
 */
uint8_t UART_u8ReceiveString(uint8_t *str)
{
	uint8_t index = 0 ;
	uint8_t u8ErrorState = STD_TYPES_OK ;
	// receive the first byte 
	if ( UART_u8ReceiveByte(&str[index]) != STD_TYPES_OK )
		u8ErrorState = UART_ReceiveString_Error ;
	// receive byte by byte until find CR
	while(str[index] != 0x0D )						// enter terminator for terminal = 0x0D ( Carriage return )
	{
		index++;
		if ( UART_u8ReceiveByte(&str[index]) != STD_TYPES_OK )
			u8ErrorState = UART_ReceiveString_Error ;
	}
	str[index] = '\0';
	return u8ErrorState ;
}