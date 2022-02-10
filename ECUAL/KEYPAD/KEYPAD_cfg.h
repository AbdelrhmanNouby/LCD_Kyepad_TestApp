/*
 * KEYPAD_cfg.h
 *
 * Created: 1/19/2022
 * Author : Abdelrhman Elsawy
 */

#ifndef ECUAL_KEYPAD_KEYPAD_CFG_H_
#define ECUAL_KEYPAD_KEYPAD_CFG_H_


// KEYPAD 3*3
#define KEYPAD_ROWS 3				
#define KEYPAD_COL  3

// MIN and MAX pin numbers for columns 
#define COL_S   5
#define COL_E   8

// MIN and MAX pin numbers for rows
#define ROW_S   2
#define ROW_E 5

// columns and rows ports 
#define COL_PORT  PORTC
#define ROW_PORT  PORTC

// columns pins 
#define COL_PIN0  PIN5
#define COL_PIN1  PIN6
#define COL_PIN2  PIN7

// rows pins 
#define ROW_PIN0  PIN2
#define ROW_PIN1  PIN3
#define ROW_PIN2  PIN4

// buttons values in keypad  
#define KEYPAD_VALUES	{{1,2,3},{4,5,6},{7,8,9}}


#endif /* ECUAL_KEYPAD_KEYPAD_CFG_H_ */
