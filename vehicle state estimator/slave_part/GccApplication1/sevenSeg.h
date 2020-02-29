/*
 * sevenSeg_BCD.h
 *
 *  Created on: Oct 24, 2019
 *      Author: Sprints
 */

#ifndef SEVENSEG_H_
#define SEVENSEG_H_

#include "gpio.h"
#include "sevenSegConfig.h"


typedef enum En_SevenSegId_t{
	SEG_0,
	SEG_1,
	SEG_2,
	SEG_3,
}En_SevenSegId_t;

/**
 * Description: Initialize the SEG_x (where x 0, 1, 2, 3) as output
 * @param  a_segment_id The segment to be initialized and it takes
 * 				  one of the enum (En_SevenSegId_t) parameters
 */
void sevenSegInit(En_SevenSegId_t a_segment_id);

/**
 * Description:   Change the SEG_x state (where x 0, 1, 2, 3) to be on
 * @param   a_segment_id The segment to be initialized and it takes
*				one of the enum (En_SevenSegId_t) parameters
 */
void sevenSegEnable(En_SevenSegId_t en_segment_id);

/**
 * Description: Change the SEG_x state (where x 0, 1, 2, 3) to be off
 * @param        a_segment_id The segment to be initialized and it takes
 *                one of the enum (En_SevenSegId_t) parameters
 */                  
void sevenSegDisable(En_SevenSegId_t en_segment_id);

/**
 * Description: To display data on SEG_X (where x 0, 1, 2, 3)
 * @param   a_segment_id The segment to be initialized and it takes
 *				one of the enum (En_SevenSegId_t) parameters
 *
 *
 * @param  u8_number the data  to display 
 */
void sevenSegWrite(En_SevenSegId_t en_segment_id, uint8_t u8_number);


#endif /* SEVENSEG_BCD_H_ */
