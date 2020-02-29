

#include"timers.h"
#include"interrupts.h"  
	 #define F_CPU 16000000
	
	 // GENERAL DEFINATION 
	 #define CLEAR_BIT(REG,BIT) (REG&=~(BIT))
	 #define SET_BIT(REG,BIT) (REG|=(BIT))
	 #define READ_BIT(REG,BIT) (REG&(BIT))
	 
	 #define HIGH_BIT 1
	 #define LOW_BIT   0
	
	 // TIMER0 DEFINTION 
	  #define  T0_MASK_MODE  0x48
	 #define T0_DELAY_MILI_PRESCALER_VALUE 1024
	 

	 #define TIMERS1_2_RESELUTION1 256
   
    #define  TOV0_FLAG_BIT  0x01
	#define  T0_TIME_TOV_PRE_1024  16.384
	#define  T0_TIME_TOV_NO_PRE  0.016
   
    #define  T0_TICK_TIME_PRE_8  (0.5)
	
	//TIMER 1 DEFINE 
	 
	 #define T1_MASK_MODE  0x0318
	 #define T1_MASK_DIS_EN_I  0xC3
	 #define T1_RESLUTION 65536
	 #define  TOV1_FLAG_BIT  0x04
	 #define OC1A_FLAG_BIT 0x10
	
	#define T1_TICK_TIME_PRE_8  0.0005
	
	#define T1_TICK_TIME_PRE_8_IN_US (0.5)
	//#define T1_TICK_TIME_PRE_8  0.0000625 work wrong 
		
	 #define  TOV2_FLAG_BIT  0x40
	  #define  OC2_FLAG_BIT  0x80
	  #define T2_TIME_TOV_PRE_1024 16.384
	  #define T2_TIME_TOV_NO_PRE   0.016


static  En_timer0perscaler_t prescaler_0=T0_NO_CLOCK;
static  En_timer1perscaler_t prescaler_1=T1_NO_CLOCK;
static  En_timer0perscaler_t prescaler_2=T0_NO_CLOCK;



 static  volatile uint8_t tcnt0_on_pwm=0x00;
   
  static  volatile uint16_t tcnt1_on_pwm=0x00; 
  static  volatile uint8_t tcnt2_on_pwm=0x00;
 
 
 
 // Timer 0///

 void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,
                  En_timer0perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare,
                   En_timer0Interrupt_t en_interruptMask){
				    TCCR0=0x00;
			     	TCNT0=0x00;
			     	OCR0=0x00;
				   CLEAR_BIT(TIMSK,BIT0);
				   CLEAR_BIT(TIMSK,BIT1);
				   TCCR0 |= en_mode| en_OC0;
				   TCNT0 = u8_initialValue;
				   OCR0=u8_outputCompare;
				   prescaler_0=en_prescal;
				 TIMSK|=en_interruptMask;
				 if (en_interruptMask!=T0_POLLING)
				SET_BIT(SREG,BIT7);
				 
				   }
				   
				   
void timer0Set(uint8_t u8_value){
	TCNT0 =u8_value;

}

uint8_t timer0Read(void){
	return TCNT0;
}

	
void timer0Start(void){
	TCCR0|=prescaler_0;
}

void timer0Stop(void){
	TCCR0&=T0_NO_CLOCK;
}

void timer0DelayMs(uint16_t u16_delay_in_ms){  
	
	uint8_t prescaler=T0_PRESCALER_1024 ; 
	uint64_t count=0;
	f64_t  time_over_flow= T0_TIME_TOV_PRE_1024;
	f64_t  F_count=0;
	
	TCCR0=0x00;
	TCNT0=0x00;
	
	TCCR0|=T0_NORMAL_MODE|T0_OC0_DIS|T0_POLLING;
    SET_BIT(TIFR,TOV0_FLAG_BIT);
	 
	  
		if(u16_delay_in_ms< T0_TIME_TOV_PRE_1024){
		 prescaler=T0_PRESCALER_NO;
		 time_over_flow=T0_TIME_TOV_NO_PRE;
	 }
	 
	  F_count=u16_delay_in_ms/ time_over_flow;
	  
	  if(((F_count-(uint64_t)F_count)*1000)>0){
		  F_count++;
		  
		    TCNT0=(256*(1-(F_count-((uint64_t)F_count))));
	 }
	  TCCR0|= prescaler;
	  while(count<F_count){
		  while(READ_BIT(TIFR,TOV0_FLAG_BIT)== LOW_BIT );
		  count++;
		 SET_BIT(TIFR,TOV0_FLAG_BIT);
	  }
	 TCCR0&=T0_NO_CLOCK;	
	 	 
}

