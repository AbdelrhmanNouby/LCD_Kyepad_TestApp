/*
 * UART.h
 *
 * Created: 1/24/2022
 * Author : Abdelrhman Elsawy
 */

#ifndef UART_H_
#define UART_H_

#include "UART_prv.h"
#include "UART_config.h"
#include "UART_ERR_HANDLE.h"
#include "../../LIB/atmega32.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/Typedef.h"

uint8_t UART_u8Init(void);
uint8_t UART_u8SendByte(uint8_t data);
uint8_t UART_u8ReceiveByte(uint8_t * data);
uint8_t UART_u8SendString(uint8_t *str);
uint8_t UART_u8ReceiveString(uint8_t *str);


#endif /* UART_H_ */