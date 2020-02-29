/*
 * SwICU.c
 *
 * Created: 29/01/2020 03:34:22 م
 *  Author: TOSHIBA
 */ 

#include"SwICU.h"

#define CLEAR_BIT(REG,BIT) (REG&=(~BIT))

#define SET_BIT(REG,BIT) (REG|=(BIT))

#define  SWICU_EDGE_MASK (0x40)

#define  INT2_INTER_FLAG_BIT  BIT5
#define  INT2_INTER_BIT       BIT5

#define GENERAL_INTERRUPT_BIT BIT7

#define TIMER_INI_VALUE    (0X00)



void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge){
	
	gpioPinDirection(EN_SW_ICU_PORT, EN_SW_ICU_PIN,INPUT);

	switch (a_en_inputCaptureEdge){
		
		case SwICU_EdgeFalling:
		
		CLEAR_BIT(MCUCSR,SWICU_EDGE_MASK);
		
		break;
		
		case SwICU_EdgeRisiging:
		
		SET_BIT(MCUCSR,SWICU_EDGE_MASK);
		
		break;
	}
   
  timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,
                T0_PRESCALER_64,TIMER_INI_VALUE,
				TIMER_INI_VALUE,
                   T0_POLLING);
				 
 	
}

EN_SwICU_Edge_t SwICU_GetCfgEdge(void){ 
	uint8_t state_register=MCUCSR& SWICU_EDGE_MASK;
	
	if(state_register==LOW)
		return SwICU_EdgeFalling ;
	else
	return SwICU_EdgeRisiging;
	
	}
	
void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdgeedge){
	
	CLEAR_BIT(GICR, INT2_INTER_BIT);
	
	switch( a_en_inputCaptureEdgeedge){
		
		case SwICU_EdgeFalling:
		
		CLEAR_BIT(MCUCSR,SWICU_EDGE_MASK);
		
		break;
		
		case SwICU_EdgeRisiging:
		
		SET_BIT(MCUCSR,SWICU_EDGE_MASK);
		
		break;
	}
	
	 SET_BIT(GICR, INT2_INTER_BIT);
	
}
 //read ICU timer 
void SwICU_Read(volatile uint8_t * a_pu8_capt){ //WHY volatile
	* a_pu8_capt= timer0Read();
}
//stop timer 
void SwICU_Stop(void){
	timer0Stop();
}
//start timer
//inil_tcnt
void SwICU_Start(void){
	timer0Set(TIMER_INI_VALUE);
	timer0Start();
}

//enable external interrupt 
void SwICU_Enable(void){
	 SET_BIT(GIFR,INT2_INTER_FLAG_BIT);
	 SET_BIT(GICR, INT2_INTER_BIT);   
     SET_BIT(SREG,GENERAL_INTERRUPT_BIT);
}

//disable external interrupt 
void SwICU_Disable(void){
	CLEAR_BIT(GICR,INT2_INTER_FLAG_BIT);
}

//  MY_ISR(TIMER0_OVF_vect){
// 	
// 	 volatile static  uint16_t num_of_ovr=0;
// 	if(re_start_count==1){
// 		num_of_ovr=0;
// 	    re_start_count=0;
// 		
// 	 num_of_ovr++; 
//  }
//  
 


 