void timer0DelayUs(uint32_t u32_delay_in_us){

	uint8_t prescaler=T0_PRESCALER_8 ,
	         tcnt_value=0x00; 
	
	f64_t  F_count=0,G_count=1;
	uint64_t count=0;
	TCCR0=0x00;
	TCNT0=0x00;
	TCCR0|=T0_NORMAL_MODE|T0_OC0_DIS;
	SET_BIT(TIFR,TOV0_FLAG_BIT);
	 
	F_count=((u32_delay_in_us-72)/ T0_TICK_TIME_PRE_8);
	
	
	if( F_count<=256.0){
		
		tcnt_value=256-F_count;
		if(((F_count-(uint64_t)F_count)*1000)>0){ //if it fractin i have 2 choise tcnt_value--or keep it as it
		tcnt_value--;
		}	
	}
	else {     
		G_count=(F_count/256);
		
	   if(((G_count-(uint64_t)G_count)*1000)>0){
		 G_count++;
		 tcnt_value= 256*(1-((G_count-(uint64_t)G_count)*1000.0));
	   }
	}

	
	   TCNT0=tcnt_value;
	    TCCR0|= prescaler;
	   while(count<G_count){
		while(READ_BIT(TIFR,TOV0_FLAG_BIT)== LOW_BIT );
		SET_BIT(TIFR,TOV0_FLAG_BIT);
		count++; 
	   }
	TCCR0&=T0_NO_CLOCK;
}

void timer0SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency){
	uint8_t ocr_value=0;
	gpioPinDirection(T0_PWM_GPIO,T0_PWM_BIT,OUTPUT);
	TCCR0=0x00;
	TCCR0|=(T0_NORMAL_MODE|T0_OC0_DIS);
	SET_BIT(TIFR,TOV0_FLAG_BIT);
	SET_BIT(TIFR,BIT1);
	TIMSK|=T0_INTERRUPT_NORMAL|T0_INTERRUPT_CMP;
	SET_BIT(SREG,BIT7);
	
if(u8_dutyCycle==100){
TIMSK&=~T0_INTERRUPT_CMP;
	
}
else if(u8_dutyCycle==0){
TIMSK&=~T0_INTERRUPT_NORMAL;
}
	 switch(u8_frequency) {
		 case 100:
		 tcnt0_on_pwm=100;
		  ocr_value=((256- tcnt0_on_pwm)*(u8_dutyCycle/100.0))+tcnt0_on_pwm;
           break;
		   
		   case 200:
		   tcnt0_on_pwm=178;
		    ocr_value=((256- tcnt0_on_pwm)*(u8_dutyCycle/100.0))+tcnt0_on_pwm;
	break;
	 }
	
	TCNT0= tcnt0_on_pwm;
	OCR0=ocr_value;
	TCCR0|=T0_PRESCALER_1024;


}
//  MY_ISR(TIMER0_OVF_vect){
//  gpioPinWrite(T0_PWM_GPIO,T0_PWM_BIT,HIGH);
//  TCNT0=tcnt0_on_pwm;
//  //start_pwm0=1;
//  }

// MY_ISR(TIMER0_COMP_vect){
// 	gpioPinWrite(T0_PWM_GPIO,T0_PWM_BIT,LOW);
// }

/////     timer 1//////////

void timer1Init(En_timer1Mode_t en_mode,
                En_timer1OC_t en_OC,
				En_timer1perscaler_t en_prescal,
				uint16_t u16_initialValue, 
			    uint16_t u16_outputCompareA,
				uint16_t u16_outputCompareB,
				uint16_t u16_inputCapture,
				En_timer1Interrupt_t en_interruptMask){
					
							    TCCR1=0x0000;
							    TCNT1=0x0000;
							    OCR1A=0x0000;
								OCR1B=0x0000;
								ICR1=0x0000;
							    CLEAR_BIT(TIMSK,BIT2);
							    CLEAR_BIT(TIMSK,BIT3);
								CLEAR_BIT(TIMSK,BIT4);
								CLEAR_BIT(TIMSK,BIT5);
							    TCCR1 |= en_mode| en_OC;
								
								 TCNT1 = u16_initialValue;
								 OCR1A=u16_outputCompareA;
								 OCR1B=u16_outputCompareB;
								 ICR1=u16_inputCapture;
								 
							    prescaler_1=en_prescal;
							    TIMSK|=en_interruptMask;
								 if (en_interruptMask!=T1_POLLING)
								 SET_BIT(SREG,BIT7);
						
					
				}
				


