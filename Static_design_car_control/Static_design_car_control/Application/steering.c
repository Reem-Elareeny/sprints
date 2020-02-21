/*
 * steering.c
 *
 * Created: 2/19/2020 7:55:13 AM
 *  Author: Reem el-Areeny
 */ 

#include "steering.h"


/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */

ERROR_STATUS_t Steering_Init(void){
	ERROR_STATUS_t  au8_status = E_Ok;
	au8_status |= Motor_Init(MOTOR_1);
	au8_status |= Motor_Init(MOTOR_2);
	return au8_status;
}

/**
 * Input: 
 * 	carDirection: The direction of the car from the predefined states of the module.
 * 	speed: The speed of the car from 0% to 100%.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This funtion controls the command and the speed of the car.
 * 							
 */
ERROR_STATUS_t Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed){
	ERROR_STATUS_t au8_status = E_Ok;
	switch(Steering_CarCmd){
		case CAR_FORWARD:
			au8_status |= Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
			au8_status |= Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
			au8_status |= Motor_SpeedUpdate(MOTOR_1,speed);
			au8_status |= Motor_SpeedUpdate(MOTOR_2,speed);
			break;
		case CAR_BACKWARD:
			au8_status |= Motor_Direction(MOTOR_1,MOTOR_FORWARD);
			au8_status |= Motor_Direction(MOTOR_2,MOTOR_FORWARD);
			au8_status |= Motor_SpeedUpdate(MOTOR_1,speed);
			au8_status |= Motor_SpeedUpdate(MOTOR_2,speed);
			break;
		case CAR_LEFT:
			au8_status |= Motor_Direction(MOTOR_1,MOTOR_FORWARD);
			au8_status |= Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
			au8_status |= Motor_SpeedUpdate(MOTOR_1,speed);
			au8_status |= Motor_SpeedUpdate(MOTOR_2,speed);
			break;
		case CAR_RIGHT:
			au8_status |= Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
			au8_status |= Motor_Direction(MOTOR_2,MOTOR_FORWARD);
			au8_status |= Motor_SpeedUpdate(MOTOR_1,speed);
			au8_status |= Motor_SpeedUpdate(MOTOR_2,speed);
			break;
		case CAR_STOP:
			au8_status |= Motor_Direction(MOTOR_1,MOTOR_STOP);
			au8_status |= Motor_Direction(MOTOR_2,MOTOR_STOP);
			au8_status |= Motor_SpeedUpdate(MOTOR_1,0);
			au8_status |= Motor_SpeedUpdate(MOTOR_2,0);
			break;
	}
	return au8_status;
}