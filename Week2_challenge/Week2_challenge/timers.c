/*
 * timer.c
 *
 * Created: 1/21/2020 12:01:59 AM
 *  Author: Reem el-Areeny
 */ 
#include "timers.h"
#include "led.h"
volatile uint64_t counter_ov_t0 = 0;
volatile uint64_t counter_ov_t2 = 0;

uint8_t T0TimeReachedFlag = 0;
uint8_t T2TimeReachedFlag = 0;

uint8_t T0CompareMatchFlag = 0;
uint8_t T2CompareMatchFlag = 0;

En_timer0perscaler_t T0_prescaler = 0;
En_timer2perscaler_t T2_prescaler = 0;

 static float_64_t T0overFlowsnum = 0.0;
 static float_64_t T2overFlowsnum = 0.0;
// 
 static float_64_t T0overFlowNumberPerOneMicroSecond = 0.0;
 static float_64_t T2overFlowNumberPerOneMicroSecond = 0.0;

 static float_64_t T0overFlowNumberPerOneMilliSecond = 0.0;
 static float_64_t T2overFlowNumberPerOneMilliSecond = 0.0;

volatile uint8_t PWM_TCNT_initialValue = 0;

static float_64_t calculateNumberOfNeededOverflowsInSecs(uint16_t);


INTERRUPT_SERVICE_ROTINE(TIMER0_OVF_vector){
// 	counter_ov_t0++;
// 	if(counter_ov_t0 == (int)T0overFlowsnum){
// 		counter_ov_t0 = 0;
// 		T0TimeReachedFlag = 1;
// 	}
	gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT,HIGH);
	timer0Set(PWM_TCNT_initialValue);
}

INTERRUPT_SERVICE_ROTINE(TIMER0_COMP_vector){
	gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT,LOW);
}

INTERRUPT_SERVICE_ROTINE(TIMER2_OVF_vector){
// 	counter_ov_t0++;
// 	if(counter_ov_t0 == (int)T0overFlowsnum){
// 		counter_ov_t0 = 0;
// 		T0TimeReachedFlag = 1;
// 	}
	gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT,HIGH);
	timer0Set(PWM_TCNT_initialValue);
}

INTERRUPT_SERVICE_ROTINE(TIMER2_COMP_vector){
	gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT,LOW);
}

void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,En_timer0perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, En_timer0Interrupt_t en_interruptMask){
	Led_Init(LED_0);
	//set mode
	TCNT0 = 0;
	TCCR0 = 0;
	OCR0 = 0;
	 
	TCCR0 |= en_mode;
	TCCR0 |= en_OC0;

	//interrupt;
	TIMSK &= ~BIT0 &  ~BIT1;
	TIMSK |= en_interruptMask;

	//set initial values
	TCNT0 = u8_initialValue;
	OCR0 = u8_outputCompare;
	//enable/disable interrupt
	
		
	//set prescaler
	//TCCR0 |= en_prescal; 
	T0_prescaler = en_prescal;
	
//	T0overFlowNumberPerOneMicroSecond = (float_64_t)(calculateNumberOfNeededOverflowsInSecs(256)/1000000);
	//T0overFlowNumberPerOneMilliSecond = (float_64_t)(calculateNumberOfNeededOverflowsInSecs(256)/1000);
	//uint32_t overFlowsnum  = overFlowNumberPerOneMicroSec * u32_delay_in_us;
}

void timer0Set(uint8_t u8_value){
	TCNT0 = u8_value;
}

uint8_t timer0Read(void){
	return TCNT0;
}

void timer0Start(void){
	TCCR0 |=  T0_prescaler;
}

void timer0Stop(void){
	TCCR0 &= ~(T0_NO_CLOCK);
// 	T0overFlowsnum = 0;
}

void timer0DelayUs(uint32_t u32_delay_in_Us){
	uint64_t count = 0;
	T0overFlowsnum  = T0overFlowNumberPerOneMicroSecond * u32_delay_in_Us;
	float fraction = T0overFlowsnum - (int)T0overFlowsnum;
	timer0Set(256 * (1 - fraction));
	T0overFlowsnum++;
	if((TIMSK & BIT0) == T0_POLLING){// interrupt disabled
		//cli();
		timer0Start();
		while(1){
			while(!(TIFR & BIT0));
			TIFR |= BIT0;//reset flag
			count++;
			if(count == (int)T0overFlowsnum){
				count = 0;
				timer0Stop();
				TCNT0 = 0;
				break;
			}
		}
	}
	else{// interrupt enabled
			sei();
			timer0Start();
	}
}