void timer1Set(uint16_t u16_value){
	uint8_t register_status=TIMSK;
	TIMSK&=T1_MASK_DIS_EN_I ;
	TCNT1 =u16_value;
	TIMSK=register_status;
}

uint16_t timer1Read(void){
	//uint8_t tccr1_status_register_=TCCR1;
	uint8_t timsk_status_register=TIMSK;
	uint16_t tcnt_value;
	//TCCR1&=T1_NO_CLOCK;//DOES READ STOP COUNT !
	TIMSK&=T1_MASK_DIS_EN_I ;
	tcnt_value=TCNT1;
	//TCCR1=tccr1_status_register_;
	TIMSK=timsk_status_register;
	return tcnt_value;
}

void timer1Start(void){
TCCR1|=prescaler_1;
}

void timer1Stop(void){
		TCCR1B&=T1_NO_CLOCK;
}

void timer1DelayMs(uint16_t u16_delay_in_ms){
		uint16_t tcnt_value=0x0000;
		f64_t  F_count=0,G_count=1;
		uint64_t count=0;
		TCCR1=0x0000;
		TCNT1=0x0000;
		TCCR1|=T1_NORMAL_MODE|T1_OC1_DIS|T1_POLLING;
		SET_BIT(TIFR,TOV1_FLAG_BIT);


		F_count=(u16_delay_in_ms/ T1_TICK_TIME_PRE_8);
		
		if( F_count>T1_RESLUTION)  {
			G_count=(F_count/T1_RESLUTION);
			
			if(((G_count-(uint64_t)G_count)*1000)>0){
				G_count++;
				//tcnt_value= 256*(1-((G_count-(uint64_t)G_count)*1000.0));
				tcnt_value= T1_RESLUTION*(1.0-(G_count-(uint64_t)G_count));
			}
		}

		else{
			
			tcnt_value=(T1_RESLUTION-F_count);
		}
		TCNT1=tcnt_value;
		TCCR1|= T1_PRESCALER_8;
		while(count<G_count){
			while(READ_BIT(TIFR,TOV1_FLAG_BIT)== LOW_BIT );
			SET_BIT(TIFR,TOV1_FLAG_BIT);
			count++;
		}
		
		TCCR1=0x0000;
	}



void timer1DelayUs(uint32_t u32_delay_in_us){//incorrect +42US
	uint16_t tcnt_value=0x0000;
	f64_t  F_count=0,G_count=1;
	uint64_t count=0;
	TCCR1=0x0000;
	TCNT1=0x0000;
	TCCR1|=T1_NORMAL_MODE|T1_OC1_DIS|T1_POLLING;
	SET_BIT(TIFR,TOV1_FLAG_BIT);


	F_count=(u32_delay_in_us/ T1_TICK_TIME_PRE_8_IN_US);
	
	if( F_count>T1_RESLUTION)  {
		G_count=(F_count/T1_RESLUTION);
		
		if(((G_count-(uint64_t)G_count)*1000)>0){
			G_count++;
			//tcnt_value= 256*(1-((G_count-(uint64_t)G_count)*1000.0));
			tcnt_value= T1_RESLUTION*(1.0-(G_count-(uint64_t)G_count));
		}
	}

	else{
		
		tcnt_value=(T1_RESLUTION-F_count);
	}
	TCNT1=tcnt_value;
	TCCR1|= T1_PRESCALER_8;
	while(count<G_count){
		while(READ_BIT(TIFR,TOV1_FLAG_BIT)== LOW_BIT );
		SET_BIT(TIFR,TOV1_FLAG_BIT);
		count++;
	}
	
	//TCCR1&=T1_NO_CLOCK;
	TCCR1=0x0000;
}

