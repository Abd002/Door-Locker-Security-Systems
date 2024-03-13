/*
 * 	uart.h
 *	Describtion: Header file of UART
 *  Created on: Feb 24, 2024
 *  Author: AbdElRahman Khalifa
 */

#ifndef UART_H_
#define UART_H_

#include"standard_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum {
	PARITY_DISABLE, EVEN_PARITY = 2, ODD_PARITY
} UART_Parity;

typedef enum {
	ONE_BIT, TWO_BIT
} UART_StopBit;

typedef enum {
	FIVE_BIT, SEX_BIT, SEVEN_BIT, EIGHT_BIT
} UART_BitData;

typedef enum {
	BAUD_RATE_2400 = 2400,
	BAUD_RATE_4800 = 4800,
	BAUD_RATE_9600 = 9600,
	BAUD_RATE_14400 = 14400
} UART_BaudRate;

typedef struct {
	InterruptMode RX_completeInerrupt;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BitData bit_data;
	UART_BaudRate baud_rate;

}  UART_ConfigType;

/*******************************************************************************
 *                               Functions Prototypes                          *
 *******************************************************************************/

/*
 * initialization for UART Driver
 *
 */
void UART_init(const UART_ConfigType*);

/*
 * send data using UART serial communication
 */
void UART_sendByte(uint8);

/*
 * recieve data form UART using polling method
 */
uint8 UART_recieveByte();

/*
 * send full string using UART
 * send hash # as indicator to the end of string
 */
void UART_sendString(const uint8 *str);

/*
 * recieve string using UART polling msethod
 * warning -> this function should be sync with the sender to avoid overwrite
 */
void UART_recieveString(uint8 *str);

/*
 * save the address of callback functiom
 */
void UART_setCallBack(void(*)(uint8));

#endif /* UART_H_ */
