/*
 * keypad.c
 *
 *  Created on: Feb 12, 2024
 *  Description: this source file for KEYPAD
 *  Author: AbdElRahman Khalifa
 */

#include "keypad.h"
#include "gpio.h"
#include <util/delay.h>

/* configure all pins as input */
static void KEYPAD_init(void) {
	int i;
	/* pull up resistors */
	GPIO_writePort(PORTA_ID, PORT_OUTPUT);
	for (i = 0; i < KEYPAD_ROW_NUMBER; i++) {
		GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_FIRST_PIN_ID+i, PIN_INPUT);
	}
	for (i = 0; i < KEYPAD_ROW_NUMBER; i++) {
		GPIO_setupPinDirection(KEYPAD_COLUMN_PORT_ID, KEYPAD_COLUMN_FIRST_PIN_ID+i, PIN_INPUT);
	}
}

/* adjust key numbers for 4x3 keypad */
#if KEYPAD_COLUMN_NUMBER==3
#ifndef KEYPAD_STANDARD
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 number_pressed){
	uint8 value;
	switch(number_pressed){
	case 10:
		value='*';
		break;
	case 11:
		value=0;
		break;
	case 12:
		value='#';
		break;
	default:
		value=number_pressed;
		break;
	}
	return value;
}
#endif
#endif

/* adjust key numbers for 4x3 keypad */
#if KEYPAD_COLUMN_NUMBER==4
#ifndef KEYPAD_STANDARD
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 number_pressed){
	uint8 value;
	if (number_pressed % 4 == 0) {
		if (number_pressed == 4) {
			value = '/';
		} else if (number_pressed == 8) {
			value = '*';
		} else if (number_pressed == 12) {
			value = '-';
		} else {
			value = '+';
		}
	} else if (number_pressed == 13) {
		value = 'C';
	} else if (number_pressed == 14) {
		value = 0;
	} else if (number_pressed == 15) {
		value = '=';
	} else {
		value = (2 - (number_pressed / 4)) * 3 + number_pressed % 4;
	}
	return value;
}
#endif
#endif

/* get the keypad button pressed */
uint8 KEYPAD_getPressedKey(void) {
	int row, col;
	KEYPAD_init();
	while (1) {
		for (row = 0; row < KEYPAD_ROW_NUMBER; row++) {

			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_FIRST_PIN_ID+row, PIN_OUTPUT);
			GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_FIRST_PIN_ID+row, KEYPAD_PRESSED_LOGIC);

			for (col = 0; col < KEYPAD_COLUMN_NUMBER; col++) {
				if(GPIO_readPin(KEYPAD_COLUMN_PORT_ID, KEYPAD_COLUMN_FIRST_PIN_ID+col)==KEYPAD_PRESSED_LOGIC){

#ifndef KEYPAD_STANDARD
	#if KEYPAD_COLUMN_NUMBER==3
						return KEYPAD_4x3_adjustKeyNumber(row * KEYPAD_COLUMN_NUMBER + col + 1);
	#else
						return KEYPAD_4x4_adjustKeyNumber(row*KEYPAD_COLUMN_NUMBER+col+1);
	#endif
	#else
						return row*KEYPAD_COLUMN_NUMBER+col+1;
#endif
				}
			}

			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_FIRST_PIN_ID+row, PIN_INPUT);
			_delay_ms(5);
		}
	}

}



