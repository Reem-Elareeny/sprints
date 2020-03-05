/*
 * BCM.c
 *
 * Created: 3/2/2020 1:25:02 PM
 *  Author: ahmed
 */ 

#include "BCM.h"

#define BCM_ID							'1'
#define EIGHT_BITS_STEPS			 8

#define DISPATCHER_1ST_ROUND	 0
#define DISPATCHER_2ND_ROUND	 1
#define DISPATCHER_3RD_ROUND	 2



volatile uint8_t gu8_TXC_Flag = TRUE;
volatile uint8_t gu8_RXC_Flag = FALSE;


uint8_t gu8_FSM_Status = IDLE;

uint16_t gu16_NumberOfBytes = INITIAL_VALUE;

uint8_t *gpu8_PointerToBuffer = NULL;

strUSART_Config_t USART_Config;

strSPI_Config_t SPI_Config;


static void TX_SetFlag (void)
{
	gu8_TXC_Flag = TRUE;
}

static void RX_SetFlag (void)
{
	gu8_RXC_Flag = TRUE;
}

ERROR_STATUS BCM_Init()
{
	ERROR_STATUS ERR = E_OK;
	
	switch (BCM_Config.u8_SerialComType)
	{
		case UART:
			switch (BCM_Config.u8_SenderOrReceiver)
			{
				case SENDER:
				
					USART_Config.USART_SPEED = USART_NORMAL_SPEED;
					USART_Config.USART_RX_Interrupt = USART_RX_POLLING;
					USART_Config.USART_TX_Interrupt = USART_TX_INTERRUPT_ENABLE;
					USART_Config.USART_UDR_EmptyInterrupt =	USART_UDR_EMPTY_POLLING;
					USART_Config.USART_RX_EnableDisable = USART_RX_DISABLE;
					USART_Config.USART_TX_EnableDisable = USART_TX_ENABLE;
					USART_Config.USART_OperationMode = USART_ASYNC;
					USART_Config.USART_Parity = USART_NO_PARITY;
					USART_Config.USART_StopBitsNumber =	USART_1_STOP_BIT;
					USART_Config.USART_CharSize = USART_8_BIT_CHR;
					USART_Config.USART_UDRE_CBK= NULL;
					USART_Config.USART_TXC_CBK = TX_SetFlag;
					USART_Config.USART_RXC_CBK = NULL;
					
					USART_Init(&USART_Config);
					break;
				case RECEIVER:
					
					USART_Config.USART_SPEED = USART_NORMAL_SPEED;
					USART_Config.USART_RX_Interrupt = USART_RX_INTERRUPT_ENABLE;
					USART_Config.USART_TX_Interrupt = USART_TX_POLLING;
					USART_Config.USART_UDR_EmptyInterrupt =	USART_UDR_EMPTY_POLLING;
					USART_Config.USART_RX_EnableDisable = USART_RX_ENABLE;
					USART_Config.USART_TX_EnableDisable = USART_TX_DISABLE;
					USART_Config.USART_OperationMode = USART_ASYNC;
					USART_Config.USART_Parity =	USART_NO_PARITY;
					USART_Config.USART_StopBitsNumber = USART_1_STOP_BIT;
					USART_Config.USART_CharSize = USART_8_BIT_CHR;
					USART_Config.USART_UDRE_CBK = NULL;
					USART_Config.USART_TXC_CBK = NULL;
					USART_Config.USART_RXC_CBK = RX_SetFlag;
				
					USART_Init(&USART_Config);
					break;
					
				default:
					ERR = E_NOK;
					break;
			}
			
			break;
			
		case SPI:
			switch(BCM_Config.u8_SenderOrReceiver)
			{
				case SENDER:
					
					SPI_Config.u8_MasterSlaveSelect = SPI_MASTER_MODE;
					SPI_Config.u8_InterruptPollingMode = SPI_INTERRUPT;
					SPI_Config.u8_DataOrder = SPI_MSB_FIRST;
					SPI_Config.u8_ModeNumber = MODE_NUMBER0;
					SPI_Config.u8_ClockRate = SPI_FREQUENCY_DIVIDER_16;
					SPI_Config.u8_Speed = SPI_NORMAL_SPEED;
					SPI_Config.SPI_CBK = TX_SetFlag;
					
					SPI_Init(&SPI_Config);
					break;
					
				case RECEIVER:
				
					SPI_Config.u8_MasterSlaveSelect = SPI_SLAVE_MODE;
					SPI_Config.u8_InterruptPollingMode = SPI_INTERRUPT;
					SPI_Config.u8_DataOrder = SPI_MSB_FIRST;
					SPI_Config.u8_ModeNumber = MODE_NUMBER0;
					SPI_Config.u8_ClockRate = SPI_FREQUENCY_DIVIDER_16;
					SPI_Config.u8_Speed = SPI_NORMAL_SPEED;
					SPI_Config.SPI_CBK = RX_SetFlag;
					
					SPI_Init(&SPI_Config);
					break;
					
				default:
					ERR = E_NOK;
					break;
			}
			
			break;
			
		default:
			ERR = E_NOK;
			break;
	
			}
	return ERR;
}


