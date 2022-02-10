/*
 * TIMER0.h
 *
 * Created: 1/15/2022 8:47:31 PM
 *  Author: Abdelrhman Elsawy
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include "../../LIB/Typedef.h"
#include "TIMER0_ERR_HANDLE.h"
#include "TIMER0_Config.h"

/* TCCR0 */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0


/* SREG */
#define I_BIT 7

#define	DELAY_AVAILABLE     0
#define	DELAY_UNAVAILABLE   1

// function to initialize timer0 
uint8_t TIMER0_u8Init (void);

// function to make timer0 start counting 
uint8_t TIMER0_u8Start (void);

// function to make timer0 stop counting 
uint8_t TIMER0_u8Stop (void);

// function to make delay
uint8_t TIMER0_u8PollingDelay_ms(uint16_t delay);

// function to make delay and call function after it 
uint8_t TIMER0_u8ISRDelay_ms(uint16_t delay, void (*fnCallBack)(void));

// compare interrupt vector 
void __vector_10(void) __attribute__ ((signal, used));


#endif /* TIMER0_H_ */