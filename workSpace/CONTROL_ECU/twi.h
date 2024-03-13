/*
 * 	i2c.h
 *	Description: Twisted Pair interface driver header file
 *  Created on: Mar 4, 2024
 *  Author: AbdElRahman Khalifa
 */

#ifndef TWI_H_
#define TWI_H_

#include"standard_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * atmega32 datasheet page 188, 185
 */

#define TWI_START 				0x08
#define TWI_REP_START 			0x10

#define TWI_MT_SLA_W_ACK 		0x18
#define TWI_MT_SLA_W_NACK 		0x20
#define TWI_MT_DATA_ACK 		0x28
#define TWI_MT_DATA_NACK 		0x30

#define TWI_ARBITRATION_LOST 	0x38

#define TWI_MR_SLA_R_ACK 		0x40
#define TWI_MR_SLA_R_NACK 		0x48
#define TWI_MR_DATA_ACK 		0x50
#define TWI_MR_DATA_NACK 		0x58

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef  uint32 TWI_BaudRate;
typedef  uint8 TWI_Address;

typedef struct {
	TWI_BaudRate bit_rate;
	TWI_Address address;
} TWI_ConfigType;

/*******************************************************************************
 *                               Functions Prototypes                          *
 *******************************************************************************/

/*
 *	set TWPS to 00
 *	configure division factor for the bit rate generator
 *	give the address of slave
 */
void TWI_init(const TWI_ConfigType*);

/*
 * send start bit to start the communication
 */
void TWI_start(void);

/*
 * send stop bit to end the communication
 */
void TWI_stop(void);

/*
 * send byte in SDA
 */
void TWI_writeByte(uint8 data);

/*
 * -read one byte
 * -send ACK
 */
uint8 TWI_readByteWithACK(void);

/*
 * -read one byte
 * -send NACK to end the communication
 */
uint8 TWI_readByteWithNACK(void);

/*
 * get the status to confirm the action
 */
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */
