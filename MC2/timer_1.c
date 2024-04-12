 /******************************************************************************
 *
 * Module: Timer 1
 *
 * File Name: timer1.c
 *
 * Description: Source file for Timer 1 driver
 *
 *******************************************************************************/

#include "timer_1.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
volatile uint8 g_key_num;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)();
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the Timer driver
 */

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCNT1 = Config_Ptr->initial_value;		/* Set timer1 initial */
	TCCR1A = (1<<FOC1A);
	TCCR1B = ((Config_Ptr->prescaler)&0x0007);
	if(Config_Ptr->mode == CTC)
	{
		OCR1A = Config_Ptr->compare_value;
		TIMSK |= (1<<OCIE1A);
		TCCR1B |= (1<<WGM12);
	}
	else if(Config_Ptr->mode == Normal)
	{
		TIMSK |= (1<<TOIE1);
	}
}

/*
 * Description:
 * Function to disable the Timer1
 */

void Timer1_deInit(void)
{
	TCCR1B &= 0xF8; /* No clock to disable the timer */
	g_callBackPtr = NULL_PTR; /* Reset the global pointer value */
}

/*
 * Description:
 * Function to set the Call Back function address
 */

void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}


