/*
 * HW_PWM.c
 *
 * Created: 2/18/2020 3:09:35 AM
 * Author : Reem el-Areeny
 */ 

#define F_CPU 16000000ul
#include <util/delay.h>
#include "Application/car_control.h"


int main(){
	Car_SM_Init();
	while(1){
		Car_SM_Update();
	}
	return 0;
}


 