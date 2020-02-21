/*
 * Interrupt.h
 *
 * Created: 2/16/2020 3:22:54 AM
 *  Author: Reem el-Areeny
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

/************************************************************************/
/*				                    INCLUDES	                 		         */
/************************************************************************/
#include "Infrastructure/registers.h"
#include "MCAL/DIO.h"

/************************************************************************/
/*				                     DEFINES			                        */
/************************************************************************/
#define INT0_vect			__vector_1
#define INT1_vect			__vector_2
#define INT2_vector			__vector_3
#define TIMER2_COMP_vector	__vector_4
#define TIMER2_OVF_vector		__vector_5
#define TIMER1_CAPT_vect	__vector_6
#define TIMER1_COMPA_vect	__vector_7
#define TIMER1_COMPB_vect	__vector_8
#define TIMER1_OVF_vect		__vector_9
#define TIMER0_COMP_vector	__vector_10
#define TIMER0_OVF_vector		__vector_11
#define SPI_STC_vect		__vector_12
#define USART_RXC_vect		__vector_13
#define USART_UDRE_vect		__vector_14
#define USART_TXC_vect		__vector_15
#define ADC_vect			__vector_16
#define EE_RDY_vect			__vector_17
#define ANA_COMP_vect		__vector_18
#define TWI_vect			__vector_19
#define SPM_RDY_vect		__vector_20


/************************************************************************/
/*		                   MACRO-LIKE FUNCTIONS		                     */
/************************************************************************/
#define sei()  (SREG |= BIT7)
#define cli()  (SREG &= ~(BIT7))

/************************************************************************/
/*		                   FUNCTIONS' PROTOTYPES		                     */
/************************************************************************/
#define INTERRUPT_SERVICE_ROTINE(vector, ...)            \
void vector (void) __attribute__ ((signal, used, externally_visible)) __VA_ARGS__; \
void vector (void)


#endif /* INTERRUPT_H_ */