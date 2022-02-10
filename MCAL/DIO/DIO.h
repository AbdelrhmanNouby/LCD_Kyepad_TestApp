/*
 * DIO.h
 *
 * Created: 1/9/2022 10:15:12 PM
 *  Author: Abdelrhman Elsawy
 */ 



#ifndef DIO_H_
#define DIO_H_

#include "../../LIB/Typedef.h"
#include "DIO_ERR_HANDLE.h"

#define HIGH 1
#define LOW  0
#define PORT_LOW 	0
#define PORT_HIGH  0xff

#define INPUTPIN 0
#define OUTPUTPIN 1
#define INPUTPIN_PULLUP	2
#define	INPUTPORT 0
#define OUTPUTPORT 1
#define INPUTPORT_PULLUP	2

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PORT_PINS 7 

// function to set direction of port 
uint8_t DIO_u8SetPortDirection( uint8_t port, uint8_t dir );

// function to set direction of pin
uint8_t DIO_u8SetPinDirection( uint8_t port, uint8_t pin, uint8_t dir);

// function to assign value to port
uint8_t DIO_u8SetPortData(uint8_t port, uint8_t data);

// function to assign value to pin 
uint8_t DIO_u8SetPinData(uint8_t port, uint8_t pin, uint8_t data);

// function to read value on port
uint8_t DIO_u8GetPortData(uint8_t port, uint8_t* data);

// function to read value on pin 
uint8_t DIO_u8GetPinData(uint8_t port, uint8_t pin, uint8_t* data);

// function to toggle port state 
uint8_t DIO_u8TogglePortData(uint8_t port);

// function to toggle pin state 
uint8_t DIO_u8TogglePinData(uint8_t port, uint8_t pin);

#endif /* DIO_H_ */
