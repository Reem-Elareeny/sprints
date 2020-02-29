/*
 * sevenSeg.c
 *
 * Created: 18/01/2020 02:42:45 م
 *  Author: TOSHIBA
 */ 
#include "sevenSeg.h"

void sevenSegInit(En_SevenSegId_t a_segment_id){
	
	gpioPinDirection(SEG_BCD_GPIO,SEG_BCD_BITS,OUTPUT);
	gpioPinDirection(SEG_BCD_DP_GPIO,SEG_BCD_DP_BIT,OUTPUT);
	
	switch(a_segment_id){
		
		case SEG_0:
	gpioPinDirection(SEG_EN1_GPIO,SEG_EN1_BIT,OUTPUT);
	break;
	
	case SEG_1:
	gpioPinDirection(SEG_EN2_GPIO,SEG_EN2_BIT,OUTPUT);
	break;
	
	case SEG_2:
	gpioPinDirection(SEG_EN3_GPIO,SEG_EN3_BIT,OUTPUT);
	break;
	
	case SEG_3:
	gpioPinDirection(SEG_EN4_GPIO,SEG_EN4_BIT,OUTPUT);
	break;
		
	}
	
}

void sevenSegEnable(En_SevenSegId_t en_segment_id){
	switch(en_segment_id){
		
		case SEG_0:
		gpioPinWrite(SEG_EN1_GPIO,SEG_EN1_BIT,HIGH);
		break;
		
		case SEG_1:
		gpioPinWrite(SEG_EN2_GPIO,SEG_EN2_BIT,HIGH);
		break;
		
		case SEG_2:
		gpioPinWrite(SEG_EN3_GPIO,SEG_EN3_BIT,HIGH);
		break;
		
		case SEG_3:
		gpioPinWrite(SEG_EN4_GPIO,SEG_EN4_BIT,HIGH);
		break;
		
	}
	
}

void sevenSegDisable(En_SevenSegId_t en_segment_id){
	switch(en_segment_id){
		
		case SEG_0:
		gpioPinWrite(SEG_EN1_GPIO,SEG_EN1_BIT,LOW);
		break;
		
		case SEG_1:
		gpioPinWrite(SEG_EN2_GPIO,SEG_EN2_BIT,LOW);
		break;
		
		case SEG_2:
		gpioPinWrite(SEG_EN3_GPIO,SEG_EN3_BIT,LOW);
		break;
		
		case SEG_3:
		gpioPinWrite(SEG_EN4_GPIO,SEG_EN4_BIT,LOW);
		break;
		
	}
	
}

void sevenSegWrite(En_SevenSegId_t en_segment_id, uint8_t u8_number){
	
// 		gpioPinWrite(SEG_EN1_GPIO,SEG_EN1_BIT,LOW);
// 		gpioPinWrite(SEG_EN2_GPIO,SEG_EN2_BIT,LOW);
// 		gpioPinWrite(SEG_EN3_GPIO,SEG_EN3_BIT,LOW);
// 		gpioPinWrite(SEG_EN4_GPIO,SEG_EN4_BIT,LOW);
		
		//gpioPinWrite(SEG_BCD_GPIO,SEG_BCD_BITS,u8_number);
		PORTB_DATA=((PORTB_DATA&0xf0)|(u8_number&0x0F));
		
	switch(en_segment_id){
	
		case SEG_0:
		gpioPinWrite(SEG_EN1_GPIO,SEG_EN1_BIT,HIGH);
		
		break;
		
		case SEG_1:
		gpioPinWrite(SEG_EN2_GPIO,SEG_EN2_BIT,HIGH);
		
		break;
		
		case SEG_2:
		gpioPinWrite(SEG_EN3_GPIO,SEG_EN3_BIT,HIGH);
		break;
		
		case SEG_3:
		gpioPinWrite(SEG_EN4_GPIO,SEG_EN4_BIT,HIGH);
		
		break;
		
	}
}