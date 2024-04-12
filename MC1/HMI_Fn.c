/*
 *
 * File Name: HMI_Fn.c
 *
 * Description: Source file for HMI functions used in application layer
 *
 *******************************************************************************/
#include "HMI_Fn.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
volatile uint8 g_password[2][5];
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

volatile uint8 HMI_enterPassword(uint8 count)
{
	uint8 i, key_num, result = MATCH;
	if(count == 1)
	{
		LCD_clearScreen();
		LCD_displayString("Plz Enter Pass:");
		_delay_ms(30);
		LCD_moveCursor(1,0);
		for(i = 0; i < 5;)
		{
			key_num = KEYPAD_getPressedKey();
			if((key_num >= 0) && (key_num <= 9))
			{
				g_password[1][i] = key_num ;
				LCD_displayCharacter('*');
				++i;
			}
			_delay_ms(500);
		}
		while(KEYPAD_getPressedKey() != 13);
		_delay_ms(100);
	}
	else if (count == 2)
	{
		LCD_clearScreen();
		LCD_displayString("Plz Re-enter the");
		_delay_ms(20);
		LCD_moveCursor(1,0);
		LCD_displayString("same pass: ");
		_delay_ms(20);
		LCD_moveCursor(1,11);
		for(i = 0; i < 5;)
		{
			key_num = KEYPAD_getPressedKey();
			if((key_num >= 0) && (key_num <= 9))
			{
				g_password[2][i] = key_num ;
				LCD_displayCharacter('*');
				++i;
			}
			_delay_ms(500);
		}
		while(KEYPAD_getPressedKey() != 13);
		_delay_ms(100);
		for(i = 0; i < 5; i++)
		{
			if(g_password[1][i] != g_password[2][i])
			{
				result = UNMATCH;
			}
		}
	}
	return result;
}

void HMI_sendPassword(void)
{
	uint8 i;
	UART_sendByte(READY_TO_COMM);
	for(i = 0; i < 5; i++)
	{
		while(UART_recieveByte() != READY_TO_RECEIVE);
		UART_sendByte(g_password[1][i]);
	}
}

void HMI_createPassword(void)
{
	uint8 result;
	do{
		HMI_enterPassword(1);
		result = HMI_enterPassword(2);
		if(result == MATCH)
		{
			ECU_sendOp(SAVE_PASS);
			_delay_ms(20);
			HMI_sendPassword();
		}
	}while(result == UNMATCH);
	LCD_clearScreen();
	LCD_displayString("Password set!");
	_delay_ms(500);
	HMI_mainOptions();
}


void HMI_mainOptions(void)
{
	uint8 key_num, status, count = 1;
	LCD_clearScreen();
	LCD_displayString("+ : Open Door");
	_delay_ms(20);
	LCD_moveCursor(1,0);
	LCD_displayString("- : Change Pass");
	do{
		key_num = KEYPAD_getPressedKey();
		switch(key_num)
			{
			case '+':
				do{
					HMI_enterPassword(1);
					ECU_sendOp(COMP_PASS);
					_delay_ms(300);
					HMI_sendPassword();
					while(UART_recieveByte() != DONE_COMP);
					status = UART_recieveByte();
					if(status == MATCH)
					{
						count = 1;
						HMI_openDoor();
					}
					else if((count < 3) && (status == UNMATCH))
					{
						count++;
						LCD_clearScreen();
						LCD_displayString("Error! Try Again");
						_delay_ms(1000);
					}
					else if((count == 3) && (status == UNMATCH))
					{
						HMI_error();
					}
				}while((count <= 3) && (status == UNMATCH));
				count = 1;
				break;
			case '-':
				do{
					HMI_enterPassword(1);
					ECU_sendOp(COMP_PASS);
					_delay_ms(300);
					HMI_sendPassword();
					while(UART_recieveByte() != DONE_COMP);
					status = UART_recieveByte();
					if(status == MATCH)
					{
						count = 1;
						HMI_createPassword();
					}
					else if((count < 3) && (status == UNMATCH))
					{
						count++;
						LCD_clearScreen();
						LCD_displayString("Error! Try Again");
						_delay_ms(1000);
					}
					else if((count == 3) && (status == UNMATCH))
					{
						HMI_error();
					}
				}while((count <= 3) && (status == UNMATCH));
				count = 1;
				break;
			default:
				break;
			}
	}while(key_num == '+' || key_num == '-');

}


void HMI_openDoor(void)
{
	ECU_sendOp(OPEN_DOOR);
	LCD_clearScreen();
	LCD_displayString("Door is");
	LCD_moveCursor(1,0);
	LCD_displayString("Unlocking");
	TIMER_DelaySec(15);
	LCD_clearScreen();
	TIMER_DelaySec(3);
	LCD_displayString("Door is Locking");
	TIMER_DelaySec(15);
	LCD_clearScreen();
}

void HMI_error(void)
{
	ECU_sendOp(PASS_ERROR);
	LCD_clearScreen();
	LCD_displayString("Wrong Password!");
	TIMER_DelaySec(60);
	HMI_mainOptions();
}
