/*
 * Timer.c
 *
 * Created: 2/16/2020 3:19:57 AM
 *  Author: Reem el-Areeny
 */ 
 
/************************************************************************/
/*				                    INCLUDES	                 		         */
/************************************************************************/
 #include "Timer.h"


/************************************************************************/
/*				                  TIMER0 DEFINES			                     */
/************************************************************************/
#define T0_NO_CLOCK			0x00 /*reset first 3 bits*/
#define T0_PRESCALER_NO		0x01
#define T0_PRESCALER_8		0x02
#define T0_PRESCALER_64		0x03
#define T0_PRESCALER_256	0x04
#define T0_PRESCALER_1024	0x05


#define T0_POLLING				0x00
#define T0_INTERRUPT_NORMAL	0x01

#define TIMER0_RESOLUTION 255

#define TOV0 BIT0

#define T0_CLEAR_PRESCALER 0xF8

/************************************************************************/
/*				                  TIMER1 DEFINES			                     */
/************************************************************************/
#define T1_NO_CLOCK			0x0000 /*reset first 3 bits*/
#define T1_PRESCALER_NO		0x0001
#define T1_PRESCALER_8		0x0002
#define T1_PRESCALER_64		0x0003
#define T1_PRESCALER_256	0x0004
#define T1_PRESCALER_1024	0x0005

#define T1_POLLING					0
#define T1_INTERRUPT_NORMAL		0x04

#define TIMER1_RESOLUTION	65535


#define TOV1 BIT2

#define T1_CLEAR_PRESCALER 0xFFF8

/************************************************************************/
/*				                  TIMER2 DEFINES			                     */
/************************************************************************/
#define T2_NO_CLOCK			0x00 /*reset first 3 bits*/
#define T2_PRESCALER_NO		0x01
#define T2_PRESCALER_8		0x02
#define T2_PRESCALER_32		0x03
#define T2_PRESCALER_64		0x04
#define T2_PRESCALER_128	0x05
#define T2_PRESCALER_256	0x06
#define T2_PRESCALER_1024	0x07

#define T2_POLLING				0x00
#define T2_INTERRUPT_NORMAL	0x40

#define TIMER2_RESOLUTION 255

#define TOV2 BIT2

#define T2_CLEAR_PRESCALER 0xF8

/************************************************************************/
/*				         STATIC FUNCTIONS & variables	        		         */
/************************************************************************/
static ERROR_STATUS_t Timer0_Init(Timer_cfg_s*);
static ERROR_STATUS_t Timer1_Init(Timer_cfg_s*);
static ERROR_STATUS_t Timer2_Init(Timer_cfg_s*);

static uint16_t gu16_Timer0_prescaler = CLEAR_VALUE; 
static uint16_t gu16_Timer1_prescaler = CLEAR_VALUE;
static uint16_t gu16_Timer2_prescaler = CLEAR_VALUE;


/************************************************************************/
/*		             TIMER FUNCTIONS' IMPLEMENTAIONS		                  */
/************************************************************************/
 /**
 * Input: Pointer to a structure contains the information needed to initialize the timer. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */
