/*
 * gpio.c
 *
 *  Created on: Feb 10, 2024
 *  Description: this source file contain AVR GPIO driver
 *  Author: AbdElRahman Khalifa
 */

#include"gpio.h"
#include"common_macros.h"
#include<avr/io.h>

/*
 * setup pin direction input/output pin
 * if the input port_number or pin_number are not valid do nothing
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num,
		GPIO_PinDirectionType direction) {
	/* if valid arguments */
	if (port_num >= 0 && port_num <= 3 && pin_num >= 0 && pin_num <= 7) {
		/* Choose which port we need to configure it */
		switch (port_num) {
		case 0:
			if (direction == PIN_INPUT) {
				CLEAR_BIT(DDRA, pin_num); /* clear this pit as it will be INPUT */
			} else {
				SET_BIT(DDRA, pin_num); /* Set this pit as it will be OUTPUT */
			}
			break;
		case 1:
			if (direction == PIN_INPUT) {
				CLEAR_BIT(DDRB, pin_num);
			} else {
				SET_BIT(DDRB, pin_num);
			}
			break;
		case 2:
			if (direction == PIN_INPUT) {
				CLEAR_BIT(DDRC, pin_num);
			} else {
				SET_BIT(DDRC, pin_num);
			}
			break;
		case 3:
			if (direction == PIN_INPUT) {
				CLEAR_BIT(DDRD, pin_num);
			} else {
				SET_BIT(DDRD, pin_num);
			}
			break;
		default:
			break;
		}
	}
	return;
}

/*
 * Write logic value on the required pin
 * if the input port_number or pin_number are not valid do nothing
 * if the pin is input, it will enable/disable internal pull-up
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value) {
	/* if valid arguments */
	if (port_num >= 0 && port_num <= 3 && pin_num >= 0 && pin_num <= 7) {
		/* Choose which port we need to write on it */
		switch (port_num) {
		case 0:
			if (value == LOGIC_LOW) {
				CLEAR_BIT(PORTA, pin_num); /* clear this pit as it will be low */
			} else {
				SET_BIT(PORTA, pin_num); /* Set this pit as it will be high/enable internal pull-up */
			}
			break;
		case 1:
			if (value == LOGIC_LOW) {
				CLEAR_BIT(PORTB, pin_num);
			} else {
				SET_BIT(PORTB, pin_num);
			}
			break;
		case 2:
			if (value == LOGIC_LOW) {
				CLEAR_BIT(PORTC, pin_num);
			} else {
				SET_BIT(PORTC, pin_num);
			}
			break;
		case 3:
			if (value == LOGIC_LOW) {
				CLEAR_BIT(PORTD, pin_num);
			} else {
				SET_BIT(PORTD, pin_num);
			}
			break;
		default:
			break;
		}
	}
	return;
}

/*
 * read and return the value for the required pin, it should be logic-high or low
 * if the input port_number or pin_number are not valid will return LOGIC_LOW
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num) {
	uint8 value;
	/* if valid arguments */
	if (port_num >= 0 && port_num <= 3 && pin_num >= 0 && pin_num <= 7) {
		/* Choose which port we need to read from it */
		switch (port_num) {
		case 0:
			value = GET_BIT(PINA, pin_num);
			break;
		case 1:
			value = GET_BIT(PINB, pin_num);
			break;
		case 2:
			value = GET_BIT(PINC, pin_num);
			break;
		case 3:
			value = GET_BIT(PIND, pin_num);
			break;
		default:
			break;
		}
	} else {
		value = 0;
	}

	return value;
}

/*
 * Setuo the direction of the required port for all pins
 * if the direction value is PORT_INPUT all pins in this port should be input pins
 * if the direction value is PORT_OUTPUT all pins in this port should be output pins
 * if the input port_number or pin_number are not valid do nothing
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PinDirectionType direction) {
	if (port_num >= 0 && port_num <= 3) {
		switch (port_num) {
		case 0:
			DDRA=direction;
			break;
		case 1:
			DDRB=direction;
			break;
		case 2:
			DDRC=direction;
			break;
		case 3:
			DDRD=direction;
			break;
		default:
			break;
		}
	}
	return;
}

/*
 * write the value on the required port
 * if any pin in the port is output pin the value will be written
 * if any pin in the port is input pin this will activate/deactivate the internal pull-up resistor
 * if the input port_number or pin_number are not valid do nothing
 */
void GPIO_writePort(uint8 port_num, uint8 value) {
	if (port_num >= 0 && port_num <= 3) {
		switch (port_num) {
		case 0:
			PORTA = value;
			break;
		case 1:
			PORTB = value;
			break;
		case 2:
			PORTC = value;
			break;
		case 3:
			PORTD = value;
			break;
		default:
			break;
		}
	}
	return;
}

/*
 * read and return the value of the required port
 * if the input port_number or pin_number are not valid return ZERO
 */

uint8 GPIO_readPort(uint8 port_num) {
	uint8 value;
	if (port_num >= 0 && port_num <= 3) {
		switch (port_num) {
		case 0:
			value = PINA;
			break;
		case 1:
			value = PINB;
			break;
		case 2:
			value = PINC;
			break;
		case 3:
			value = PIND;
			break;
		default:
			break;
		}
	} else {
		value = 0;
	}
	return value;
}
