 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: motor.c
 *
 * Description: Source file for the DC Motor driver
 *
 *
 *******************************************************************************/

#include "motor.h"

/*******************************************************************************
 *                            Functions Definition                             *
 *******************************************************************************/

/*
 * Description :
 * The Function responsible for setup the direction for DC motor pins through the GPIO driver.
 */

void DcMotor_Init(void)
{
	/* Setting Motor Pins to Output */
	GPIO_setupPinDirection(MOTOR_PORT,MOTOR_IN1,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT,MOTOR_IN2,PIN_OUTPUT);
	/* Setting Motor to stop at first */
	GPIO_writePin(MOTOR_PORT,MOTOR_IN1,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT,MOTOR_IN2,LOGIC_LOW);
}

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	PWM_Timer0_Start(speed);
	switch(state)
	{
	case CW:
		GPIO_writePin(MOTOR_PORT,MOTOR_IN1,LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT,MOTOR_IN2,LOGIC_LOW);
		break;
	case ACW:
		GPIO_writePin(MOTOR_PORT,MOTOR_IN1,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT,MOTOR_IN2,LOGIC_HIGH);
		break;
	case stop:
		GPIO_writePin(MOTOR_PORT,MOTOR_IN1,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT,MOTOR_IN2,LOGIC_LOW);
		break;
	}
}
