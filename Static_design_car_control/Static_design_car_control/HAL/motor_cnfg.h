/*
 * motor.h
 *
 * Created: 2/20/2020 5:50:16 AM
 *  Author: Reem el-Areeny
 */ 

#ifndef DCMOTORCONFIG_H_
#define DCMOTORCONFIG_H_

/************************************************************************/
/*				                    INCLUDES	                 		         */
/************************************************************************/
#include "../MCAL/DIO.h"


/************************************************************************/
/*				            MOTOR CONFIGURATIONS	             		         */
/************************************************************************/
#define MOTOR_EN_1_GPIO		(GPIOD)
#define MOTOR_EN_1_BIT		(BIT4)

#define MOTOR_OUT_1A_GPIO	(GPIOD)
#define MOTOR_OUT_1B_GPIO	(GPIOD)
#define MOTOR_OUT_1A_BIT	(BIT3)
#define MOTOR_OUT_1B_BIT	(BIT2)


#define MOTOR_EN_2_GPIO		(GPIOD)
#define MOTOR_EN_2_BIT		(BIT5)

#define MOTOR_OUT_2A_GPIO	(GPIOD)
#define MOTOR_OUT_2B_GPIO	(GPIOD)
#define MOTOR_OUT_2A_BIT	(BIT7)
#define MOTOR_OUT_2B_BIT	(BIT6)

#endif /* MOTORDC_CFG_H_ */