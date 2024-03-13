/*
 * 	motor.c
 *	Description: DC motor driver source code
 *  Created on: Feb 19, 2024
 *  Author: AbdElRahman Khalifa
 */


#include"motor.h"
#include"gpio.h"
#include"pwm.h"

/* 	Description
 * 	-The Function responsible for setup the direction for the two
 *			motor pins through the GPIO driver.
 *	-Stop at the DC-Motor at the beginning through the GPIO driver
*/
void DcMotor_Init(void){
	/* configuration of IN1 and IN2 pins as output pins */
	GPIO_setupPinDirection(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, PIN_OUTPUT);

	/* stop the motor */
	GPIO_writePin(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
}

/*
 * 	Description:
 * 	-The function responsible for rotate the DC Motor CW/ or A-CW or
 *			stop the motor based on the state input state value.
 * 	-Send the required duty cycle to the PWM driver based on the
 *			required speed value.
*/
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	PWM_Timer0_Start(speed);
	if(state==CW){
		GPIO_writePin(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
	}else if(state==ACW){
		GPIO_writePin(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_HIGH);
	}else {
		GPIO_writePin(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
	}
}
