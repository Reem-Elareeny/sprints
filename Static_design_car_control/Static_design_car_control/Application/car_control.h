/*
 * car_control.h
 *
 * Created: 2/19/2020 7:56:16 AM
 *  Author: Reem el-Areeny
 */ 


#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_


/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/
#include "steering.h"
#include "../HAL/US.h"
#define F_CPU 16000000ul
#include <util/delay.h>

/*************************************************************/
/*                     FUNCTIONS DECLARATION                 */
/*************************************************************/
/*
 * Fun----------: ERROR_STATUS Car_SM_Init(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: Initiate the car state machine with state"forward at speed 80%",
 * -------------- And initiate steering and ultrasonic functions
*/
extern ERROR_STATUS_t Car_SM_Init(void);

/*
 * Fun----------: ERROR_STATUS Car_SM_Update(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: changes car state according to the ultrasonic input
 * -------------- And represents the motors output for each state
*/
extern ERROR_STATUS_t Car_SM_Update(void);


#endif /* CAR_CONTROL_H_ */