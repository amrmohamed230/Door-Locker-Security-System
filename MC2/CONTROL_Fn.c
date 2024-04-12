/*
 *
 * File Name: CONTROL_Fn.c
 *
 * Description: Source file for CONTROL functions used in application layer
 *
 *******************************************************************************/
#include "CONTROL_Fn.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
volatile uint8 g_password[5];
volatile uint8 g_op;
volatile uint8 g_sec_count = 0;

volatile uint8 ECU_receiveOp(void)
{
	while(UART_recieveByte() != READY_TO_COMM);
	UART_sendByte(READY_TO_RECEIVE);
	return UART_recieveByte();
}

void ECU_sendOp(uint8 op)
{
	UART_sendByte(READY_TO_COMM);
	while(UART_recieveByte() != READY_TO_RECEIVE);
	UART_sendByte(op);
}

void TIMER_DelaySec(uint8 sec)
{
	Timer1_ConfigType TIMER1_Config = {0, 7812, PS_1024, CTC};
	Timer1_setCallBack(TIMER_secCount);
	Timer1_init(&TIMER1_Config);
	while(g_sec_count < sec);
	Timer1_deInit();
	g_sec_count = 0;
}

void TIMER_secCount(void)
{
	g_sec_count++;
}

void CONTROL_CHOOSE_OP(void)
{
	g_op = ECU_receiveOp();
	switch(g_op)
	{
	case SAVE_PASS:
		CONTROL_savePassword();
		break;
	case COMP_PASS:
		CONTROL_comparePassword();
		break;
	case OPEN_DOOR:
		CONTROL_openDoor();
		break;
	case PASS_ERROR:
		CONTROL_error();
		break;
	}
}

void CONTROL_receivePassword(void)
{
	uint8 i;
	while(UART_recieveByte() != READY_TO_COMM);
	for(i = 0; i < 5; i++)
	{
		UART_sendByte(READY_TO_RECEIVE);
		g_password[i] = UART_recieveByte();
	}
}

void CONTROL_savePassword(void)
{
	uint8 i;
	CONTROL_receivePassword();
	for(i = 0; i < 5; i++)
	{
		EEPROM_writeByte(EEPROM_ADDRESS+i, g_password[i]);
		_delay_ms(10);
	}
}

void CONTROL_comparePassword(void)
{
	uint8 i, status = MATCH, temp;
	CONTROL_receivePassword();
	for(i = 0; i < 5; i++)
	{
		EEPROM_readByte(EEPROM_ADDRESS+i, &temp);
		if(g_password[i] != temp)
		{
			status = UNMATCH;
			break;
		}
	}
	UART_sendByte(DONE_COMP);
	UART_sendByte(status);
}

void CONTROL_openDoor(void)
{
	DcMotor_Rotate(CW,100);
	GPIO_writePin(PORTD_ID,PIN7_ID,LOGIC_HIGH);
	TIMER_DelaySec(15);
	GPIO_writePin(PORTD_ID,PIN7_ID,LOGIC_LOW);
	DcMotor_Rotate(stop,0);
	TIMER_DelaySec(3);
	DcMotor_Rotate(ACW,100);
	TIMER_DelaySec(15);
	DcMotor_Rotate(stop,0);
}

void CONTROL_error(void)
{
	Buzzer_on();
	TIMER_DelaySec(60);
	Buzzer_off();
}
