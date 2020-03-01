/*
 * Timer.h
 *
 *  Created on: Dec 21, 2019
 *      Author: Ehab & Reem
 */

#ifndef TIMER_H_
#define TIMER_H_

/************************************************************************/
/*											INCLUDES							            */
/************************************************************************/
#include "../Infrastructure/std_types.h"
#include "../Infrastructure/registers.h"
#include "interrupt.h"
#include "../Infrastructure/Errors.h"

/************************************************************************/
/*											DEFINES			                        */
/************************************************************************/

#define		TIMER_CH0					0
#define		TIMER_CH1					1
#define		TIMER_CH2					2

#define		TIMER_MODE					0

#define		COUNTER_RISING_MODE		1
#define		COUNTER_FALLING_MODE		2

#define		TIMER_POLLING_MODE		0
#define		TIMER_INTERRUPT_MODE		1

#define		TIMER_NO_CLOCK					0
#define		TIMER_PRESCALER_NO			1
#define		TIMER_PRESCALER_8				2
#define		TIMER_PRESCALER_32			3
#define		TIMER_PRESCALER_64			4
#define		TIMER_PRESCALER_128			5
#define		TIMER_PRESCALER_256			6
#define		TIMER_PRESCALER_1024			7
#define		EXTERNAL_CLOCK_FALLING		8
#define		EXTERNAL_CLOCK_RISING		9

/************************************************************************/
/*								  Structures Definitions	                     */
/************************************************************************/
typedef struct Timer_cfg_s
{
	uint8_t Timer_CH_NO;
	uint8_t Timer_Mode;
	uint8_t Timer_Polling_Or_Interrupt;
	uint8_t Timer_Prescaler;
	void (*Timer_Cbk_ptr)(void);
}Timer_cfg_s;



/************************************************************************/
/*						    TIMER FUNCTIONS' PROTOTYPES							   */
/************************************************************************/

/**
 * Description: Initializes the timer peripheral based on a pre-configured struct
 * @param Timer_cfg : Pointer to the configuration struct 
 * @return function status 
 */
extern ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg);

/**
 * Description: Deinitializes the timer peripheral based on the pre-initialization
 * @return function status 
 */
extern ERROR_STATUS Timer_DeInit(uint8_t Timer_CH_NO);

/**
 * Description: Starts the timer/counter
 * @param Timer_CH_NO : Channel's number :
 *										  - 0 -> TIMER_CH0
 *										  - 1 -> TIMER_CH1
 *										  - 2 -> TIMER_CH2
 * @param Timer_Count : TCNT (Timer/Counter Register) Value : for TIMER_CH0 & TIMER_CH2 
 *																takes values from (0~255)
 *															  for TIMER_CH1 
 *																takes values from (0~65,535)
 * @return function status 
 */
extern ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count);

/**
 * Description: Stops the timer/counter
 * @param Timer_CH_NO : Channel's number :
 *										  - 0 -> TIMER_CH0
 *										  - 1 -> TIMER_CH1
 *										  - 2 -> TIMER_CH2
 * @return function status 
 */
extern ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO);

/**
 * Description: Checks if the timer overflowed or not
 * @param Timer_CH_NO : Channel's number :
 *										  - 0 -> TIMER_CH0
 *										  - 1 -> TIMER_CH1
 *										  - 2 -> TIMER_CH2
 * @param Data : output parameter returns : 
 *										   - 0 -> FALSE
 *										   - 1 -> TRUE
 * @return function status
 */
extern ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH_NO, uint8_t* Data);

/**
 * Description: Sets the value of the TCNT (Timer/Counter Register)
 * @param Timer_CH_NO : Channel's number :
 *										  - 0 -> TIMER_CH0
 *										  - 1 -> TIMER_CH1
 *										  - 2 -> TIMER_CH2
 * @param Data : TCNT Value
 * @return function status 
 */
extern ERROR_STATUS Timer_SetValue(uint8_t Timer_CH_NO, uint16_t Data);

/**
 * Description: Gets the value of the TCNT (Timer/Counter Register)
 * @param Timer_CH_NO : Channel's number :
 *										  - 0 -> TIMER_CH0
 *										  - 1 -> TIMER_CH1
 *										  - 2 -> TIMER_CH2
 * @param Data : output parameter returns : TCNT Value
 * @return function status 
 */
extern ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO, uint16_t* Data);



#endif /* TIMER_H_ */