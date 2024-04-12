/*
 *
 * File Name: CONTROL_Fn.h
 *
 * Description: Header file for CONTROL functions used in application layer
 *
 *******************************************************************************/

#ifndef ECU_FN_H_
#define ECU_FN_H_

#define READY_TO_COMM     0x10
#define READY_TO_RECEIVE  0x20
#define EEPROM_ADDRESS 	  0x0311
#define SAVE_PASS	  	  0x30
#define COMP_PASS	   	  0x40
#define OPEN_DOOR	  	  0x50
#define DONE_COMP	  	  0x60
/* STATUS */
#define DOOR_IS_OPENED 	  0x01
#define MATCH	  	   	  0x02
#define UNMATCH	 	 	  0x03
#define PASS_IS_SAVED  	  0x04
#define PASS_ERROR	  	  0x05

#include "gpio.h"
#include "timer_1.h"
#include "std_types.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "twi.h"
#include "motor.h"
#include "buzzer.h"
#include "my_pwm.h"
#include "external_eeprom.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
volatile uint8 ECU_receiveOp(void);
void ECU_sendOp(uint8 op);
void TIMER_DelaySec(uint8 sec);
void TIMER_secCount(void);
void CONTROL_CHOOSE_OP(void);
void CONTROL_savePassword(void);
void CONTROL_receivePassword(void);
void CONTROL_comparePassword(void);
void CONTROL_openDoor(void);
void CONTROL_error(void);

#endif /* CONTROL_FN_H_ */
