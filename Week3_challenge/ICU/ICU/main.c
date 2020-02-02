/*
 * ICU.c
 *
 * Created: 1/30/2020 10:54:41 AM
 * Author : Reem el-Areeny
 */ 

#include "gpio.h"
#include "led.h"
#include "interrupt.h"
#include "SwICU.h"
#include "timers.h"
#include "dcMotor.h"
#include <util/delay.h>
extern volatile uint8_t inputStatus;
//extern volatile uint8_t TCNT_value;

int main(void)
{

	 	MotorDC_Init(MOT_1);
		MotorDC_Init(MOT_2);

	 	MotorDC_Dir(MOT_1, FORWARD);
	 	MotorDC_Dir(MOT_2, FORWARD);
		MotorDC_Speed_PollingWithT0(50);


	//enable global interrupt
// 	sei();
// 	GIFR &= ~(BIT5);
// 	Led_Init(LED_0);
// 	PORTB_DIR &= ~(BIT3);
// 	MCUCSR |= BIT6;
//  GICR |= BIT5;


		uint8_t TCNT_value = 0;
		uint8_t distance = 0;
		Led_Init(LED_0);
		Led_Init(LED_1);
		Led_Init(LED_2);
		Led_Init(LED_3);
		gpioPinDirection(GPIOA,BIT3,OUTPUT);
		SwICU_Init(SwICU_EdgeRisiging);
		timer0Init(T2_NORMAL_MODE,T2_OC2_DIS,T2_PRESCALER_64,0x00,0x00,T2_POLLING);
		
	while(1){
		 

		gpioPinWrite(GPIOA,BIT3,HIGH);
		//timer2DelayMs(100);
		_delay_ms(1);
		gpioPinWrite(GPIOA,BIT3,LOW);
		//while(!(GIFR & BIT5));
		
		while(3 != inputStatus);
		
		SwICU_Read(&TCNT_value);
		distance = (TCNT_value *8)/58;

		if(distance <= 5){
			MotorDC_Dir(MOT_1, STOP);
			MotorDC_Dir(MOT_2, STOP);
			Led_Init(LED_0);
			Led_On(LED_0);
			Led_Init(LED_1);
			Led_Off(LED_1);
		}else{
			MotorDC_Dir(MOT_1, FORWARD);
			MotorDC_Dir(MOT_2, FORWARD);
			Led_Init(LED_1);
			Led_On(LED_1);
			Led_Init(LED_0);
			Led_Off(LED_0);
		}
// 		switch (distance)
// 		{
// 			case 2:
// 			Led_Off(LED_0);
// 			Led_On(LED_1);
// 			Led_Off(LED_2);
// 			Led_Off(LED_3);
// 			break;
// 
// 			case 3:
// 			Led_On(LED_0);
// 			Led_On(LED_1);
// 			Led_Off(LED_2);
// 			Led_Off(LED_3);
// 			break;
// 
// 			case 4:
// 			Led_Off(LED_0);
// 			Led_Off(LED_1);
// 			Led_On(LED_2);
// 			Led_Off(LED_3);
// 			break;
// 
// 			case 5:
// 			Led_On(LED_0);
// 			Led_Off(LED_1);
// 			Led_On(LED_2);
// 			Led_Off(LED_3);
// 			break;
// 
// 			case 6:
// 			Led_Off(LED_0);
// 			Led_On(LED_1);
// 			Led_On(LED_2);
// 			Led_Off(LED_3);
// 			break;
// 
// 			case 7:
// 			Led_On(LED_0);
// 			Led_On(LED_1);
// 			Led_On(LED_2);
// 			Led_Off(LED_3);
// 			break;
// 
// 			case 8:
// 			Led_Off(LED_0);
// 			Led_Off(LED_1);
// 			Led_Off(LED_2);
// 			Led_On(LED_3);
// 			break;
// 
// 			case 9:
// 			Led_On(LED_0);
// 			Led_Off(LED_1);
// 			Led_Off(LED_2);
// 			Led_On(LED_3);
// 			break;
// 
// 			case 10:
// 			Led_Off(LED_0);
// 			Led_On(LED_1);
// 			Led_Off(LED_2);
// 			Led_On(LED_3);
// 			break;
// 
// 			case 11:
// 			Led_On(LED_0);
// 			Led_On(LED_1);
// 			Led_Off(LED_2);
// 			Led_On(LED_3);
// 			break;
// 
// 			case 12:
// 			Led_Off(LED_0);
// 			Led_Off(LED_1);
// 			Led_On(LED_2);
// 			Led_On(LED_3);
// 			break;
// 
// 			case 13:
// 			Led_On(LED_0);
// 			Led_Off(LED_1);
// 			Led_On(LED_2);
// 			Led_On(LED_3);
// 			break;
// 
// 			case 14:
// 			Led_Off(LED_0);
// 			Led_On(LED_1);
// 			Led_On(LED_2);
// 			Led_On(LED_3);
// 			break;
// 
// 			case 15:
// 			Led_On(LED_0);
// 			Led_On(LED_1);
// 			Led_On(LED_2);
// 			Led_On(LED_3);
// 			break;
// 
// 			default:
// 			Led_Off(LED_0);
// 			Led_Off(LED_1);
// 			Led_Off(LED_2);
// 			Led_Off(LED_3);
// 			break;//  		}
 		TCNT0 = 0;
		//timer2DelayMs(200);
		inputStatus = 1;
		_delay_ms(1000);
	}	return 0;
   // while (1);
}

