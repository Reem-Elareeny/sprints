/*
 * registers.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */


/*
 * registers.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_
#include "std_types.h"

/*
 * General Registers
 */
#define MCUCR	        *((reg_type8_t)0x55)
#define MCUCSR	        *((reg_type8_t)0x54)
#define GICR	        *((reg_type8_t)0x5B)
#define GIFR	        *((reg_type8_t)0x5A)

/*
 * PORTx registers
 */

#define PORTA_DATA      *((reg_type8_t)0x3B)
#define PORTA_DIR  	    *((reg_type8_t)0x3A)
#define PORTA_PIN	    *((reg_type8_t)0x39)

#define PORTB_DATA 	    *((reg_type8_t)0x38)
#define PORTB_DIR  	    *((reg_type8_t)0x37)
#define PORTB_PIN	    *((reg_type8_t)0x36)

#define PORTC_DATA 	    *((reg_type8_t)0x35)
#define PORTC_DIR  	    *((reg_type8_t)0x34)
#define PORTC_PIN	    *((reg_type8_t)0x33)


#define PORTD_DATA 	    *((reg_type8_t)0x32)
#define PORTD_DIR  	    *((reg_type8_t)0x31)
#define PORTD_PIN	    *((reg_type8_t)0x30)

#define SREG *((reg_type8_t)0x5F)
/*
 * General Timer registers
 */
#define TIMSK		    *((reg_type8_t)0x59)
#define TIFR		    *((reg_type8_t)0x58)


/*
 * Timer 0 Registers
 */

#define TCCR0	    	*((reg_type8_t)0x53)
#define TCNT0	    	*((reg_type8_t)0x52)
#define OCR0	    	*((reg_type8_t)0x5C)


/*
 * Timer 2 Registers
 */

#define TCCR2	    	*((reg_type8_t)0x45)
#define TCNT2	    	*((reg_type8_t)0x44)
#define OCR2	    	*((reg_type8_t)0x43)
#define ASSR            *((reg_type8_t)0x42)



/* 
*interrupts
*/
#define GICR	    	*((reg_type8_t)0x5B)
#define MCUCR	    	*((reg_type8_t)0x55) 
#define MCUCSR	    	*((reg_type8_t)0x54)

#endif /* REGISTERS_H_ */

