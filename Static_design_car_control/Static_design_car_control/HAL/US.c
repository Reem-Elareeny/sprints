/*
 * US.c
 *
 * Created: 2/19/2020 7:15:42 AM
 *  Author: Reem el-Areeny
 */ 
 #define F_CPU 16000000ul
 #include <util/delay.h>

#include "../Infrastructure/std_types.h"

#include "../Infrastructure/registers.h"
#include "SW_ICU.h"
#include "us.h"
#include "../MCAL/DIO.h"
#include "../MCAL/Timer.h"
#include "../Interrupt.h"


/*************************************************************/
/*                      Local Defines	                      */
/*************************************************************/
#define DIVIDER_TO_CALCULATE_DISTANCE_FROM_TIME 58


/*************************************************************/
/*                      Global Variables                     */
/*************************************************************/
uint16_t Distance = 0;

/*
 * Function Name   : Us_Init.                                                                       
 * Input Parameters : None.                                                                                                                                            *                                                                                                *
 * Output Parameters: None.                                                                         
 * In_Out Parameters: None.                                                                         
 * Return           : ERROR_STATUS.                                                                 
 * Description      : This function initiate the UltraSonic by set the value of the Dio_Dirction of 
 *                    the pin trigger as an output then initiate the ICU to use it to calculate the 
 *                    On time of the ECHO signal.                                                   
 *                                                                                                  
 *                                                                                                  
 */
ERROR_STATUS_t Us_Init(void){
	ERROR_STATUS_t au8_status = E_Ok;
	/*init the trigger*/
	DIO_Cfg_t dio_config= {GPIOA,BIT0,OUTPUT};
	au8_status |= DIO_init(&dio_config);
	Icu_cfg_s Icu_Cfg = {TIMER_CH2,TIMER_PRESCALER_1024};
	au8_status |= Icu_Init(&Icu_Cfg);
	return au8_status;
}

/*
 * Function Name    : Us_Trigger.                                                                 
 * Input Parameters : None.                                                                                                                                                     *                                                                                                *
 * Output Parameters: None.                                                                       
 * In_Out Parameters: None.                                                                       
 * Return           : ERROR_STATUS                                                                
 * Description      : This function send the  pulse, to trigger pin of the UltraSonic to enhance  
 *                    the  ECUO signal                                                            
 */
ERROR_STATUS_t Us_Trigger(void){
	ERROR_STATUS_t au8_status = E_Ok;
	au8_status |= DIO_Write(GPIOA,BIT0,HIGH);
	_delay_ms(1);
	au8_status |= DIO_Write(GPIOA,BIT0,LOW);
	return au8_status;
}

/*
 * Function Name    : Us_GetDistance.                                                             
 * Input Parameters : pointer to uint16 that will return the distance on it.                                                                                                                     *                                                                                                *
 * Output Parameters: Distance.                                                                   
 * In_Out Parameters: None.                                                                       
 * Return           : ERROR_STATUS.                                                               
 * Description      : This function get the time of high signal of ECUO pulse, then               
 *                    use it to calculate the distance, then return the value in the              
 *                    Distance parameter.                                                         
 */
ERROR_STATUS_t Us_GetDistance(uint16_t * dis){
		ERROR_STATUS_t au8_status = E_Ok;
		uint32_t au8_time = 0;
		au8_status |= Icu_ReadTime(TIMER_CH2,SwICU_EdgeRisiging,&au8_time);
		*dis =  au8_time/DIVIDER_TO_CALCULATE_DISTANCE_FROM_TIME;
		return E_Ok;
}