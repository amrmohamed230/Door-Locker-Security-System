 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: motor.h
 *
 * Description: Header file for the DC Motor driver
 *
 *
 *******************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"
#include "gpio.h"
#include "my_pwm.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MOTOR_PORT PORTA_ID
#define MOTOR_IN1 PIN0_ID
#define MOTOR_IN2 PIN1_ID

/*******************************************************************************
 *                                Data Types                                   *
 *******************************************************************************/
typedef enum{
	CW,
	ACW,
	stop
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 */

void DcMotor_Init(void);

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */

void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* MOTOR_H_ */
