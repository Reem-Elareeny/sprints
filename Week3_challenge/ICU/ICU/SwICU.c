/*
 * SwICU.c
 *
 * Created: 1/29/2020 2:49:12 PM
 *  Author: Reem el-Areeny
 */ 

#include "timers.h"
#include "SwICU.h"
#include "gpio.h"
#include "led.h"

static EN_SwICU_Edge_t en_inputCaptureEdge = SwICU_EdgeFalling;
volatile uint8_t inputStatus = 1;
//volatile uint8_t TCNT_value = 0;
void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge){
	sei();
	GIFR &= ~(BIT5);
	gpioPinDirection(INT2_GPIO,INT2_BIT,INPUT);
	timer0Init(T0_NORMAL_MODE, T0_OC0_DIS, T0_PRESCALER_64, 0x00, 0x00, T0_POLLING);
	SwICU_SetCfgEdge(a_en_inputCaptureEdge);
	SwICU_Enable();
}

// 
// EN_SwICU_Edge_t SwICU_GetCfgEdge(void){
// 	
// }

void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdge){
	SwICU_Disable();
	switch(a_en_inputCaptureEdge){
		case SwICU_EdgeRisiging:			
			MCUCSR |= BIT6;
			break;
		case SwICU_EdgeFalling:
			MCUCSR &= ~BIT6;
			break;
	}
	GIFR &= ~(BIT5);
	SwICU_Enable();

}

void SwICU_Read(volatile uint8_t * a_pu8_capt){
	*a_pu8_capt  = timer0Read();
}

void SwICU_Stop(void){
	timer0Stop();
}

void SwICU_Start(void){
	timer0Start();
}

void SwICU_Enable(void){
	GICR |= BIT5;
}

void SwICU_Disable(void){
	GICR &= ~(BIT5);
}

INTERRUPT_SERVICE_ROTINE(INT2_vector){
	//Led_On(LED_0);
	if(inputStatus == 1){
		SwICU_Stop();
		SwICU_SetCfgEdge(SwICU_EdgeFalling);
		inputStatus = 2;
			
		//Led_On(LED_0);
	}else if (inputStatus== 2){
		SwICU_Start();
		SwICU_SetCfgEdge(SwICU_EdgeRisiging);
		//TCNT_value = TCNT0;
		//TCNT0 = 0x00;
		inputStatus = 3;
		//Led_Off(LED_0);
	}
}

void ultrasonicActivate(){
	//gpioPinDirection(TRIGGER_GPIO,TRIGGER_PIN, OUTPUT);
}