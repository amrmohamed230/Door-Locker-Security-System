 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the Buzzer driver
 *
 *******************************************************************************/

#include "buzzer.h"

/*******************************************************************************
 *                      Functions Definition                                   *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction for the buzzer pin as output pin through the GPIO driver
 * Turn off the buzzer through the GPIO.
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_Port, BUZZER_Pin, PIN_OUTPUT);
	GPIO_writePin(BUZZER_Port, BUZZER_Pin, LOGIC_LOW);
}

/*
 * Description :
 * Function to enable the Buzzer through the GPIO
 */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_Port, BUZZER_Pin, LOGIC_HIGH);
}

/*
 * Description :
 * Function to disable the Buzzer through the GPIO
 */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_Port, BUZZER_Pin, LOGIC_LOW);
}

