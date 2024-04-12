/*
 *
 * File Name: HMI_Fn.h
 *
 * Description: Header file for HMI functions used in application layer
 *
 *******************************************************************************/

#ifndef HMI_FN_H_
#define HMI_FN_H_

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
#include "lcd.h"
#include "keypad.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
volatile uint8 ECU_receiveOp(void);
void ECU_sendOp(uint8 op);
void TIMER_DelaySec(uint8 sec);
void TIMER_secCount(void);
volatile uint8 HMI_enterPassword(uint8 count);
void HMI_sendPassword(void);
void HMI_createPassword(void);
void HMI_mainOptions(void);
void HMI_openDoor(void);
void HMI_error(void);

#endif /* HMI_FN_H_ */
