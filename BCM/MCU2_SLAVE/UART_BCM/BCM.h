/*
 * BCM.h
 *
 * Created: 3/2/2020 1:25:16 PM
 *  Author: ahmed
 */ 


#ifndef BCM_H_
#define BCM_H_

#include "USART.h"
#include "SPI.h"
#include "BCM_LCfg.h"

#define IDLE				(0xff)

#define START_SENDING		(1)
#define SENDING				(2)
#define SENDING_COMPLETE	(3)

#define START_RECEIVING		(4)
#define RECEIVING			(5)
#define RECEIVING_COMPLETE	(6)

#define UART				(0)
#define SPI					(1)
#define SENDER				(2)
#define RECEIVER			(3)

#define INITIAL_VALUE	(0)

ERROR_STATUS BCM_Init(void);
ERROR_STATUS BCM_DeInit(void);
ERROR_STATUS BCM_RxDispatch(void);
ERROR_STATUS BCM_TxDispatch(void);
ERROR_STATUS BCM_Send (uint8_t* pu8_Data , uint16_t u16_BytesNumber);
ERROR_STATUS BCM_Receive(uint8_t* pu8_Data);




#endif /* BCM_H_ */