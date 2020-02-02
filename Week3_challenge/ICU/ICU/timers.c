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


// INTERRUPT_SERVICE_ROTINE(TIMER0_OVF_vector){
// // 	counter_ov_t0++;
// // 	if(counter_ov_t0 == (int)T0overFlowsnum){
// // 		counter_ov_t0 = 0;
// // 		T0TimeReachedFlag = 1;
// // 	}
// 	gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT_M1,HIGH);
// 	gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT_M2,HIGH);
// 	timer0Set(PWM_TCNT_initialValue);
// }
volatile uint32_t T0_Overflow = 0;

// INTERRUPT_SERVICE_ROTINE(TIMER0_OVF_vector){
// 	T0_Overflow ++;	
// 		//gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT_M1,HIGH);
// 		//gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT_M2,HIGH);
// 		//TCNT0 = PWM_TCNT_initialValue;
//  		Led_Init(LED_2);
//  		Led_On(LED_2);
// 		Led_Off(LED_3);
// }
// 
// INTERRUPT_SERVICE_ROTINE(TIMER0_COMP_vector){
//  	Led_Init(LED_3);
//  	Led_On(LED_3);
// 	Led_Off(LED_2);
// 	gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT_M1,LOW);
// 	gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT_M2,LOW);
// }

INTERRUPT_SERVICE_ROTINE(TIMER2_OVF_vector){
// 	counter_ov_t0++;
// 	if(counter_ov_t0 == (int)T0overFlowsnum){
// 		counter_ov_t0 = 0;
// 		T0TimeReachedFlag = 1;
// 	}
	gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT_M1,HIGH);
	gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT_M2,HIGH);
	timer0Set(PWM_TCNT_initialValue);
}

INTERRUPT_SERVICE_ROTINE(TIMER2_COMP_vector){
	gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT_M1,LOW);
	gpioPinWrite(T0_PWM_GPIO, T0_PWM_BIT_M2,LOW);
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
	if(en_interruptMask != T0_POLLING){
		sei();
	}
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
	gpioPinDirection(T0_PWM_GPIO,T0_PWM_BIT_M1,OUTPUT);
	gpioPinDirection(T0_PWM_GPIO,T0_PWM_BIT_M2,OUTPUT);
		switch(u8_frequency){
			case 200:
				PWM_TCNT_initialValue = 178;
				CTC_value =(uint8_t)((256-PWM_TCNT_initialValue) * u8_dutyCycle / 100)+PWM_TCNT_initialValue;
				timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_1024,PWM_TCNT_initialValue,CTC_value,interrupt_mask);
				timer0Start();
				//Led_On(LED_3);
				break;
			case 100:
// 				PWM_TCNT_initialValue = 100;
				PWM_TCNT_initialValue = 100;
				CTC_value =(uint8_t)((256-PWM_TCNT_initialValue) * u8_dutyCycle / 100)+PWM_TCNT_initialValue;
				timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_1024,PWM_TCNT_initialValue,CTC_value, interrupt_mask);
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
 		PWM_TCNT_initialValue = 0;
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
			timer2Init(T2_NORMAL_MODE,T2_OC2_DIS,T2_PRESCALER_1024,PWM_TCNT_initialValue,CTC_value,0x00,interrupt_mask);
			timer2Start();
			break;
		case 100:
			PWM_TCNT_initialValue = 100;
			CTC_value =(uint8_t)((256-PWM_TCNT_initialValue) * u8_dutyCycle / 100)+PWM_TCNT_initialValue;
			timer2Init(T2_NORMAL_MODE,T2_OC2_DIS,T2_PRESCALER_1024,PWM_TCNT_initialValue,CTC_value,0x00,interrupt_mask);
			timer2Start();
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


void HwPWMInit(void){ 
		
}

void HwPWMSetDuty(uint8_t a_u8_duty, uint32_t a_u32_frequency){
	
}

