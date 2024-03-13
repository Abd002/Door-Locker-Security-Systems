/*
 * keypad.h
 *
 *  Created on: Feb 12, 2024
 *  Description: this header file for KEYPAD
 *  Author: AbdElRahman Khalifa
 */

#include "standard_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* if we use buttons */
//#define KEYPAD_STANDARD

/* KEYPAD cofiguration for numbers of rows and columns */
#define KEYPAD_ROW_NUMBER 		4
#define KEYPAD_COLUMN_NUMBER 	4

/* KEYPAD cofiguration for button logic */
#define KEYPAD_PRESSED_LOGIC 	LOGIC_LOW
#define KEYPAD_RELEASED_LOGIC 	LOGIC_HIGH

/* KEYPAD cofiguration for PORTS */
#define KEYPAD_ROW_PORT_ID 		PORTA_ID
#define KEYPAD_COLUMN_PORT_ID 	PORTA_ID

/* KEYPAD cofiguration for first pins */
#define KEYPAD_ROW_FIRST_PIN_ID PIN0_ID
#define KEYPAD_COLUMN_FIRST_PIN_ID PIN4_ID


/*******************************************************************************
 *                               Functions Prototypes                          *
 *******************************************************************************/
/* get the keypad button pressed */
uint8 KEYPAD_getPressedKey(void) ;