// void timer0DelayMs(uint16_t u16_delay_in_ms){
// 	uint64_t count = 0;
// 	T0overFlowsnum  = 1;//T0overFlowNumberPerOneMilliSecond * u16_delay_in_ms;
// 	if((TIMSK & BIT0) == T0_POLLING){// interrupt disabled
// 		cli();
// 		timer0Start();
// 		while(1){
// 			while(!(TIFR & BIT0));
// 			TIFR |= BIT0;//reset flag
// 			count++;
// 			if(count == (int)T0overFlowsnum){
// 				count = 0;
// 				timer0Stop();
// 				TCNT0 = 0;
// 				break;
// 			}
// 		break;}
// 	}
// 	else{// interrupt enabled
// 		sei();
// 		timer0Start();
// 	}
// 	
// }
// 
// 
void timer0SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency){
	uint8_t CTC_value = 0;
	uint8_t interrupt_mask = 0;
	//freq/(prescaler * 1+256)
	if(u8_dutyCycle == 100){
		CTC_value = 0;
		interrupt_mask = (T0_INTERRUPT_NORMAL);
	}else if(u8_dutyCycle == 0){
			interrupt_mask = (T0_COMP_MODE);
	}else{
		CTC_value =(uint8_t)(256 * u8_dutyCycle / 100);
		interrupt_mask = (T0_INTERRUPT_NORMAL | T0_INTERRUPT_CMP);
	}
	//interrupt_mask = (T0_INTERRUPT_NORMAL | T0_INTERRUPT_CMP);
	sei();
	gpioPinDirection(T0_PWM_GPIO,T0_PWM_BIT,OUTPUT);
	
		switch(u8_frequency){
			case 200:
				PWM_TCNT_initialValue = 178;
				CTC_value =(uint8_t)((256-PWM_TCNT_initialValue) * u8_dutyCycle / 100)+PWM_TCNT_initialValue;
				timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_1024,PWM_TCNT_initialValue,CTC_value,interrupt_mask);
				timer0Start();
				break;
			case 100:
				PWM_TCNT_initialValue = 100;
				CTC_value =(uint8_t)((256-PWM_TCNT_initialValue) * u8_dutyCycle / 100)+PWM_TCNT_initialValue;
				timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_1024,PWM_TCNT_initialValue,CTC_value,interrupt_mask);
				timer0Start();
				break;
// 			case 1://1K
// 				PWM_TCNT_initialValue = 6;
// 				CTC_value =(uint8_t)((256-PWM_TCNT_initialValue) * u8_dutyCycle / 100)+PWM_TCNT_initialValue;
// 				timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,PWM_TCNT_initialValue,74,interrupt_mask);
// 				timer0Start();
// 				break;
// 			case 2://1K
// 				PWM_TCNT_initialValue = 132;
// 				CTC_value =(uint8_t)((256-PWM_TCNT_initialValue) * u8_dutyCycle / 100)+PWM_TCNT_initialValue;
// 				timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,PWM_TCNT_initialValue,CTC_value,interrupt_mask);
// 				timer0Start();
// 				break;
		}
		
// 		PWM_TCNT_initialValue =256 - MCU_FREQUECY/(prescaler*u8_frequency);
// 		timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,PWM_TCNT_initialValue,CTC_value,(T0_INTERRUPT_NORMAL | T0_INTERRUPT_CMP));
// 		timer0Start();
// 		PWM_TCNT_initialValue = 0;
}

