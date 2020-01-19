/*
 * GccApplication1.c
 *
 * Created: 1/18/2020 12:42:05 AM
 * Author : Reem el-Areeny
 */ 

//#include <avr/io.h>

#include "led.h"
#include "pushButton.h" 
#include <avr/delay.h>

void testCase1_GPIO_REQ7();
void testCase2_GPIO_REQ8();
void testCase3_GPIO_REQ9();

int main(void)
{	//testCase1_GPIO_REQ7();
	testCase2_GPIO_REQ8();
	//testCase3_GPIO_REQ9();
	return 0;
}
void testCase1_GPIO_REQ7(){
	
}

void testCase2_GPIO_REQ8(){
	Led_Init(LED_0);	
	pushButtonInit(BTN_0);
	while (1){
		if(!pushButtonGetStatus(BTN_0)){
			Led_On(LED_0);
			unsigned long long int index;
			int pushed = 0;
			for(index = 0; index< 5 ; index++)
				pushed = pushButtonGetStatus(BTN_0);	
			if(!pushed)
				softwareDelayMs(50);
			Led_Off(LED_0);
		}
	}
}

void testCase3_GPIO_REQ9(){
	int state;
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);

	while(1){
		state = 0;
		switch(state){
			case 0:
				Led_On(LED_0);
				//_delay_ms(1000);
				softwareDelayMs(50);
				Led_Off(LED_0);
			case 1:
				Led_On(LED_1);
				softwareDelayMs(50);
				Led_Off(LED_1);
			case 3:
				Led_On(LED_2);
				softwareDelayMs(50);
				Led_Off(LED_2);
				break;
		}
	}
}