ERROR_STATUS BCM_TxDispatch()
{
	
	ERROR_STATUS ERR = E_OK;
	static uint16_t u16_DataBufferIndex = INITIAL_VALUE;
	static uint8_t u8_CHKSUM = INITIAL_VALUE;
	static uint8_t u8_DispatchEnteranceCounter = INITIAL_VALUE;
	
	uint8_t u8_NumberOfBytesLSBs = gu16_NumberOfBytes;
	uint8_t u8_NumberOfBytesMSBs = (gu16_NumberOfBytes >> EIGHT_BITS_STEPS);
	
	switch (BCM_Config.u8_SerialComType)
	{
		case UART:
			switch(BCM_Config.u8_SenderOrReceiver)
			{
				case SENDER:
					if(gu8_TXC_Flag)
					{
						gu8_TXC_Flag = FALSE;
						switch (gu8_FSM_Status)
						{
							case IDLE:
								switch(u8_DispatchEnteranceCounter)
								{
									case DISPATCHER_1ST_ROUND: 
										USART_SendChar(BCM_ID);
										u8_DispatchEnteranceCounter = DISPATCHER_2ND_ROUND;
										break;
										
									case DISPATCHER_2ND_ROUND:
										USART_SendChar(u8_NumberOfBytesMSBs);
										u8_DispatchEnteranceCounter = DISPATCHER_3RD_ROUND;
										break;
										
									case DISPATCHER_3RD_ROUND:
										USART_SendChar(u8_NumberOfBytesLSBs);
										u8_DispatchEnteranceCounter = INITIAL_VALUE;
										gu8_FSM_Status = SENDING;
										break;
								}
								break;
													
							case SENDING:
								if (u16_DataBufferIndex < gu16_NumberOfBytes && gpu8_PointerToBuffer[u16_DataBufferIndex] != NULL_CHAR)
								{
									
									USART_SendChar(gpu8_PointerToBuffer[u16_DataBufferIndex]);
									u8_CHKSUM += gpu8_PointerToBuffer[u16_DataBufferIndex];
									u16_DataBufferIndex++;
								}
								else
								{
									gu8_FSM_Status = SENDING_COMPLETE;
								}
								break;
								
							case SENDING_COMPLETE:
								USART_SendChar(u8_CHKSUM);
								gu8_FSM_Status = IDLE;
								break;
							
						}
						
					}
					break;
				
				case RECEIVER:
					ERR = E_NOK;
					break;
				
				default:
					ERR = E_NOK;
					break;
						
			}
		
		case SPI:
			switch (BCM_Config.u8_SenderOrReceiver)
			{
				case SENDER :
					if(gu8_TXC_Flag)
					{
						gu8_TXC_Flag = FALSE;
						
						switch (gu8_FSM_Status)
						{
							case START_SENDING:
								switch(u8_DispatchEnteranceCounter)
								{
									case DISPATCHER_1ST_ROUND:
										SPI_SendChar(BCM_ID);
										u8_DispatchEnteranceCounter = DISPATCHER_2ND_ROUND;
										break;
								
									case DISPATCHER_2ND_ROUND:
										SPI_SendChar(u8_NumberOfBytesMSBs);
										u8_DispatchEnteranceCounter = DISPATCHER_3RD_ROUND;
										break;
								
									case DISPATCHER_3RD_ROUND:
										SPI_SendChar(u8_NumberOfBytesLSBs);
										u8_DispatchEnteranceCounter = INITIAL_VALUE;
										gu8_FSM_Status = SENDING;
										break;
								}
								break;
							
							case SENDING:
								if (u16_DataBufferIndex < gu16_NumberOfBytes && gpu8_PointerToBuffer[u16_DataBufferIndex] != NULL_CHAR /*&& gpu8_PointerToBuffer[u16_DataBufferIndex] != '\n'*/)
								{
								
									SPI_SendChar(gpu8_PointerToBuffer[u16_DataBufferIndex]);
									u8_CHKSUM += gpu8_PointerToBuffer[u16_DataBufferIndex];

									u16_DataBufferIndex++;
								}
								else
								{
									gu8_FSM_Status = SENDING_COMPLETE;
									gu8_TXC_Flag = TRUE;
								}
								break;
							
							case SENDING_COMPLETE:
								SPI_SendChar(u8_CHKSUM);
								gu8_FSM_Status = IDLE;
								break;
							
						}
					}
					break;
				
				case RECEIVER :
					gu8_FSM_Status = E_NOK;
					break;
				
				default:
					gu8_FSM_Status = E_NOK;
					break;
			}
	}
	
	return gu8_FSM_Status;
}

