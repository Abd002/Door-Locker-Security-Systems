/*
 * 	i2c.c
 *	Description: Twisted Pair interface driver source code
 *  Created on: Mar 4, 2024
 *  Author: AbdElRahman Khalifa
 */

#include "twi.h"

#include"common_macros.h"
#include<avr/io.h>

/*
 *	set TWPS to 00
 *	configure division factor for the bit rate generator
 *	give the address of slave
 *	enable module
 */
void TWI_init(const TWI_ConfigType* configuration) {
	/* set TWPS to 00 */
	TWSR = 0;

	/* configure division factor for the bit rate generator */
	TWBR = (uint8)((F_CPU/(float64)(2*configuration->bit_rate))-8);

	/* give the address of slave */
	TWAR = configuration->address;

	/* enable module */
	TWCR = (1 << TWEN);
}

/*
 * send start bit to start the communication
 */
void TWI_start(void) {
	/*
	 * clear interrupt flag
	 * send start bit
	 * enable module
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* waiting until (start bit is send successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT));
}

/*
 * send stop bit to end the communication
 */
void TWI_stop(void) {
	/*
	 * clear interrupt flag
	 * send end bit
	 * enable module
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	/* if u make polling here it will stuck because hardware willn't recieve any action after sending stop bit */
}

/*
 * send byte in SDA
 */
void TWI_writeByte(uint8 data) {
	/* write data into data register */
	TWDR = data;

	/*
	 * clear interrupt flag
	 * enable module
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);

	/* waiting until data send successfully */
	while (BIT_IS_CLEAR(TWCR, TWINT));
}

/*
 * -read one byte
 * -send ACK
 */
uint8 TWI_readByteWithACK(void) {
	uint8 data;

	/*
	 * clear interrupt flag
	 * enable module
	 */
	TWCR = (1 << TWINT)  | (1 << TWEN);

	/* waiting until we recieve byte */
	while (BIT_IS_CLEAR(TWCR, TWINT));

	data=TWDR;

	/* send ACK and enable TWI and clear the flag */
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);

	/* waiting until ACK send successfully */
	while (BIT_IS_CLEAR(TWCR, TWINT));

	return data;

}

/*
 * -read one byte
 * -send NACK to end the communication
 */
uint8 TWI_readByteWithNACK(void) {

	/*
	 * clear interrupt flag
	 * enable module
	 */
	TWCR = (1 << TWINT)  | (1 << TWEN);

	/* waiting until we recieve byte */
	while (BIT_IS_CLEAR(TWCR, TWINT));

	return TWDR;
}

/*
 * get the status to confirm the action
 */
uint8 TWI_getStatus(void) {
	return (TWSR & (0xf8));
}
