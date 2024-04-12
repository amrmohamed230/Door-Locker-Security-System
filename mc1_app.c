/*
 * mc1_app.c
 * By: Amr Mohamed Yousef
 * Diploma Number: 83
 * Facebook Name: Amr Mohamed
 * =====================================================================================================================================
 */

#include "HMI_Fn.h"

int main(void)
{
	UART_ConfigType UART_Config = {eight_bit, even, one_bit, 9600};
	sei();
	LCD_init();
	UART_init(&UART_Config);
	HMI_createPassword();
	while(1);
}
