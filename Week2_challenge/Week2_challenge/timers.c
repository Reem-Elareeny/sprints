/*
 * timer.c
 *
 * Created: 1/21/2020 12:01:59 AM
 *  Author: Reem el-Areeny
 */ 
#include "timers.h"
#include <avr/io.h>
volatile uint64_t counter_ov_t0 = 0;
volatile uint64_t counter_ov_t2 = 0;

uint8_t T0TimeReachedFlag = 0;
uint8_t T2TimeReachedFlag = 0;

uint8_t T0CompareMatchFlag = 0;
uint8_t T2CompareMatchFlag = 0;

En_timer0perscaler_t prescaler = 0;

static float_64_t T0overFlowsnum = 0.0;
static float_64_t T2overFlowsnum = 0.0;

static float_64_t T0overFlowNumberPerOneMicroSecond = 0.0;
static float_64_t T2overFlowNumberPerOneMicroSecond = 0.0;

static float_64_t T0overFlowNumberPerOneMilliSecond = 0.0;
static float_64_t T2overFlowNumberPerOneMilliSecond = 0.0;


static float_64_t calculateNumberOfNeededOverflowsInSecs(void);


INTERRUPT_SERVICE_ROTINE(TIMER0_OVF_vector){
	counter_ov_t0++;
	if(counter_ov_t0 == (int)T0overFlowsnum){
		counter_ov_t0 = 0;
		T0TimeReachedFlag = 1;
	}
}

INTERRUPT_SERVICE_ROTINE(TIMER2_OVF_vector){
	counter_ov_t2++;
	if(counter_ov_t2 == (int)T2overFlowsnum){
		counter_ov_t2 = 0;
		T2TimeReachedFlag = 1;
	}
}

void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,En_timer0perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, En_timer0Interrupt_t en_interruptMask){
	//set mode
	TCNT0 = 0;
	TCCR0 = 0;
	OCR0 = 0;
	 
	TCCR0 |= en_mode;
	TCCR0 |= en_OC0;

	//interrupt;
	TIMSK |= en_interruptMask;

	//set initial values
	TCNT0 = u8_initialValue;
	OCR0 = u8_outputCompare;
	//enable/disable interrupt
	
		
	//set prescaler
	//TCCR0 |= en_prescal; 
	prescaler = en_prescal;
	
	T0overFlowNumberPerOneMicroSecond = (float_64_t)(calculateNumberOfNeededOverflowsInSecs()/1000000);
	T0overFlowNumberPerOneMilliSecond = (float_64_t)(calculateNumberOfNeededOverflowsInSecs()/1000);
	//uint32_t overFlowsnum  = overFlowNumberPerOneMicroSec * u32_delay_in_us;
}

void timer0Set(uint8_t u8_value){
	TCNT0 = u8_value;
}

uint8_t timer0Read(void){
	return TCNT0;
}

void timer0Start(void){
	TCCR0 |=  prescaler;
}

void timer0Stop(void){
	TCCR0 &= ~(T0_NO_CLOCK);
	T0overFlowsnum = 0;
}

// void timer0DelayUs(uint32_t u32_delay_in_Us){
// 	
// 	uint64_t count = 0;
// 	T0overFlowsnum  = T0overFlowNumberPerOneMicroSecond * u32_delay_in_Us;
// 
// 	if((TIMSK & T0_INTERRUPT_NORMAL) || (TIMSK & T0_INTERRUPT_CMP)){// interrupt disabled
// 		timer0Start();
// 		while(!(TIFR & BIT0));
// 		TIFR |= BIT0;//reset flag
// 		count++;
// 		if(count == (int)T0overFlowsnum){
// 			count = 0;
// 			timer0Stop();
// 			TCNT0 = 0;
// 
// 		}
// 	}else{// interrupt enabled
// 			T0overFlowsnum  = T0overFlowNumberPerOneMicroSecond * u32_delay_in_Us;
// 			timer0Start();
// 	}
// 
// }

void timer0DelayMs(uint16_t u16_delay_in_ms){
	T0overFlowsnum  = T0overFlowNumberPerOneMilliSecond * u16_delay_in_ms;
	timer0Start();
}

void timer0DelayUs(uint32_t u32_delay_in_Us){
	T0overFlowsnum  = T0overFlowNumberPerOneMicroSecond * u32_delay_in_Us;
	timer0Start();
}

void timer0SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency){
}

static float_64_t calculateNumberOfNeededOverflowsInSecs(void){
	uint16_t prescaler_value = 0;
	switch(prescaler){
		case T0_NO_CLOCK:
			return 0;
		case T0_PRESCALER_NO:
			prescaler_value = 1;
			break;
		case T0_PRESCALER_8:
			prescaler_value = 8;
			break;
		case T0_PRESCALER_64:
			prescaler_value = 64;
			break;
		case T0_PRESCALER_256:
			prescaler_value = 256;
			break;
		case T0_PRESCALER_1024:
			prescaler_value = 1024;
			break;
	}	
	return ((((1/(1.0/MCU_FREQUECY))-1)/prescaler_value)/256);
}

//----------------------------------timer_2-------------------------------------
void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC,En_timer2perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, uint8_t u8_assynchronous, En_timer2Interrupt_t en_interruptMask){
	//set mode
	TCNT2 = 0;
	TCCR2 = 0;
	OCR2 = 0;
	ASSR  = u8_assynchronous;
	TCCR2 |= en_mode;
	TCCR2 |= en_OC;

	//interrupt;
	TIMSK |= en_interruptMask;

	//set initial values
	TCNT2 = u8_initialValue;
	OCR2 = u8_outputCompare;
	//enable/disable interrupt
	
	
	//set prescaler
	prescaler = en_prescal;
	
	T2overFlowNumberPerOneMicroSecond = (float_64_t)(calculateNumberOfNeededOverflowsInSecs()/1000000);
	T2overFlowNumberPerOneMilliSecond = (float_64_t)(calculateNumberOfNeededOverflowsInSecs()/1000);
}

void timer2Set(uint8_t u8_a_value){
	TCNT2 = u8_a_value;
}

uint8_t timer2Read(void){
	return TCNT2;
}

void timer2Start(void){
	TCCR2 |=  prescaler;
}

void timer2Stop(void){
	TCCR2 &= ~(T2_NO_CLOCK);
	T2overFlowsnum = 0;
}

void timer2DelayMs(uint16_t u16_delay_in_ms){
		T2overFlowsnum  = T2overFlowNumberPerOneMicroSecond * u16_delay_in_ms;
		timer2Start();
}

void timer2DelayUs(uint32_t u16_delay_in_us){
		T2overFlowsnum  = T2overFlowNumberPerOneMicroSecond * u16_delay_in_us;
		timer2Start();
}

void timer2SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency){
	
}