ERROR_STATUS BCM_RxDispatch()
{
	
	ERROR_STATUS ERR = E_OK;
	static uint16_t u16_DataBufferIndex = INITIAL_VALUE;
	static uint8_t u8_CHKSUM = INITIAL_VALUE;
	static uint8_t u8_Dispatch_enterence_counter = INITIAL_VALUE;
	static uint8_t u8_ReceivedID = INITIAL_VALUE;
	static uint16_t u16_ReceivedDataSize = INITIAL_VALUE;
	uint8_t u8_TempValueForMSBs = INITIAL_VALUE;
	uint8_t u8_ReceivedCHKSUM = INITIAL_VALUE;
	
	switch (BCM_Config.u8_SerialComType)
	{
		case UART:
		break;
		
		case SPI:
			switch (BCM_Config.u8_SenderOrReceiver)
			{
				case SENDER:
					ERR = E_NOK;
					break;
					
				case RECEIVER:
					if (gu8_RXC_Flag)
					{
						gu8_RXC_Flag = FALSE;
					switch (gu8_FSM_Status)
					{
						case START_RECEIVING:
						
							switch(u8_Dispatch_enterence_counter)
							{
								case DISPATCHER_1ST_ROUND:
									SPI_ReceiveChar(&u8_ReceivedID);
									u8_Dispatch_enterence_counter = DISPATCHER_2ND_ROUND;
									break;
								
								case DISPATCHER_2ND_ROUND:
									SPI_ReceiveChar(&u8_TempValueForMSBs);
									u16_ReceivedDataSize = u8_TempValueForMSBs;				
									u16_ReceivedDataSize <<= EIGHT_BITS_STEPS;
									u8_Dispatch_enterence_counter = DISPATCHER_3RD_ROUND;
									break;
								
								case DISPATCHER_3RD_ROUND:
								SPI_ReceiveChar(&u8_TempValueForMSBs);
								
								u16_ReceivedDataSize += u8_TempValueForMSBs;
								
								u8_Dispatch_enterence_counter = INITIAL_VALUE;
								gu8_FSM_Status = RECEIVING;
								break;
							}
							break;
						
						case RECEIVING:
							if (u16_DataBufferIndex < u16_ReceivedDataSize)
							{
								SPI_ReceiveChar(gpu8_PointerToBuffer + u16_DataBufferIndex);
								u8_CHKSUM += gpu8_PointerToBuffer[u16_DataBufferIndex];
								u16_DataBufferIndex++;

							}
							else
							{
								
								gu8_FSM_Status = RECEIVING_COMPLETE;
								gu8_RXC_Flag = TRUE;
							}
							break;
						
						case RECEIVING_COMPLETE:
							
							SPI_ReceiveChar(&u8_ReceivedCHKSUM);
							PORTA_DIR = u8_ReceivedCHKSUM; 
							if (u8_ReceivedCHKSUM != u8_CHKSUM)
							{
								ERR = E_NOK;
							}
							gu8_FSM_Status = IDLE;
					}
			}
	}
					
	}
	return gu8_FSM_Status;
}

ERROR_STATUS BCM_Send (uint8_t* pu8_Data , uint16_t u16_NumberOfBytes)
{
	ERROR_STATUS ERR = E_OK;
	
 	if (gu8_FSM_Status == IDLE)
	 {
		 gu8_FSM_Status = START_SENDING;
		 gpu8_PointerToBuffer = pu8_Data;
		 gu16_NumberOfBytes = u16_NumberOfBytes;
	 }

	return ERR;
}

ERROR_STATUS BCM_Receive(uint8_t* pu8_Data)
{
	ERROR_STATUS ERR = E_OK;
	
	if (gu8_FSM_Status == IDLE)
	{
		gu8_FSM_Status = START_RECEIVING;
		gpu8_PointerToBuffer = pu8_Data;
	}
	return ERR;
		/*
		set FSM to RECEIVING
		set global pointer to pu8_Data
	*/
}
