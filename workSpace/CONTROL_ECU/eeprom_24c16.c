/*
 * 	eeprom_24c16.c
 *	Description: source file for EEPROM 24C16 driver
 *  Created on: Mar 4, 2024
 *  Author: AbdElRahman Khalifa
 */

#include"eeprom_24c16.h"
#include"twi.h"

/*
 * write one byte into specific address to External EEPROM using TWI
 * single meesage
 */
uint8 EEPROM_writeByte(uint16 address, uint8 *data) {
	uint8 i;
	/* first take the control of TWI drive */
	TWI_start();
	if (TWI_getStatus() != TWI_START)
		return EEPROM_ERROR;

	/*
	 * send the address of slave ->EEPROM
	 * send last 3 bits of address
	 * write mode
	*/
	TWI_writeByte((0xa0) | ((address >> 7) & (0x0e)));
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return EEPROM_ERROR;

	/* send data contain last bits of the address */
	TWI_writeByte((uint8)address);
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return EEPROM_ERROR;

	/* send data to EEPROM */
	for(i=0;i<5;i++){
		TWI_writeByte(data[i]);
	}

	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return EEPROM_ERROR;

	/* Stop the communication */
	TWI_stop();

	return EEPROM_SUCCESS;
}

/*
 * read one byte from specific address at External EEPROM using TWI
 * combined message
 */
uint8 EEPROM_readByte(uint16 address, uint8 *data) {
	/* first take the control of TWI drive */
	TWI_start();
	if (TWI_getStatus() != TWI_START)
		return EEPROM_ERROR;

	/*
	 * send the address of slave ->EEPROM
	 * send last 3 bits of address
	 * write mode
	 */
	TWI_writeByte((0xa0) | ((address >> 7) & (0x0e)));
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return EEPROM_ERROR;

	/* send data contain last bits of the address */
	TWI_writeByte((uint8)address);
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return EEPROM_ERROR;

	/* repeated start */
	TWI_start();

	/*
	 * send the address of slave ->EEPROM
	 * send last 3 bits of address
	 * read mode
	 */
	TWI_writeByte((0xa1) | ((address >> 7) & (0x0e)));
	if (TWI_getStatus() != TWI_MR_SLA_R_ACK)
		return EEPROM_ERROR;

	/* read data */
	*data = TWI_readByteWithNACK();

	if (TWI_getStatus() != TWI_MR_DATA_NACK)
		return EEPROM_ERROR;

	TWI_stop();

	return EEPROM_SUCCESS;
}