ERROR_STATUS_t Timer_Init(Timer_cfg_s* Timer_cfg){
	ERROR_STATUS_t  au8_status = E_Ok;
	if(Timer_cfg == NULL){
		au8_status = E_Nok;
	}else{
		switch(Timer_cfg->Timer_CH_NO){
			case TIMER_CH0:
			au8_status |= Timer0_Init(Timer_cfg);
			break;
			case TIMER_CH1:
			au8_status |= Timer1_Init(Timer_cfg);
			break;
			case TIMER_CH2:
			au8_status |= Timer2_Init(Timer_cfg);
			break;
			default:
			au8_status = E_Nok;
			break;
		}
	}
	
	return au8_status;
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to be started.
 *	Timer_Count: The start value of the timer.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function strats the needed timer.
 * 							
 */
ERROR_STATUS_t Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count){
	ERROR_STATUS_t  au8_status = E_Ok;
		switch(Timer_CH_NO){
			case TIMER_CH0:
				TCNT0 = (TIMER0_RESOLUTION - Timer_Count);
				TCCR0 |= gu16_Timer0_prescaler; 
				break;
			case TIMER_CH1:
				TCCR1B |= gu16_Timer1_prescaler;
				TCNT1 = (TIMER1_RESOLUTION - Timer_Count);
				break;
			case TIMER_CH2:
				TCNT2 = (TIMER2_RESOLUTION - Timer_Count);
				TCCR2 |= gu16_Timer2_prescaler;
			default:
				au8_status = E_Nok;
				break;
		}	
	return au8_status;
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to be stopped.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function stops the needed timer.
 * 							
 */
ERROR_STATUS_t Timer_Stop(uint8_t Timer_CH_NO){
	ERROR_STATUS_t  au8_status = E_Ok;
	switch(Timer_CH_NO){
		case TIMER_CH0:
			TCCR0 &= T0_CLEAR_PRESCALER;
			break;
		case TIMER_CH1:
			TCCR1B &= T1_CLEAR_PRESCALER;
			break;
		case TIMER_CH2:
			TCCR2 &= T2_CLEAR_PRESCALER;
			break;
		default:
			au8_status = E_Nok;
			break;
	}
	return au8_status;
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the value of the timer.
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to return the value of the timer.
 * 							
 */
ERROR_STATUS_t Timer_GetValue(uint8_t Timer_CH_NO, uint16_t* Data){
	ERROR_STATUS_t  au8_status = E_Ok;
	if(Data == NULL){
		au8_status = E_Nok;
	}else{
		switch(Timer_CH_NO){
			case TIMER_CH0:
				*Data = TCNT0 ;
				break;
			case TIMER_CH1:
				*Data = TCNT1 ;
				break;
			case TIMER_CH2:
				*Data = TCNT2 ;
				break;
			default:
				au8_status = E_Nok;
				break;
		}
	}
	return au8_status;
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its status.
 * Output:
 * 	Data: A variable of type bool returns if the flag of the timer is raised or not.
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to return if the flag of the timer is raised or not.
 * 							
 */
ERROR_STATUS_t Timer_GetStatus(uint8_t Timer_CH_NO, uint8_t* Data){
	ERROR_STATUS_t au8_status = E_Ok;
	if(Data == NULL){
		au8_status = E_Nok;
	}else{
		switch(Timer_CH_NO){
			case TIMER_CH0:
				*Data = (TIFR & TOV0);
				TIFR |= TOV0;
				break;
			case TIMER_CH1:
				*Data = (TIFR & TOV1);
				TIFR |= TOV1;
				break;
			case TIMER_CH2:
				*Data = (TIFR & TOV2);
				TIFR |= TOV2;
				break;
			default:
				au8_status = E_Nok;
				break;
		}
	}
	return au8_status;
}



/************************************************************************/
/*		             STATIC FUNCTIONS' IMPLEMENTAIONS		               */
/************************************************************************/
/**
* Input: Pointer to a structure contains the information needed to initialize the timer. 
* Output:
* In/Out:			
* Return: The error status of the function.			
* Description: Initiates the module.
* 							
*/
static ERROR_STATUS_t Timer0_Init(Timer_cfg_s* Timer0_cfg){
	ERROR_STATUS_t au8_status = E_Ok;
	if(Timer0_cfg == NULL){
		au8_status = E_Nok;
	}else{
		/*clear all registers*/
		TCNT0 = CLEAR_VALUE;
		TCCR0 = CLEAR_VALUE;
		OCR0 = CLEAR_VALUE;
		/*set the interrupt*/
		switch(Timer0_cfg->Timer_Polling_Or_Interrupt){
			case TIMER_POLLING_MODE:
				TIMSK |= T0_POLLING;
				break;
			case TIMER_INTERRUPT_MODE:
				TIMSK |= T0_INTERRUPT_NORMAL;
				break;
			default:
				au8_status = E_Nok;
				break;
		}

		/*set the prescaler*/
		switch(Timer0_cfg->Timer_Prescaler){
			case TIMER_NO_CLOCK:
				gu16_Timer0_prescaler = T0_NO_CLOCK;
				break;
			case TIMER_PRESCALER_NO:
				gu16_Timer0_prescaler = T0_PRESCALER_NO;
				break;
			case TIMER_PRESCALER_8:
				gu16_Timer0_prescaler = T0_PRESCALER_8;
				break;
			case TIMER_PRESCALER_64:
				gu16_Timer0_prescaler = T0_PRESCALER_64;
				break;
			case TIMER_PRESCALER_256:
				gu16_Timer0_prescaler = T0_PRESCALER_256;
				break;
			case TIMER_PRESCALER_1024:
				gu16_Timer0_prescaler = T0_PRESCALER_1024;
				break;
			default:
				au8_status = E_Nok;
				break;
		}
	}
	return au8_status;
}

/**
* Input: Pointer to a structure contains the information needed to initialize the timer. 
* Output:
* In/Out:			
* Return: The error status of the function.			
* Description: Initiates the module.
* 							
*/
static ERROR_STATUS_t Timer1_Init(Timer_cfg_s* Timer1_cfg){
	ERROR_STATUS_t au8_status = E_Ok;
	if(Timer1_cfg == NULL){
		au8_status = E_Nok;
		}else{
			/*clear all registers*/
			TCCR1A = CLEAR_VALUE;
			TCCR1B = CLEAR_VALUE;
			TCNT1L = CLEAR_VALUE;
			TCNT1H = CLEAR_VALUE;
			OCR1AL = CLEAR_VALUE;
			OCR1AH = CLEAR_VALUE;
			OCR1BL = CLEAR_VALUE;
			OCR1BH = CLEAR_VALUE;

			/*set the interrupt*/
			switch(Timer1_cfg->Timer_Polling_Or_Interrupt){
				case TIMER_POLLING_MODE:
					TIMSK |= T1_POLLING;
					break;
				case TIMER_INTERRUPT_MODE:
					TIMSK |= T1_INTERRUPT_NORMAL;
					break;
				default:
					au8_status = E_Nok;
					break;
			}
					/*set the prescaler*/
					switch(Timer1_cfg->Timer_Prescaler){
						case TIMER_NO_CLOCK:
							gu16_Timer1_prescaler = T1_NO_CLOCK;
							break;
						case TIMER_PRESCALER_NO:
							gu16_Timer1_prescaler = T1_PRESCALER_NO;
							break;
						case TIMER_PRESCALER_8:
							gu16_Timer1_prescaler = T1_PRESCALER_8;
							break;
						case TIMER_PRESCALER_64:
							gu16_Timer1_prescaler = T1_PRESCALER_64;
							break;
						case TIMER_PRESCALER_256:
							gu16_Timer1_prescaler = T1_PRESCALER_256;
							break;
						case TIMER_PRESCALER_1024:
							gu16_Timer1_prescaler = T1_PRESCALER_1024;
							break;
						default:
							au8_status = E_Nok;
							break;
					}
				
		}
	return au8_status;
}

/**
* Input: Pointer to a structure contains the information needed to initialize the timer. 
* Output:
* In/Out:			
* Return: The error status of the function.			
* Description: Initiates the module.
* 							
*/
static ERROR_STATUS_t Timer2_Init(Timer_cfg_s* Timer2_cfg){
	ERROR_STATUS_t au8_status = E_Ok;
	if(Timer2_cfg == NULL){
		au8_status = E_Nok;
	}else{
		/*clear all registers*/
		TCNT2 = CLEAR_VALUE;
		TCCR2 = CLEAR_VALUE;
		OCR2= CLEAR_VALUE;
		ASSR &=  ~(BIT3);
		TIMSK &= ~(BIT6) & ~(BIT7);
		TIFR |= TOV2;
		 
		/*set the interrupt*/
		switch(Timer2_cfg->Timer_Polling_Or_Interrupt){
			case TIMER_POLLING_MODE:
				TIMSK |= T2_POLLING;
				break;
			case TIMER_INTERRUPT_MODE:
				TIMSK |= T2_INTERRUPT_NORMAL;
				break;
			default:
				au8_status = E_Nok;
				break;
		}

		/*set the prescaler*/
		switch(Timer2_cfg->Timer_Prescaler){
			case TIMER_NO_CLOCK:
				gu16_Timer2_prescaler = T2_NO_CLOCK;
				break;
			case TIMER_PRESCALER_NO:
				gu16_Timer2_prescaler = T2_PRESCALER_NO;
				break;
			case TIMER_PRESCALER_8:
				gu16_Timer2_prescaler = T2_PRESCALER_8;
				break;
			case TIMER_PRESCALER_32:
				gu16_Timer2_prescaler = T2_PRESCALER_32;
				break;
			case TIMER_PRESCALER_64:
				gu16_Timer2_prescaler = T2_PRESCALER_64;
				break;
			case TIMER_PRESCALER_128:
				gu16_Timer2_prescaler = T2_PRESCALER_128;
				break;
			case TIMER_PRESCALER_256:
				gu16_Timer2_prescaler = T2_PRESCALER_256;
				break;
			case TIMER_PRESCALER_1024:
				gu16_Timer2_prescaler = T2_PRESCALER_1024;
				break;
			default:
				au8_status = E_Nok;
				break;
		}
	}
	return au8_status;
}