void timer1SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency){	
	 uint16_t ocr_value=0;
	gpioPinDirection(T1_PWM_GPIO,T1_PWM_BIT,OUTPUT);
	TCCR1=0x0000;
	TCCR1|=(T1_NORMAL_MODE|T1_OC1_DIS);
	
	SET_BIT(TIFR,TOV1_FLAG_BIT);
	SET_BIT(TIFR,OC1A_FLAG_BIT);
	SET_BIT(TIFR,0x08);
	

	TIMSK|=T1_INTERRUPT_NORMAL|T1_INTERRUPT_CMP_1A;

	switch (u8_dutyCycle){
		case 100:
		TIMSK&=~T1_INTERRUPT_CMP_1A;
		break;
		case 0:
		TIMSK&=~T1_INTERRUPT_NORMAL;
		break;
	}
	
	SET_BIT(SREG,BIT7);
	switch(u8_frequency) {
		case 100:
		tcnt1_on_pwm=65380;
		ocr_value=((T1_RESLUTION- tcnt1_on_pwm)*(u8_dutyCycle/100.0))+tcnt1_on_pwm;
		break;
		
		case 200:
		tcnt1_on_pwm=65458;
		ocr_value=((T1_RESLUTION- tcnt1_on_pwm)*(u8_dutyCycle/100.0))+tcnt1_on_pwm;
		break;
	}
	
	TCNT1= tcnt1_on_pwm;
	OCR1A=ocr_value;
	gpioPinWrite(T1_PWM_GPIO,T1_PWM_BIT,HIGH);
	TCCR1|=T1_PRESCALER_1024;

}
// MY_ISR(TIMER1_OVF_vect){
// 	gpioPinWrite(T1_PWM_GPIO,T1_PWM_BIT,HIGH);
// 	TCNT1=tcnt1_on_pwm;
// }

// MY_ISR(TIMER1_COMPA_vect){
// 	gpioPinWrite(T1_PWM_GPIO,T1_PWM_BIT,LOW);
// }

	


//===========================Timer2 Control===============================*/

void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC,
                En_timer2perscaler_t en_prescal, uint8_t u8_initialValue,
				 uint8_t u8_outputCompare, uint8_t u8_assynchronous,
				  En_timer2Interrupt_t en_interruptMask){
					  
					   TCCR2=0x00;
					   TCNT2=0x00;
					   OCR2=0x00;
					   CLEAR_BIT(TIMSK,BIT6);
					   CLEAR_BIT(TIMSK,BIT7);
					   TCCR2 |= en_mode| en_OC;
					   prescaler_2=en_prescal;
					   TIMSK|=en_interruptMask;
					   TCNT2 = u8_initialValue;
					   OCR2=u8_outputCompare;
					   CLEAR_BIT(ASSR,BIT3);
					    if (en_interruptMask!=T2_POLLING){
						    SET_BIT(SREG,BIT7);
					    }
					
				  }

void timer2Set(uint8_t u8_a_value){

	TCNT0 =u8_a_value;

}


uint8_t timer2Read(void){
	return TCNT2;
	
}

void timer2Start(void){
	TCCR2=prescaler_2;
}


void timer2Stop(void){
	TCCR2&=T2_NO_CLOCK;
}

void timer2DelayMs(uint16_t u16_delay_in_ms){
	uint8_t prescaler=T2_PRESCALER_1024 ;
	uint64_t count=0;
	f64_t  time_over_flow= T2_TIME_TOV_PRE_1024;
	f64_t  F_count=0;
	TCCR2=0x00;
	TCNT2=0x00;
	TCCR2|=T2_NORMAL_MODE|T2_OC2_DIS;
	SET_BIT(TIFR,TOV2_FLAG_BIT);
	
	
	if(u16_delay_in_ms< T2_TIME_TOV_PRE_1024){
		prescaler=T2_PRESCALER_NO,
		
		time_over_flow=T2_TIME_TOV_NO_PRE;
	}
	
	F_count=(u16_delay_in_ms)/ time_over_flow;
	
	if(((F_count-(uint64_t)F_count)*1000)>0){
		F_count++;
		
		TCNT2=(uint8_t)(256*(1-(F_count-((uint64_t)F_count))));
	}
	TCCR2|= prescaler;
	while(count<F_count){
		while(READ_BIT(TIFR,TOV2_FLAG_BIT)== LOW_BIT );
		count++;
		SET_BIT(TIFR,TOV2_FLAG_BIT);
	}
	TCCR2&=T2_NO_CLOCK;
}

