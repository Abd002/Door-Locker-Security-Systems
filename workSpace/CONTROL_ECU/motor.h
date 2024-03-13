/*
 * 	motor.h
 *	Description: DC motor driver header file
 *  Created on: Feb 19, 2024
 *  Author: AbdElRahman Khalifa
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include"standard_types.h"

#define MOTOR_EN_PORT_ID 	PORTB_ID
#define MOTOR_EN_PIN_ID 	PIN3_ID

#define MOTOR_IN1_PORT_ID 	PORTB_ID
#define MOTOR_IN1_PIN_ID 	PIN0_ID

#define MOTOR_IN2_PORT_ID 	PORTB_ID
#define MOTOR_IN2_PIN_ID 	PIN1_ID

typedef enum{
	STOP,CW,ACW
}DcMotor_State;


/* 	Description
 * 	-The Function responsible for setup the direction for the two
 *			motor pins through the GPIO driver.
 *	-Stop at the DC-Motor at the beginning through the GPIO driver
*/
void DcMotor_Init(void);

/*
 * 	Description:
 * 	-The function responsible for rotate the DC Motor CW/ or A-CW or
 *			stop the motor based on the state input state value.
 * 	-Send the required duty cycle to the PWM driver based on the
 *			required speed value.
*/
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* MOTOR_H_ */
