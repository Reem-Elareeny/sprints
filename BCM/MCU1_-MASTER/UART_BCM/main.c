/*
 * UART_BCM.c
 *
 * Created: 3/1/2020 7:40:16 PM
 * Author : ahmed
 */ 

#include "BCM.h"

#define BUFFER_LENGTH 10


uint8_t data[BUFFER_LENGTH] = {0};

int main (void)
{
/************************************/
/*					MASTER					*/
/************************************/

	uint8_t iteration = 0;
	uint8_t u8_current_data = 0;

	strUSART_Config_t USART_Config = {
		USART_NORMAL_SPEED,
		USART_RX_POLLING,
		USART_TX_POLLING,
		USART_UDR_EMPTY_POLLING,
		USART_RX_ENABLE,
		USART_TX_ENABLE,
		USART_ASYNC,
		USART_NO_PARITY,
		USART_1_STOP_BIT,
		USART_8_BIT_CHR
	};

	ENABLE_GINT;
	USART_Init(&USART_Config);
	BCM_Init();
 	BCM_Send (data , BUFFER_LENGTH);
 	
	 
	while(1)
	{
		if (iteration<BUFFER_LENGTH)
		{
			
			USART_ReceiveChar(&u8_current_data);
			data[iteration] = u8_current_data;
			
			iteration++;
			
		}
		else
		{
			BCM_TxDispatch();
		}
		
	}
}