void timer2DelayUs(uint32_t u32_delay_in_us){// UNcoreect delay
	uint8_t prescaler=T2_PRESCALER_8,
	tcnt_value=0x00;
	 
	f64_t  F_count=0,G_count=1;
	uint64_t count=0;
	
	TCCR2=0x00;
	TCNT2=0x00;
	TCCR2|=T2_NORMAL_MODE|T2_OC2_DIS;
 	SET_BIT(TIFR,TOV2_FLAG_BIT);

	F_count=(u32_delay_in_us/ T0_TICK_TIME_PRE_8);
	
	if( F_count>256)  {
		G_count=(F_count/256);
		
		if(((G_count-(uint64_t)G_count)*1000)>0){
		    G_count++;
			//tcnt_value= 256*(1-((G_count-(uint64_t)G_count)*1000.0));
			tcnt_value= 256*(1.0-(G_count-(uint64_t)G_count));
		}
	}

	else{
		
		tcnt_value=(256-F_count);
	}
	TCNT2=tcnt_value;
	TCCR2|= prescaler;
	while(count<G_count){
		while(READ_BIT(TIFR,TOV2_FLAG_BIT)== LOW_BIT );
		SET_BIT(TIFR,TOV2_FLAG_BIT);
		count++;
	}
	TCCR2&=T2_NO_CLOCK;
}


 void timer2SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency){
	 uint8_t ocr_value=0;
 gpioPinDirection(T2_PWM_GPIO,T2_PWM_BIT,OUTPUT);
 TCCR2=0x00;
 TCCR2|=(T2_NORMAL_MODE|T2_OC2_DIS);
 
 SET_BIT(TIFR,TOV2_FLAG_BIT);
 SET_BIT(TIFR,OC2_FLAG_BIT);

TIMSK|=T2_INTERRUPT_NORMAL|T2_INTERRUPT_CMP;

switch (u8_dutyCycle){
 case 100:
	 TIMSK&=~T2_INTERRUPT_CMP;
	 break;
 case 0:
	 TIMSK&=~T2_INTERRUPT_NORMAL;
	 break;
 }
 
 SET_BIT(SREG,BIT7);
 switch(u8_frequency) {
	 case 100:
	 tcnt2_on_pwm=100;
	 ocr_value=((256- tcnt2_on_pwm)*(u8_dutyCycle/100.0))+tcnt2_on_pwm;
	 break;
	 
	 case 200:
	 tcnt2_on_pwm=178;
	 ocr_value=((256- tcnt2_on_pwm)*(u8_dutyCycle/100.0))+tcnt2_on_pwm;
	 break;
 }
 
 TCNT2= tcnt2_on_pwm;
 OCR2=ocr_value;
 gpioPinWrite(T2_PWM_GPIO,T2_PWM_BIT,HIGH);
 TCCR2|=T2_PRESCALER_1024;

 }
//  MY_ISR(TIMER2_OVF_vect){
// 	 gpioPinWrite(T2_PWM_GPIO,T2_PWM_BIT,HIGH);
// 	 TCNT2=tcnt2_on_pwm;
//  }

//  MY_ISR(TIMER2_COMP_vect){
// 	 gpioPinWrite(T2_PWM_GPIO,T2_PWM_BIT,LOW);
//  }
















// 
// void timer0DelayUs(uint32_t u32_delay_in_us){
// 
// 	uint8_t prescaler=T0_PRESCALER_8 ,
// 	tcnt_value=0x00,
// 	register_status=TCCR0;  //not important register_status
// 	
// 	f64_t  F_count=0,G_count=1;
// 	uint64_t count=0;
// 	
// 
// 	TCCR0=0x00;
// 	TCNT0=0x00;
// 	TCCR0|=T0_NORMAL_MODE|T0_OC0_DIS;
// 	SET_BIT(TIFR,TOV0_FLAG_BIT);
// 	
// 	F_count=(u32_delay_in_us/ T0_TICK_TIME_PRE_8);
// 	
// 	if( F_count>256)  {
// 		G_count=(F_count/256);
// 		
// 		if(((G_count-(uint64_t)G_count)*1000)>0){
// 			G_count++;
// 			tcnt_value= 256*(1-((G_count-(uint64_t)G_count)*1000.0));
// 		}
// 	}



