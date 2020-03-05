/*
 * UART_BCM.c
 *
 * Created: 3/1/2020 7:40:16 PM
 * Author : ahmed
 */ 

#include "BCM.h"

#define BUFFER_LENGTH 10


uint8_t data[BUFFER_LENGTH]={0};


int main (void)
{
		/************************************/
		/*			SLAVE					*/
		/************************************/
	uint8_t iteration = 0;

	ENABLE_GINT;
	strUSART_Config_t USART_Config = {
		USART_NORMAL_SPEED,
		USART_RX_POLLING,
		USART_TX_POLLING,
		USART_UDR_EMPTY_POLLING,
		USART_RX_DISABLE,
		USART_TX_ENABLE,
		USART_ASYNC,
		USART_NO_PARITY,
		USART_1_STOP_BIT,
		USART_8_BIT_CHR
	};
	USART_Init(&USART_Config);
	BCM_Init();
	BCM_Receive (data);
	
	
	uint8_t status = START_SENDING;
	
	while(1)
	{
	    
		while (status != IDLE)
		{
			status = BCM_RxDispatch();
			
			
		}
		
		if (iteration<BUFFER_LENGTH)
		{
			
			USART_SendChar(data[iteration]);
			iteration++;
		}
	}
}

