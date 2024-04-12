 /******************************************************************************
 *
 * Module: Timer 1
 *
 * File Name: timer1.h
 *
 * Description: Header file for Timer 1 driver
 *
 *******************************************************************************/

#ifndef TIMER_1_H_
#define TIMER_1_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

typedef enum{
	N_Clk,
	N_PS,
	PS_8,
	PS_64,
	PS_256,
	PS_1024
}Timer1_Prescaler;

typedef enum{
	Normal,
	CTC
}Timer1_Mode;

typedef struct{
     uint16 initial_value;
     uint16 compare_value; /* it will be used in compare mode only. */
     Timer1_Prescaler prescaler;
     Timer1_Mode mode;
}Timer1_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the Timer driver
 */

void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description:
 * Function to disable the Timer1
 */

void Timer1_deInit(void);

/*
 * Description:
 * Function to set the Call Back function address
 */

void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER_1_H_ */
