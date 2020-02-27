/*
 * motor.c
 *
 * Created: 2/20/2020 5:51:49 AM
 *  Author: Reem el-Areeny
 */ 

#include "motor.h"


/**
 * Func			: Motor_Init
 * Input		: motorNumber
 *	  	  		  #def
 *	  	  		  number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: ERROR_STATUS
 * Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
 */
 ERROR_STATUS_t Motor_Init(uint8_t en_motor_number){

 	ERROR_STATUS_t au8_status = E_Ok;

	DIO_Cfg_t DIO_info;

	Pwm_Cfg_s PWM_info;
	PWM_info.Prescaler = PWM_PRESCALER_1024;
			

	switch(en_motor_number){
		case MOTOR_1:
			PWM_info.Channel = PWM_CH1A;
			DIO_info.GPIO = MOTOR_EN_1_GPIO;
			DIO_info.pins = MOTOR_EN_1_BIT;
			DIO_info.dir = OUTPUT;
			au8_status |= DIO_init(&DIO_info);

			DIO_info.GPIO = MOTOR_OUT_1A_GPIO;
			DIO_info.pins = MOTOR_OUT_1A_BIT;
			DIO_info.dir = OUTPUT;
			au8_status |= DIO_init(&DIO_info);

			DIO_info.GPIO = MOTOR_OUT_1B_GPIO;
			DIO_info.pins = MOTOR_OUT_1B_BIT;
			DIO_info.dir = OUTPUT;
			au8_status |= DIO_init(&DIO_info);
			break;
 		case MOTOR_2:
				PWM_info.Channel = PWM_CH1B;
				DIO_info.GPIO = MOTOR_EN_2_GPIO;
				DIO_info.pins = MOTOR_EN_2_BIT;
				DIO_info.dir = OUTPUT;
				au8_status |= DIO_init(&DIO_info);

				DIO_info.GPIO = MOTOR_OUT_2A_GPIO;
				DIO_info.pins = MOTOR_OUT_2A_BIT;
				DIO_info.dir = OUTPUT;
				au8_status |= DIO_init(&DIO_info);

				DIO_info.GPIO = MOTOR_OUT_2B_GPIO;
				DIO_info.pins = MOTOR_OUT_2B_BIT;
				DIO_info.dir = OUTPUT;
				au8_status |= DIO_init(&DIO_info);
				break;
			default:
				au8_status  = E_Nok;
				break;
	}
	au8_status |= Pwm_Init(&PWM_info);
	return au8_status;
}


/**
* Fun		 : Motor_Direction
* input	 : @param Motor_Number
#define
MOTOR_1, MOTOR_2

@param Motor_Direction
#define
Stop, Forward, Backword
* output  	 : no output
* return 	 : ERROR_STATUS
* Descriptio: Controls the motor direction from getting the motor number and the direction.
*/
ERROR_STATUS_t Motor_Direction(uint8_t en_motor_number, uint8_t en_motor_dir){
	ERROR_STATUS_t au8_status = E_Ok;
	switch(en_motor_number){
		case MOTOR_1:
			switch(en_motor_dir){
				case MOTOR_FORWARD:
					au8_status |= DIO_Write(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, HIGH);
					au8_status |= DIO_Write(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
					break;
				case MOTOR_BACKWARD:
					au8_status |= DIO_Write(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
					au8_status |= DIO_Write(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, HIGH);
					break;
				case MOTOR_STOP:
					au8_status |= DIO_Write(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
					au8_status |= DIO_Write(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
					break;
				default:
					au8_status = E_Nok;
					break;
			}
			break;
		
		case MOTOR_2:
			switch(en_motor_dir){
				case MOTOR_FORWARD:
					au8_status |= DIO_Write(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, HIGH);
					au8_status |=DIO_Write(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
					break;
				case MOTOR_BACKWARD:
					au8_status |= DIO_Write(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
					au8_status |= DIO_Write(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, HIGH);
					break;
				case MOTOR_STOP:
					au8_status |= DIO_Write(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
					au8_status |= DIO_Write(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
					break;
				default:
					au8_status = E_Nok;
			}
			break;
		default:
			au8_status = E_Nok;
			break;
	}
	return au8_status;
}

/**
* Fun		 : Motor_Start
* input	 : @param Motor_Number
#define
MOTOR_1, MOTOR_2
@param Mot_Speed
set the motor speed
* output  	 : no output
* return 	 : ERROR_STATUS
* Descriptio: Start the motor.
*/
ERROR_STATUS_t Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed){
	ERROR_STATUS_t au8_status = E_Ok;
	switch(Motor_Number){
		case MOTOR_1:
			au8_status |= Pwm_Start(PWM_CH1A,Mot_Speed,Frequncy_100HZ);
			break;
		case MOTOR_2:
			au8_status |=Pwm_Start(PWM_CH1B,Mot_Speed,Frequncy_100HZ);
			break;
		default:
			au8_status = E_Nok;
			break;
	}
	return au8_status;
}


/**
 * Fun		 : Motor_SpeedUpdate
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Controls the motor speed from getting the motor number and the speed.
*/
ERROR_STATUS_t Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed){
	ERROR_STATUS_t au8_status = E_Ok;
	switch(Motor_Number){
		case MOTOR_1:
			au8_status |= Pwm_Stop(PWM_CH1A);
			au8_status |= Pwm_Start(PWM_CH1A,Speed,Frequncy_100HZ);
			break;
		case MOTOR_2:
			au8_status |= Pwm_Stop(PWM_CH1B);
			au8_status |= Pwm_Start(PWM_CH1B,Speed,Frequncy_100HZ);
			break;
		default:
			au8_status = E_Nok;
	}
	return au8_status;
}

/**
 * Fun		 : Motor_Stop
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: stop the motor.
*/
ERROR_STATUS_t Motor_Stop(uint8_t Motor_Number){
	ERROR_STATUS_t au8_status = E_Ok;
	return au8_status;
}

/**
 * Func			: Motor_GetStatus
 * Input		: Motor_Number
 *	  	  		 #def
 *	  	  		 number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: Initialization_STATUS
 * Description	: Returns status of the motor whether intialized or not
 */
ERROR_STATUS_t Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status){
	ERROR_STATUS_t au8_status = E_Ok;
	return au8_status;
}

