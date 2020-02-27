/*
 * car_control.c
 *
 * Created: 2/19/2020 7:56:01 AM
 *  Author: Reem el-Areeny
 */ 

#include "car_control.h"

/*************************************************************/
/*                     LOCAL DEFINES                 */
/*************************************************************/
#define MOTOR_SPEED 35
#define LOWEST_DISTANCE_ALLOWED 25
#define ALLOWED_DISTANCE 35

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
ERROR_STATUS_t Car_SM_Init(void){
	ERROR_STATUS_t  au8_status = E_Ok;
	au8_status |= Us_Init();
	au8_status |= Steering_Init();
	return au8_status;
}

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
ERROR_STATUS_t Car_SM_Update(void){
	ERROR_STATUS_t  au8_status = E_Ok;
	uint16_t au8_distance = 0;
	au8_status |= Us_Trigger();
	au8_status |= Us_GetDistance(&au8_distance);
	if(au8_distance < LOWEST_DISTANCE_ALLOWED){
		au8_status |= Steering_SteerCar(CAR_BACKWARD,MOTOR_SPEED);
	}else if (au8_distance >= LOWEST_DISTANCE_ALLOWED && au8_distance <ALLOWED_DISTANCE){
		au8_status |= Steering_SteerCar(CAR_RIGHT,MOTOR_SPEED);
	}else
	{
		au8_status |= Steering_SteerCar(CAR_FORWARD,MOTOR_SPEED);
	}

	return  au8_status;
}
