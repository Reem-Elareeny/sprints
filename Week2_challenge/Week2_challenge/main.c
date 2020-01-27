/*
 * Week2_challenge.c
 *
 * Created: 1/20/2020 11:54:50 PM
 * Author : Reem el-Areeny
 */ 

#include "led.h"
#include "timers.h"
#include "pushButton.h"
void state_machine_with_polling();
void push_button_with_timer_interrupts();

int main(void)
{
    /* Replace with your application code */
	Led_Init(LED_0);
//  	timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_8,0x00,0x00,T0_POLLING);
	timer0SwPWM(0,2);
    while (1) 
    {
			//Led_On(LED_0);
		//	timer0DelayMs(1000);
			//Led_Off(LED_0);
			//if(T0TimeReachedFlag){
		//		Led_Toggle(LED_0);
				//T0TimeReachedFlag = 0;
			//}
	     }
		//state_machine_with_polling();
	//push_button_with_timer_interrupts();
	

}

void state_machine_with_polling(){
	int state;
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,0x00,0x00,T0_POLLING);
	state = 0;

	while(1){
		switch(state){
			case 0:
				Led_Toggle(LED_0);
				timer0DelayUs(1000000);
				Led_Toggle(LED_0);
				//state = 1;
				//break;
			case 1:
				Led_Toggle(LED_1);
				timer0DelayUs(1000000);
				Led_Toggle(LED_1);
				//state = 2;
				//break;
			case 2:
				Led_Toggle(LED_2);
				timer0DelayUs(1000000);
				Led_Toggle(LED_2);
				//state = 0;
				break;
		}
	}
}


void push_button_with_timer_interrupts(){
	//uint8_t count = 0;
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Off(LED_0);
	Led_Off(LED_2);
	pushButtonInit(BTN_0);

     while (1)
     {
 		if(pushButtonGetStatus(BTN_0)){
			timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,0x00,0x00,T0_INTERRUPT_NORMAL);
			Led_On(LED_0);
			timer0DelayMs(1000);
 		}
		 if(T0TimeReachedFlag == 1){
			 T0TimeReachedFlag =0;
			 Led_Off(LED_0);
			 timer0Stop();
		 }
	}
}


// void push_button_with_timer_interrupts(){
// 	timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,0x00,0x00,T0_POLLING);
// 	Led_Init(LED_0);
// 	Led_Off(LED_0);
// 	pushButtonInit(BTN_0);
// 	pushButtonExternalInterruptEnable();
//  	while (1){
// 		 	Led_Off(LED_0);
// 			if(bTN1Pressed == 1){
// 				Led_On(LED_0);
// 				_delay_ms(1000);
// 
// 				bTN1Pressed = 0;
// 				//_delay_ms(1000);
// // 				if(bTN1Pressed == 1){
// // 					_delay_ms(1000);
// // 					bTN1Pressed = 0;
// // 
// // 				}
// // 				Led_Toggle(LED_0);
// 			}
// // 		Led_Off(LED_0);
//  		}
// 	
// }