/*
 * registers.h
 *
 * Created: 2/15/2020 11:07:24 PM
 *  Author: Reem el-Areeny
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

/************************************************************************/
/*				                    INCLUDES	                 		         */
/************************************************************************/
#include "std_types.h"

/************************************************************************/
/*		                   GENERAL REGISTERS		                        */
/************************************************************************/
#define MCUCR	        *((reg_type8_t)0x55)

#define MCUCSR	        *((reg_type8_t)0x54)
#define GICR	        *((reg_type8_t)0x5B)
#define GIFR	        *((reg_type8_t)0x5A)


/************************************************************************/
/*		                     PORTS REGISTERS		                        */
/************************************************************************/
#define PORTA_DATA      *((reg_type8_t)0x3B)
#define PORTA_DIR       *((reg_type8_t)0x3A)
#define PORTA_PIN	      *((reg_type8_t)0x39)

#define PORTB_DATA 	    *((reg_type8_t)0x38)
#define PORTB_DIR  	    *((reg_type8_t)0x37)
#define PORTB_PIN	       *((reg_type8_t)0x36)

#define PORTC_DATA 	    *((reg_type8_t)0x35)
#define PORTC_DIR  	    *((reg_type8_t)0x34)
#define PORTC_PIN	       *((reg_type8_t)0x33)


#define PORTD_DATA 	    *((reg_type8_t)0x32)
#define PORTD_DIR  	    *((reg_type8_t)0x31)
#define PORTD_PIN	       *((reg_type8_t)0x30)


/************************************************************************/
/*		                GENERAL TIMER REGISTERS		                     */
/************************************************************************/
#define TIMSK		    *((reg_type8_t)0x59)
#define TIFR		    *((reg_type8_t)0x58)


/************************************************************************/
/*		                    TIMER0 REGISTERS		                        */
/************************************************************************/
#define TCCR0	    	*((reg_type8_t)0x53)
#define TCNT0	    	*((reg_type8_t)0x52)
#define OCR0	    	*((reg_type8_t)0x5C)


/************************************************************************/
/*		                    TIMER1 REGISTERS		                        */
/************************************************************************/
#define TCCR1A			*(reg_type8_t)(0X4F)
#define TCCR1B			*(reg_type8_t)(0X4E)
#define TCCR1			*(reg_type16_t)(0X4E)
#define TCNT1H			*(reg_type8_t)(0X4D)
#define TCNT1L			*(reg_type8_t)(0X4C)
#define TCNT1			*(reg_type16_t)(0X4C)
#define OCR1AH			*(reg_type8_t)(0X4B)
#define OCR1AL			*(reg_type8_t)(0X4A)
#define OCR1A			*(reg_type16_t)(0X4A)
#define OCR1BH			*(reg_type8_t)(0X49)
#define OCR1BL			*(reg_type8_t)(0X48)
#define OCR1B			*(reg_type16_t)(0X48)
#define ICR1H			*(reg_type8_t)(0X47)
#define ICR1L			*(reg_type8_t)(0X46)
#define ICR1			*(reg_type16_t)(0X46)

/************************************************************************/
/*		                    TIMER2 REGISTERS		                        */
/************************************************************************/
#define TCCR2	    	*((reg_type8_t)0x45)
#define TCNT2	    	*((reg_type8_t)0x44)
#define OCR2	    	*((reg_type8_t)0x43)
#define ASSR         *((reg_type8_t)0x42)


/************************************************************************/
/*		                TIMERS INTERRUPTS REGISTERS		                  */
/************************************************************************/
#define GICR	    	*((reg_type8_t)0x5B)
#define MCUCR	    	*((reg_type8_t)0x55) 
#define MCUCSR	    	*((reg_type8_t)0x54)


/************************************************************************/
/*		                GLOBAL INTERRUPT REGISTER 	                     */
/************************************************************************/
#define SREG *((reg_type8_t)0x5F)



#endif /* REGISTERS_H_ */