/*
 * Timer_config.h
 *
 * Created: 2/16/2020 3:19:42 AM
 *  Author: Reem el-Areeny
 */ 


#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_


/************************************************************************/
/*				                    INCLUDES	                 		         */
/************************************************************************/
#include "../Infrastructure/std_types.h"


/************************************************************************/
/*					        	CONFIGURATIONS TYPEDEF                       	*/
/************************************************************************/
typedef struct Timer_cfg_s
{
	uint8_t Timer_CH_NO;
	uint8_t Timer_Mode;
	uint8_t Timer_Polling_Or_Interrupt;
	uint8_t Timer_Prescaler;
}Timer_cfg_s;


#endif /* TIMER_CONFIG_H_ */