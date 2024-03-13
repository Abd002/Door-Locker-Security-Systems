/*
 * gpio.h
 *
 *  Created on: Feb 10, 2024
 *  Description: this Header file for AVR GPIO
 *  Author: AbdElRahman Khalifa
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "standard_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NUM_OF_PORTS 4
#define NUM_OF_PINS_PER_PORT 8

#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3

#define PIN0_ID 0
#define PIN1_ID 1
#define PIN2_ID 2
#define PIN3_ID 3
#define PIN4_ID 4
#define PIN5_ID 5
#define PIN6_ID 6
#define PIN7_ID 7


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* enum for the statue of the pin */
typedef enum {
	PIN_INPUT, PIN_OUTPUT
} GPIO_PinDirectionType;

/* enum for the statue of the all pins of the port */
typedef enum {
	PORT_INPUT, PORT_OUTPUT = 0xff
} GPIO_PortDirectionType;


/*******************************************************************************
 *                               Functions Prototypes                              *
 *******************************************************************************/

/*
 * setup pin direction input/output pin
 * if the input port_number or pin_number are not valid do nothing
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num,
		GPIO_PinDirectionType direction);

/*
 * Write logic value on the required pin
 * if the input port_number or pin_number are not valid do nothing
 * if the pin is input, it will enable/disable internal pull-up
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*
 * read and return the value for the required pin, it should be logic-high or low
 * if the input port_number or pin_number are not valid will return LOGIC_LOW
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/*
 * Setuo the direction of the required port for all pins
 * if the direction value is PORT_INPUT all pins in this port should be input pins
 * if the direction value is PORT_OUTPUT all pins in this port should be output pins
 * if the input port_number or pin_number are not valid do nothing
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PinDirectionType direction);

/*
 * write the value on the required port
 * if any pin in the port is output pin the value will be written
 * if any pin in the port is input pin this will activate/deactivate the internal pull-up resistor
 * if the input port_number or pin_number are not valid do nothing
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/*
 * read and return the value of the required port
 * if the input port_number or pin_number are not valid return ZERO
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */
