/*
 * lcd.h
 *
 * Created on: Feb 10, 2024
 * Description : lcd driver header file
 * Author: AbdElRahman Khalifa
 */

#ifndef LCD_H_
#define LCD_H_

#include "standard_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* configuration of RS pin */
#define LCD_RS_PORT_ID PORTD_ID
#define LCD_RS_PIN_ID PIN2_ID

/* configuration of E pin */
#define LCD_E_PORT_ID PORTD_ID
#define LCD_E_PIN_ID PIN3_ID

/* configuration of DATA pins */
#define LCD_DATA_PORT_ID 		PORTC_ID
#define LCD_DATA_FIRST_PIN_ID 	PIN0_ID

/* configuration of lcd mode */
#define LCD_MODE LCD_TWO_LINES_EIGHT_BITS_MODE

/* some commands */
#define LCD_CLEAR_SCREEN 0x01
#define LCD_CURSOR_OFF 0x0c
#define LCD_TWO_LINES_EIGHT_BITS_MODE 0X38
#define LCD_TWO_LINES_FOUR_BITS_MODE 0X28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_FORCE_CURSOR 0x80



/*******************************************************************************
 *                               Functions Prototypes                              *
 *******************************************************************************/

/* send commands to lcd */
void LCD_sendCommand(uint8 command);

/* send data to lcd */
void LCD_displayCharacter(char data);

/* send data to lcd */
void LCD_init(void);

/* write string */
void LCD_displayString(const char *str_ptr);

/* move cursor base 0 */
void LCD_moveCursor(uint8 row, uint8 col);

/* print string in specific location */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char* str_ptr);

/* clear lcd screen */
void LCD_clearScreen(void);

/* display integer number on lcd */
void LCD_intgerToString(uint16 number);

#endif /* LCD_H_ */
