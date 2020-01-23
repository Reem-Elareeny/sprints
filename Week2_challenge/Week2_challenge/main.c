/*
 * Week2_challenge.c
 *
 * Created: 1/20/2020 11:54:50 PM
 * Author : Reem el-Areeny
 */ 

#include "led.h"
#include "timers.h"
void state_machine_REQ();

int main(void)
{
    /* Replace with your application code */
	sei();
	Led_Init(LED_0);
	timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,0x00,0x00,T0_INTERRUPT_NORMAL);
	
    while (1) 
    {
		timer0DelayUs(1000000);
		if(T0TimeReachedFlag){
			Led_Toggle(LED_0);
			T0TimeReachedFlag = 0;
		}
     }
// state_machine_REQ();
}

void state_machine_REQ(){
	int state;
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,0x00,0x00,T0_POLLING);
	
	while(1){
		state = 0;
		switch(state){
			case 0:
				Led_On(LED_0);
				timer0DelayUs(1000000);
				Led_Off(LED_0);
			case 1:
				Led_On(LED_1);
				timer0DelayUs(1000000);
				Led_Off(LED_1);
			case 3:
				Led_On(LED_2);
				timer0DelayUs(1000000);
				Led_Off(LED_2);
			break;
		}
	}
}

// void push_button(){
// 	Led_Init(LED_0);
// 	pushButtonInit(BTN_0);
// 	while (1){
// 		if(!pushButtonGetStatus(BTN_0)){
// 			Led_On(LED_0);
// 			unsigned long long int index;
// 			int pushed = 0;
// 			for(index = 0; index< 5 ; index++)
// 			pushed = pushButtonGetStatus(BTN_0);
// 			if(!pushed)
// 			softwareDelayMs(50);
// 			Led_Off(LED_0);
// 		}
// 	}
// }