/***************************************************************************
*Timer1 functions
*/

// 
// void timer1Init(En_timer1Mode_t en_mode,En_timer1OC_t en_OC,En_timer1perscaler_t en_prescal, uint16_t u16_initialValue, uint16_t u16_outputCompareA, uint16_t u16_outputCompareB,uint16_t u16_inputCapture, En_timer1Interrupt_t en_interruptMask)
// {
// 
//    switch (en_mode)
//    {
//       case T1_NORMAL_MODE :
//       TCCR1A &= TCCR1A_VALUE_FOR_NORMAL_MODE ;
//       TCCR1B &= TCCR1B_VALUE_FOR_NORMAL_MODE ;
//       break;
// 
//       case T1_COMP_MODE_OCR1A_TOP : 
//       TCCR1A &= TCCR1A_VALUE_FOR_COMPA_MODE ;
//       TCCR1B |= TCCR1B_VALUE_FOR_COMPAL_MODE ;
//       break;
// 
// 		case T1_COMP_MODE_ICR1_TOP :
// 		TCCR1A &= TCCR1A_VALUE_FOR_COMP_ICR_MODE ;
// 		TCCR1B |= TCCR1B_VALUE_FOR_COMP_ICR_MODE ;
// 		break;
//    }
// 
// 	switch (en_OC)
// 	{
// 	   case T1_OC1_DIS:
// 		TCCR1A &= TCCR1A_VALUE_FOR_OC1_DISCONNECT ;
// 		break;
// 
// 		case T1_OC1A_CLEAR:
// 		TCCR1A &= TCCR1A_VALUE_FOR_OC1A_CLEAR ;
// 		break;
// 
// 		case T1_OC1A_SET:
// 		TCCR1A &= TCCR1A_VALUE_FOR_OC1A_SET ;
// 		break;
// 
// 		case T1_OC1A_TOGGLE:
// 		TCCR1A &= TCCR1A_VALUE_FOR_OC1A_TOGGLE ;
// 		break;
// 
// 		case T1_OC1B_CLEAR:
// 		TCCR1A &= TCCR1A_VALUE_FOR_OC1B_CLEAR ;
// 		break;
// 
// 		case T1_OC1B_SET:
// 		TCCR1A &= TCCR1A_VALUE_FOR_OC1B_SET ;
// 		break;
// 
// 		case T1_OC1B_TOGGLE:
// 		TCCR1A &= TCCR1A_VALUE_FOR_OC1B_TOGGLE;
// 		break;
// 	}
// 
// 	gen_Pre_Scaler_T1 = en_prescal;
// 	
// 	au8_Temp_For_Low_Bit = u16_initialValue;
// 	au8_Temp_For_Hight_Bit = (u16_initialValue SHIFT_8_BIT_RIGHT);
// 	
// 	TCNT1H = au8_Temp_For_Hight_Bit;
// 	TCNT1L = au8_Temp_For_Low_Bit;
// 
// 	au8_Temp_For_Low_Bit = u16_outputCompareA;
// 	au8_Temp_For_Hight_Bit = (u16_outputCompareA SHIFT_8_BIT_RIGHT);
// 
// 	OCR1AH = au8_Temp_For_Hight_Bit;
// 	OCR1AL = au8_Temp_For_Low_Bit;
// 
// 	au8_Temp_For_Low_Bit = u16_outputCompareB;
// 	au8_Temp_For_Hight_Bit = (u16_outputCompareB SHIFT_8_BIT_RIGHT);
// 
// 	OCR1BH = au8_Temp_For_Hight_Bit;
// 	OCR1BL = au8_Temp_For_Low_Bit;
// 
// 	au8_Temp_For_Low_Bit = u16_inputCapture;
// 	au8_Temp_For_Hight_Bit = (u16_inputCapture SHIFT_8_BIT_RIGHT);
// 
// 	ICR1H = au8_Temp_For_Hight_Bit;
// 	ICR1L = au8_Temp_For_Low_Bit;
// 
// 	TIMSK &= 0xC3;
// 	TIMSK |= en_interruptMask;
// 
// }
// 
// void timer1Set(uint16_t u16_value)
// {
//    au8_Temp_For_Low_Bit = u16_value;
//    au8_Temp_For_Hight_Bit = (u16_value SHIFT_8_BIT_RIGHT);
//    
// 	
// 	
// 	timer1Stop();
// 
//    TCNT1H = au8_Temp_For_Hight_Bit;
//    TCNT1L = au8_Temp_For_Low_Bit;
// 
// 	
// 
// 	timer1Start();
// }
// 
// 
// void timer1OCRSet(uint16_t u16_value)
// {
// 	au8_Temp_For_Low_Bit = u16_value;
// 	au8_Temp_For_Hight_Bit = (u16_value SHIFT_8_BIT_RIGHT);
// 	
// 	
// 	
// 	timer1Stop();
// 
// 	OCR1AH = au8_Temp_For_Hight_Bit;
// 	OCR1AL = au8_Temp_For_Low_Bit;
// 
// 	
// 
// 	timer1Start();
// }
// 
// 
// uint16_t timer1Read(void)
// {
//    timer1Stop();
// 	
// 	au8_Temp_For_Low_Bit = TCNT1L;
// 	au8_Temp_For_Hight_Bit = TCNT1H;
// 
// 	timer1Start();
// 	return (au8_Temp_For_Low_Bit | (au8_Temp_For_Hight_Bit SHIFT_8_BIT_LEFT));
// }
// 
// void timer1Start(void)
// {
//    TCCR1B |= gen_Pre_Scaler_T1;
// }
// 
// void timer1Stop(void)
// {
//    TCCR1B &= TCCR1B_VALUE_TO_STOP_TIMER1 ;
// }
// 
// void timer1DelayMs(uint16_t u16_delay_in_ms)
// {
//    uint16_t au16_Counter_Of_T1_ms;
// 	uint16_t au16_Timer1_Initial_Value;
// 	//uint8_t  au8_Counter_Of_Over_Flows = ZERO_VALUE;
// 	switch(gen_Pre_Scaler_T1)
// 	{
// 		case T0_PRESCALER_NO :
// 		au16_Timer1_Initial_Value = TIMER1_INITIAL_VALUE_FOR_NO_PRESCALER_MS ;
// 		break;
// 
// 		case T0_PRESCALER_8 :
// 		au16_Timer1_Initial_Value = IMER1_INITIAL_VALUE_FOR_8_PRESCALER_MS ;
// 		break;
// 
// 		case T0_PRESCALER_64 :
// 		au16_Timer1_Initial_Value = IMER1_INITIAL_VALUE_FOR_64_PRESCALER_MS ;
// 		break;
// 
// 		default:
// 		au16_Timer1_Initial_Value = ZERO_VALUE ;
// 		break;
// 
// 	}
// 
// 	for (au16_Counter_Of_T1_ms = u16_delay_in_ms; au16_Counter_Of_T1_ms > LOWEST_VALUE; au16_Counter_Of_T1_ms--)
// 	{
// 		/*Initialize the TCCR0 with specific value that will achieve the part of ms
// 		*according to the prescaler
// 		*/
// 		timer1Set(au16_Timer1_Initial_Value);
// 		timer1Start();
// 			/*stay here waiting for timer0 over flow flag to be set
// 			*/
// 			while (!TOV1);
// 
// 			/*Reset the timer0 over flow flag by putting logical 1 in it
// 			*/
// 			RESETTOV1 ;
// 		timer1Stop();
// 	}
// }
// 
// void timer1SwPWM(uint8_t u8_dutyCycle,En_timer1Frequency_t u8_frequency)
// {
// 
//    SREG |= BIT7;
//    switch (u8_frequency)
// 	{
// 	   case T1_100_frequency:
// 	   au16_T1_PWM_Initial_Value = TIMER1_PWM_INITIAL_VALUE_FOR_100HZ ;
// 	   au16_T1_PWM_Duty_Cycle = (au16_T1_PWM_Initial_Value + ((TOTAL_PERCENT - u8_dutyCycle) * TIMER1_NUMBER_OF_TICKS_FOR_PWM_100HZ));
// 	   timer1Init(T1_NORMAL_MODE,T1_OC1_DIS,T1_PRESCALER_64,au16_T1_PWM_Initial_Value,au16_T1_PWM_Duty_Cycle,0x00,0x00,T1_INTERRUPT_NORMAL);
// 	   TIMSK |= T1_INTERRUPT_CMP_1A;
// 	   break;
// 		
// 		case T1_1k_Frequency:
// 		au16_T1_PWM_Initial_Value = TIMER1_PWM_INITIAL_VALUE_FOR_1K ;
// 		au16_T1_PWM_Duty_Cycle = (au16_T1_PWM_Initial_Value + ((TOTAL_PERCENT - u8_dutyCycle) * TIMER1_NUMBER_OF_TICKS_FOR_PWM_1K ));
// 	   timer1Init(T1_NORMAL_MODE,T1_OC1_DIS,T1_PRESCALER_8,au16_T1_PWM_Initial_Value,au16_T1_PWM_Duty_Cycle,0x00,0x00,T1_INTERRUPT_NORMAL);
// 		TIMSK |= T1_INTERRUPT_CMP_1A;
// 		break;
// 
// 		case T1_2k_Frequency:
// 		au16_T1_PWM_Initial_Value = TIMER1_PWM_INITIAL_VALUE_FOR_2K ;
// 		au16_T1_PWM_Duty_Cycle = (au16_T1_PWM_Initial_Value + ((TOTAL_PERCENT - u8_dutyCycle) * TIMER1_NUMBER_OF_TICKS_FOR_PWM_2K));
// 		timer1Init(T1_NORMAL_MODE,T1_OC1_DIS,T1_PRESCALER_8,au16_T1_PWM_Initial_Value,au16_T1_PWM_Duty_Cycle,0x00,0x00,T1_INTERRUPT_NORMAL);
// 		TIMSK |= T1_INTERRUPT_CMP_1A;
// 		break;
// 
// 		case T1_5k_Frequency:
// 		au16_T1_PWM_Initial_Value = TIMER1_PWM_INITIAL_VALUE_FOR_5K ;
// 		au16_T1_PWM_Duty_Cycle = (au16_T1_PWM_Initial_Value + ((TOTAL_PERCENT - u8_dutyCycle) * TIMER1_NUMBER_OF_TICKS_FOR_PWM_5K ));
// 		timer1Init(T1_NORMAL_MODE,T1_OC1_DIS,T1_PRESCALER_8,au16_T1_PWM_Initial_Value,au16_T1_PWM_Duty_Cycle,0x00,0x00,T1_INTERRUPT_NORMAL);
// 		TIMSK |= T1_INTERRUPT_CMP_1A;
// 		break;
// 
// 		case T1_10k_Frequency:
// 		au16_T1_PWM_Initial_Value = TIMER1_PWM_INITIAL_VALUE_FOR_10K ;
// 		au16_T1_PWM_Duty_Cycle = (au16_T1_PWM_Initial_Value + ((TOTAL_PERCENT - u8_dutyCycle) * TIMER1_NUMBER_OF_TICKS_FOR_PWM_10K));
// 		timer1Init(T1_NORMAL_MODE,T1_OC1_DIS,T1_PRESCALER_NO,au16_T1_PWM_Initial_Value,au16_T1_PWM_Duty_Cycle,0x00,0x00,T1_INTERRUPT_NORMAL);
// 		TIMSK |= T1_INTERRUPT_CMP_1A;
// 		break;
// 	}
// 	timer1Start();
// 
// }