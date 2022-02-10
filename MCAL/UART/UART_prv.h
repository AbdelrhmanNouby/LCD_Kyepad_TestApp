/*
 * UART_prv.h
 *
 * Created: 1/24/2022
 * Author : Abdelrhman Elsawy
 */


#ifndef UART_PRV_H_
#define UART_PRV_H_

#include "../../LIB/atmega32.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/Typedef.h"

/*===================================================
 * UART Registers BITs
 *===================================================*/

/*UCSRA Register*/
#define RXC_BIT                 7 
#define TXC_BIT                 6
#define UDRE_BIT                5
#define FE_BIT                  4
#define DOR_BIT                 3  
#define PE_BIT                  2		  
#define U2x_BIT                 1
#define MPCM_BIT                0

/*UCSRB Register*/
#define RXCIE_BIT               7
#define TXCIE_BIT               6
#define UDRIE_BIT               5
#define RXEN_BIT                4
#define TXEN_BIT                3
#define UCSZ2_BIT               2
#define RXB8_BIT                1
#define TXB8_BIT                0	

/*UCSRC Register*/
#define URSEL_BIT               7
#define UMSEL_BIT               6
#define UPM1_BIT                5
#define UPM0_BIT                4
#define USBS_BIT                3
#define UCSZ1_BIT               2
#define UCSZ0_BIT               1
#define UCPOL_BIT               0

/*=========================================================
 * Config macros
 *=========================================================*/
#define UART_NO_PARITY			 0
#define UART_EVEN_PARITY         2
#define UART_ODD_PARITY          3

#define UART_1_STOP_BIT          0
#define UART_2_STOP_BIT          1

#define UART_5_BITS              0
#define UART_6_BITS              1
#define UART_7_BITS              2
#define UART_8_BITS              3
#define UART_9_BITS              7

// F_CPU 8 MHz
#define UART_BAUDRATE_2400       207
#define UART_BAUDRATE_4800       103
#define UART_BAUDRATE_9600       51


#endif /* UART_PRV_H_ */