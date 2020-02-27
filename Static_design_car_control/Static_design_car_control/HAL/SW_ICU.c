/*
 * SW_ICU.c
 *
 * Created: 2/18/2020 2:26:32 PM
 *  Author: Reem el-Areeny
 */ 
 
#include "SW_ICU.h"
#include "../Interrupt.h"

/************************************************************************/
/*									 LOCAL DEFINES									      */
/************************************************************************/
#define INT2_GPIO GPIOB
#define INT2_BIT BIT2
#define TIME_OF_1_TICK_IN_US 64
/************************************************************************/
/*							      GLOBAL VARIABLES								      */
/************************************************************************/
volatile uint8_t gu8_inputStatus = RISE;
volatile uint8_t gu8_Status_flag = 0;


/************************************************************************/
/*				         Static Functions' Prototypes						      */
/************************************************************************/
static ERROR_STATUS_t SwICU_SetCfgEdge(uint8_t a_en_inputCaptureEdge);
static ERROR_STATUS_t SwICU_Enable();
static ERROR_STATUS_t SwICU_Disable(void);
static ERROR_STATUS_t SwICU_Start(void);

/************************************************************************/
/*				          Functions' implementations							      */
/************************************************************************/
/*
 * Function 	: Icu_Init                                                
 * Input 		: Icu_cfg : pointer to structure of type Icu_cfg_s        
 * Return 		: value of type ERROR_STATUS							 
 * 				  which is one of the following values:					  
 * 				  - E_OK  : initialized successfully					  
 *				  - E_NOK : not initialized successfully				  
 * Description  : Initializes the ICU by initializing the timer			  
 * 				  and enabling the global interrupt						
 */
ERROR_STATUS_t Icu_Init(Icu_cfg_s * Icu_Cfg){
	ERROR_STATUS_t au8_status = E_Ok;
	DIO_Cfg_t int2 = {INT2_GPIO,INT2_BIT,INPUT};
	au8_status |= DIO_init (&int2);
	
	Timer_cfg_s Timer_info;
	Timer_info.Timer_CH_NO = TIMER_CH2;
	Timer_info.Timer_Mode = TIMER_MODE;
	Timer_info.Timer_Prescaler = TIMER_PRESCALER_1024;
	Timer_info.Timer_Polling_Or_Interrupt = TIMER_POLLING_MODE;
	au8_status |= Timer_Init(&Timer_info);
	au8_status |= SwICU_SetCfgEdge(SwICU_EdgeRisiging);
	au8_status |= SwICU_Enable();
	sei();
	return au8_status;
}

/*
 * Function		: Icu_ReadTime
 * Input		: 
 *				Icu_Channel --> ICU timer channel
 *									- ICU_TIMER_CH0
 *									- ICU_TIMER_CH1
 *									- ICU_TIMER_CH2
 *				Icu_EdgeToEdge -- > edges to calculate pusle time between:
 *									- ICU_RISE_TO_RISE
 *									- ICU_RISE_TO_FALL
 *									- ICU_FALE_TO_RISE					   
 * Output 		: Icu_Time : pointer to uint32 variable to give the time   
 * 				  from falling edge to rising edge						   
 * Return 		: value of type ERROR_STATUS							   
 * 				  which is one of the following values:					   
 * 				  - E_OK : successful									   
 *				  - E_NOK : not successful								   
 * Description	: calculates the time between 2 edges				       
*/
ERROR_STATUS_t Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time){
	ERROR_STATUS_t au8_status = E_Ok;
 	uint16_t au8numOfTicks = 0;
 	while(gu8_Status_flag != DONE);
	gu8_Status_flag = NOT_DONE;
 	au8_status |= Timer_GetValue(Icu_Channel, &au8numOfTicks);
 	*Icu_Time = au8numOfTicks * TIME_OF_1_TICK_IN_US;
 	return au8_status;
}


/************************************************************************/
/*		             STATIC FUNCTIONS' IMPLEMENTAIONS		               */
/************************************************************************/
/**
* Input: rising/falling edge.
* Output:
* In/Out:
* Return: The error status of the function.
* Description: set the external interrupt to the rising/falling edge
*
*/
static ERROR_STATUS_t SwICU_SetCfgEdge(uint8_t a_en_inputCaptureEdge){
	ERROR_STATUS_t au8_status = E_Ok;
	au8_status |= SwICU_Disable();
	switch(a_en_inputCaptureEdge){
		case SwICU_EdgeRisiging:
			MCUCSR |= BIT6;
			break;
		case SwICU_EdgeFalling:
			MCUCSR &= ~BIT6;
			break;
	}

	/*reset the flag*/
	GIFR &= ~(BIT5);
	au8_status |= SwICU_Enable();
	return au8_status;
}


/**
* Input:
* Output:
* In/Out:
* Return: The error status of the function.
* Description: stops the ICU
*
*/
static ERROR_STATUS_t SwICU_Stop(void){
	ERROR_STATUS_t au8_status = E_Ok;
	au8_status |= Timer_Stop(TIMER_CH2);
	return au8_status;
}


/**
* Input:
* Output:
* In/Out:
* Return: The error status of the function.
* Description: starts the ICU
*
*/
static ERROR_STATUS_t SwICU_Start(void){
	ERROR_STATUS_t au8_status = E_Ok;
	au8_status |= Timer_Start(TIMER_CH2,255);
	return au8_status;
}


/**
* Input:
* Output:
* In/Out:
* Return: The error status of the function.
* Description: Enable the external interrupt
*
*/
static ERROR_STATUS_t SwICU_Enable(){
	ERROR_STATUS_t au8_status = E_Ok;
	/*enable external interrupt 2*/
	GICR |= BIT5;
	return au8_status;
}


/**
* Input:
* Output:
* In/Out:
* Return: The error status of the function.
* Description: disable the external interrupt
*
*/
static ERROR_STATUS_t SwICU_Disable(void){
	ERROR_STATUS_t au8_status = E_Ok;
	/*disable external interrupt 2*/
	GICR &= ~(BIT5);
	return au8_status;
}


/************************************************************************/
/*						      EXTERNAL INTERRUPT HANDLING							*/
/************************************************************************/
INTERRUPT_SERVICE_ROTINE(INT2_vector){
	
	if(gu8_inputStatus == RISE){
		SwICU_Start();
		SwICU_SetCfgEdge(SwICU_EdgeFalling);
		gu8_inputStatus = FALL;
		
		}else if (gu8_inputStatus == FALL){
		SwICU_Stop();
		SwICU_SetCfgEdge(SwICU_EdgeRisiging);
		gu8_inputStatus = RISE;
		gu8_Status_flag = DONE;
	}

}