void timer0DelayMs(uint16_t u16_delay_in_ms){
	uint8_t count = 0;
	uint64_t numOfOverFlows = 0;
	uint64_t numOfExtraTicks = 0;
	switch(T0_prescaler){
		case T0_NO_CLOCK:
			break;
		case T0_PRESCALER_NO:
		//overflows & ticks per 1 milliseconds
		//((((1/(1.0/MCU_FREQUECY))-1)/prescaler_value)/255);
			numOfOverFlows = 63;
			numOfExtraTicks =128 ;
			break;
		case T0_PRESCALER_8:
			numOfOverFlows = 8;
			numOfExtraTicks =208 ;
			break;
		case T0_PRESCALER_64:
			numOfOverFlows = 1;
			numOfExtraTicks =250 ;
			break;
		case T0_PRESCALER_256:
			numOfOverFlows = 1;
			numOfExtraTicks =62 ;
			break;
		case T0_PRESCALER_1024: 
			numOfOverFlows = 1;
			numOfExtraTicks = 22 ;
			break;
	}
		//cli();

		while(u16_delay_in_ms--){
			
			timer0Start();
			timer0Set(256 - numOfExtraTicks);
		while(1){
				while(!(TIFR & BIT0));
				TIFR |= BIT0;//reset flag
				count++;
				if(count == numOfOverFlows){
					count = 0;
					timer0Stop();
					TCNT0 = 0;
					break;
				}
				//break;
			}
		}
	}

// static float_64_t calculateNumberOfNeededOverflowsInSecs(uint16_t compareSize){
// 	uint16_t prescaler_value = 0;
// 	switch(prescaler){
// 		case T0_NO_CLOCK:
// 			return 0;
// 		case T0_PRESCALER_NO:
// 			prescaler_value = 1;
// 			break;
// 		case T0_PRESCALER_8:
// 			prescaler_value = 8;
// 			break;
// 		case T0_PRESCALER_64:
// 			prescaler_value = 64;
// 			break;
// 		case T0_PRESCALER_256:
// 			prescaler_value = 256;
// 			break;
// 		case T0_PRESCALER_1024:
// 			prescaler_value = 1024;
// 			break;
// 	}	
// 	return ((((1/(1.0/MCU_FREQUECY))-1)/prescaler_value)/255);
// }

//----------------------------------timer_2-------------------------------------
void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC,En_timer2perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, uint8_t u8_assynchronous, En_timer2Interrupt_t en_interruptMask){
	Led_Init(LED_0);
	//set mode
	TCNT2 = 0;
	TCCR2 = 0;
	OCR2 = 0;
	ASSR = u8_assynchronous;
	
	TCCR2 |= en_mode;
	TCCR2 |= en_OC;

	//interrupt;
	TIMSK &= ~BIT6 &  ~BIT7;
	TIMSK |= en_interruptMask;

	//set initial values
	TCNT2 = u8_initialValue;
	OCR2 = u8_outputCompare;
	
	//enable/disable interrupt
	
	
	//set prescaler
	//TCCR0 |= en_prescal;
	T2_prescaler = en_prescal;
	
	//	T0overFlowNumberPerOneMicroSecond = (float_64_t)(calculateNumberOfNeededOverflowsInSecs(256)/1000000);
	//T0overFlowNumberPerOneMilliSecond = (float_64_t)(calculateNumberOfNeededOverflowsInSecs(256)/1000);
	//uint32_t overFlowsnum  = overFlowNumberPerOneMicroSec * u32_delay_in_us;
}

void timer2Set(uint8_t u8_a_value){
	TCNT2 = u8_a_value;
}

uint8_t timer2Read(void){
	return TCNT2;
}

void timer2Start(void){
	TCCR2 |=  T2_prescaler;
}

void timer2Stop(void){
	TCCR2 &= (T2_NO_CLOCK);
	T2overFlowsnum = 0;
}

