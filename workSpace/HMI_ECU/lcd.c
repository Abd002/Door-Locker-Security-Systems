/*
 * lcd.c
 *
 *  Created on: Feb 10, 2024
 *  Description : lcd driver source file
 *  Author: AbdElRahman Khalifa
 */

#include"lcd.h"
#include"gpio.h"
#include"common_macros.h"
#include<util/delay.h>
#include<stdlib.h>

/* send data to lcd */
void LCD_init(void){
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);	/* configure Rs as output pin */
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);	/* configure E as output pin */

	/* INIT the mode of LCD & configure the output pins */
#if LCD_MODE==LCD_TWO_LINES_EIGHT_BITS_MODE
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PIN_OUTPUT);
#else
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+4, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+5, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+6, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+7, PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
#endif
	_delay_ms(20); 		  										/* LCD Power ON delay always > 15ms */
	LCD_sendCommand(LCD_MODE);									/* 2-lines + 8bit mode OR 2-lines +4bit mode */
	LCD_sendCommand(LCD_CLEAR_SCREEN);							/* clear screen */
	LCD_sendCommand(LCD_CURSOR_OFF);							/* cursor off */
}

/* send commands to lcd */
void LCD_sendCommand(uint8 command){
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);	/* RS=0 send command mode */
	_delay_ms(1); 												/* Tas delay */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);		/* E=1 from datasheet */
	_delay_ms(1); 												/* Tpw-Tdsw delay */

	/* send command using two modes */
#if LCD_MODE==LCD_TWO_LINES_EIGHT_BITS_MODE
	GPIO_writePort(LCD_DATA_PORT_ID, command);
#else
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+4, GET_BIT(command, 4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+5, GET_BIT(command, 5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+6, GET_BIT(command, 6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+7, GET_BIT(command, 7));

	_delay_ms(1); 												/* Tdsw */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);      /* E=0 from datasheet */
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);     /* E=0 from datasheet */
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+4, GET_BIT(command, 0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+5, GET_BIT(command, 1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+6, GET_BIT(command, 2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+7, GET_BIT(command, 3));
#endif
	_delay_ms(1); 												/* Tdsw */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);      /* E=0 from datasheet */
	_delay_ms(1); 												/* Th */
}

/* send data to lcd */
void LCD_displayCharacter(char data){
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);	/* RS=1 send data mode */
	_delay_ms(1); 												/* Tas delay */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);		/* E=1 from datasheet */
	_delay_ms(1); 												/* Tpw-Tdsw delay */

	/* send command using two modes */
#if LCD_MODE==LCD_TWO_LINES_EIGHT_BITS_MODE
	GPIO_writePort(LCD_DATA_PORT_ID, data);
#else
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+4, GET_BIT(data, 4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+5, GET_BIT(data, 5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+6, GET_BIT(data, 6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+7, GET_BIT(data, 7));

	_delay_ms(1); 												/* Tdsw */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);      /* E=0 from datasheet */
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);     /* E=0 from datasheet */
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+4, GET_BIT(data, 0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+5, GET_BIT(data, 1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+6, GET_BIT(data, 2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID+7, GET_BIT(data, 3));
#endif
	_delay_ms(1); 												/* Tdsw */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);      /* E=0 from datasheet */
	_delay_ms(1); 												/* Th */
}



/* write string */
void LCD_displayString(const char *str_ptr){
	while(*str_ptr != '\0'){
		LCD_displayCharacter(*str_ptr);
		str_ptr++;
	}
}

/* move cursor base 0 */
void LCD_moveCursor(uint8 row, uint8 col){
	uint8 location;
	switch(row){
	case 0:
		location=0x00+col;
		break;
	case 1:
		location=0x40+col;
		break;
	case 2:
		location=0x10+col;
		break;
	case 3:
		location=0x50+col;
		break;
	default:
		break;
	}
	LCD_sendCommand(location|LCD_FORCE_CURSOR);
}

/* print string in specific location */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char* str_ptr){
	LCD_moveCursor(row, col);
	LCD_displayString(str_ptr);
}

/* clear lcd screen */
void LCD_clearScreen(void){
	LCD_sendCommand(LCD_CLEAR_SCREEN);
}

/* display integer number on lcd */
void LCD_intgerToString(uint16 number){
	char buff[18];
	itoa(number, buff, 10);
	LCD_displayString(buff);
}
