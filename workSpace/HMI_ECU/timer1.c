/*
 * 	timer1.h
 *	Description: source file for timer 1 driver
 *  Created on: Mar 10, 2024
 *  Author: AbdElRahman Khalifa
 */


#include"timer1.h"
#include"common_macros.h"
#include<avr/io.h>
#include<avr/interrupt.h>

volatile static void (*g_ptr)(void)=NULL;

ISR(TIMER1_COMPA_vect){
	if(g_ptr!=NULL)
		g_ptr();
}

ISR(TIMER1_OVF_vect){
	if(g_ptr!=NULL)
		g_ptr();
}

/*
 * Function to initialize the Timer driver
 */
void Timer1_init(const Timer1_ConfigType *Config_Ptr) {
	/* non PWM mode */
	TCCR1A = (1 << FOC1A) | (1 << FOC1B);

	/* clear modes */
	TCCR1B &= ~(3 << WGM12);

	/* required mode ctc or normal mode */
	if (Config_Ptr->mode == TIMER1_CTC) {
		OCR1A = Config_Ptr->compare_value;
		SET_BIT(TCCR1B, WGM12);
		SET_BIT(TIMSK, OCIE1A);
	}
	/* set the initial counter for timer */
	TCNT1 = Config_Ptr->initial_value;

	/* configure timer 1 prescaler and start it  */
	TCCR1B = (TCCR1B & 0xf8) | (Config_Ptr->prescaler);

}

/*
 * Function to disable the Timer1
 */
void Timer1_deInit(void){
	TCCR1A = 0;
	TCCR1B &= ~(3 << WGM12);
	TCCR1B &= 0xf8;
}

/*
 * Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void)){
	g_ptr=a_ptr;
}
