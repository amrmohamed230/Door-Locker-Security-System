/*
 * mc2_app.c
 * By: Amr Mohamed Yousef
 * Diploma Number: 83
 * Facebook Name: Amr Mohamed
 * ======================================================================================================================================
 */

#include "CONTROL_Fn.h"

int main(void)
{
	TWI_ConfigType TWI_Config = {10, 400};
	UART_ConfigType UART_Config = {eight_bit, even, one_bit, 9600};
	sei();
	TWI_init(&TWI_Config);
	Buzzer_init();
	DcMotor_Init();
	UART_init(&UART_Config);
	while(1)
	{
		CONTROL_CHOOSE_OP();
	}
}
