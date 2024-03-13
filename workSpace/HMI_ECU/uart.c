/*
 * 	uart.c
 *	Describtion: source file of UART
 *  Created on: Feb 24, 2024
 *  Author: AbdElRahman Khalifa
 */

#include"uart.h"
#include"common_macros.h"
#include<avr/io.h>
#include<avr/interrupt.h>

static volatile void (*g_ptr)(uint8)=0;

ISR(USART_RXC_vect){
	if(g_ptr!=0){
		g_ptr(UDR);
	}
}

/*
 * initialization for UART Driver
 * set RX interrupt or polling as req
 */
void UART_init(const UART_ConfigType *configuration) {
	UCSRA = 0;

	/* reduce the divisor of the baud rate divider from 16 to 8 */
	SET_BIT(UCSRA, U2X);

	/* set RX interrupt or polling as required */
	MAKE_BIT(UCSRB, RXCIE, configuration->RX_completeInerrupt);

	/* enable rx and tx */
	SET_BIT(UCSRB, RXEN);
	SET_BIT(UCSRB, TXEN);

	/* set this bit to write into UCSRC */
	SET_BIT(UCSRC, URSEL);

	/* set error parity as required */
	UCSRC = (UCSRC & 0xcf) | (configuration->parity << 4);

	/* set stop bit as required */
	MAKE_BIT(UCSRC, USBS, configuration->stop_bit);

	/* set data BITs */
	UCSRC = (UCSRC & 0xf9) | ((configuration->bit_data & 3) << 1);

	/* set baud rate as required */
	UBRRL=0;
	uint16 baudRate = F_CPU / (8UL * configuration->baud_rate) - 1;
	UBRRL=(baudRate&0x00ff);
	UBRRH=baudRate>>8;
}

/*
 * send data using UART serial communication
 */
void UART_sendByte(uint8 data) {
	while (BIT_IS_CLEAR(UCSRA, UDRE));
	UDR = data;
}

/*
 * recieve data form UART using polling method
 */
uint8 UART_recieveByte() {
	while (BIT_IS_CLEAR(UCSRA, RXC));
	SET_BIT(UCSRA,RXC);
	return UDR;
}

/*
 * send full string using UART
 * send hash # as indicator to the end of string
 */
void UART_sendString(const uint8 *str) {
	while (*str != '\0') {
		UART_sendByte(*str);
		str++;
	}
	UART_sendByte('#');
}

/*
 * recieve string using UART polling msethod
 * warning -> this function should be sync with the sender to avoid overwrite
 */
void UART_recieveString(uint8 *str) {
	do {
		*str = UART_recieveByte();
	} while (*str++ != '#');
	*(str - 1) = '\0';
}

/*
 * save the address of callback functiom
 */
void UART_setCallBack(void(*f_ptr)(uint8)){
	g_ptr=f_ptr;
}