void timer2DelayMs(uint16_t u16_delay_in_ms){
	uint8_t count = 0;
	uint64_t numOfOverFlows = 0;
	uint64_t numOfExtraTicks = 0;
	switch(T2_prescaler){
		case T2_NO_CLOCK:
			break;
		case T2_PRESCALER_NO:
			numOfOverFlows = 63;
			numOfExtraTicks =128 ;
			break;
		case T2_PRESCALER_8:
			numOfOverFlows = 8;
			numOfExtraTicks =208 ;
			break;
		case T2_PRESCALER_32:
// 			numOfOverFlows = 1;
// 			numOfExtraTicks =250 ;
			break;
		case T2_PRESCALER_64:
			numOfOverFlows = 1;
			numOfExtraTicks =250 ;
			break;
		case T2_PRESCALER_128:
// 			numOfOverFlows = 1;
// 			numOfExtraTicks =250 ;
 			break;
		case T2_PRESCALER_256:
			numOfOverFlows = 1;
			numOfExtraTicks =62 ;
			break;
		case T2_PRESCALER_1024:
			numOfOverFlows = 1;
			numOfExtraTicks = 22 ;
			break;
	}
	//cli();

	while(u16_delay_in_ms--){
	
		timer0Start();
		timer0Set(256 - numOfExtraTicks);
		while(1){
			while(!(TIFR & BIT0));
			TIFR |= BIT0;//reset flag
			count++;
			if(count == numOfOverFlows){
				count = 0;
				timer0Stop();
				TCNT0 = 0;
				break;
			}
			//break;
		}
	}

}
void timer2DelayUs(uint32_t u32_delay_in_us){
	uint64_t count = 0;
	T2overFlowsnum  = T2overFlowNumberPerOneMicroSecond * u32_delay_in_us;
	if((TIMSK & BIT6) == T2_POLLING){// interrupt disabled
		//cli();
		timer2Start();
		while(1){
			while(!(TIFR & BIT6));
			TIFR |= BIT6;//reset flag
			count++;
			if(count == (int)T2overFlowsnum){
				count = 0;
				timer2Stop();
				TCNT2 = 0;
				break;
			}
		}
	}
	else{// interrupt enabled
		sei();
		timer2Start();
	}
}


void timer2SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency){
	uint8_t CTC_value = 0;
	uint8_t interrupt_mask = 0;
	//freq/(prescaler * 1+256)
	if(u8_dutyCycle == 100){
		CTC_value = 0;
			interrupt_mask = (T2_INTERRUPT_NORMAL);
		}else if(u8_dutyCycle == 0){
			interrupt_mask = (T2_COMP_MODE);
		}else{
			CTC_value =(uint8_t)(256 * u8_dutyCycle / 100);
			interrupt_mask = (T2_INTERRUPT_NORMAL | T2_INTERRUPT_CMP);
	}
	//interrupt_mask = (T0_INTERRUPT_NORMAL | T0_INTERRUPT_CMP);
	sei();
	gpioPinDirection(T2_PWM_GPIO,T2_PWM_BIT,OUTPUT);
	
	switch(u8_frequency){
		case 200:
			PWM_TCNT_initialValue = 178;
			CTC_value =(uint8_t)((256-PWM_TCNT_initialValue) * u8_dutyCycle / 100)+PWM_TCNT_initialValue;
			timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_1024,PWM_TCNT_initialValue,CTC_value,interrupt_mask);
			timer0Start();
			break;
		case 100:
			PWM_TCNT_initialValue = 100;
			CTC_value =(uint8_t)((256-PWM_TCNT_initialValue) * u8_dutyCycle / 100)+PWM_TCNT_initialValue;
			timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_1024,PWM_TCNT_initialValue,CTC_value,interrupt_mask);
			timer0Start();
			break;
// 		case 1://1K
// 			PWM_TCNT_initialValue = 6;
// 			CTC_value =(uint8_t)((256-PWM_TCNT_initialValue) * u8_dutyCycle / 100)+PWM_TCNT_initialValue;
// 			timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,PWM_TCNT_initialValue,74,interrupt_mask);
// 			timer0Start();
// 			break;
// 		case 2://1K
// 			PWM_TCNT_initialValue = 132;
// 			CTC_value =(uint8_t)((256-PWM_TCNT_initialValue) * u8_dutyCycle / 100)+PWM_TCNT_initialValue;
// 			timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,PWM_TCNT_initialValue,CTC_value,interrupt_mask);
// 			timer0Start();
// 			break;
	}
	
	// 		PWM_TCNT_initialValue =256 - MCU_FREQUECY/(prescaler*u8_frequency);
	// 		timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,PWM_TCNT_initialValue,CTC_value,(T0_INTERRUPT_NORMAL | T0_INTERRUPT_CMP));
	// 		timer0Start();
	// 		PWM_TCNT_initialValue = 0;
}

