/*
 * 	pwm.c
 *	Description: pwm driver source code
 *  Created on: Feb 19, 2024
 *  Author: AbdElRahman Khalifa
 */


#include"pwm.h"
#include"avr/io.h"
#include"gpio.h"

/*
 *
 * Description:
 * -The function responsible for trigger the Timer0 with the PWM Mode.
 * -Setup the PWM mode with Non-Inverting.
 * -Setup the prescaler with F_CPU/8.
 * -Setup the compare value based on the required input duty cycle
 * -Setup the direction for OC0 as output pin through the GPIO driver.
 * -The generated PWM signal frequency will be 500Hz to control the DC
 *		Motor speed.
*/
void PWM_Timer0_Start(uint8 duty_cycle){

	/*
	 * WGM01=WGM00=1 	fast PWM
	 * COM01=1 			(nin-inverting mode)
	 * CS01=1			Setup the prescaler with F_CPU/8.
	 */

	TCCR0 =(1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS01);

	/* configure oc0 as output pin */
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);

	/* setup the speed of motor  */
	OCR0=(duty_cycle/100.0)*255;
}
