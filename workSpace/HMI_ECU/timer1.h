/*
 * 	timer1.h
 *	Description: header file for timer 1 driver
 *  Created on: Mar 10, 2024
 *  Author: AbdElRahman Khalifa
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include"standard_types.h"

typedef enum{
	TIMER1_FRQ1 = 1,
	TIMER1_FRQ8,
	TIMER1_FRQ64,
	TIMER1_FRQ256,
	TIMER1_FRQ1024
}Timer1_Prescaler;

typedef enum{
	TIMER1_CTC,
	TIMER1_NORMAL
}Timer1_Mode;

typedef struct {
	uint16 initial_value;
	uint16 compare_value;
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
}Timer1_ConfigType;

/*
 * Function to initialize the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Function to disable the Timer1
 */
void Timer1_deInit(void);

/*
 * Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
