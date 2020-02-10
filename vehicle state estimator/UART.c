/*
 * UART.c
 *
 * Created: 2/9/2020 7:49:33 PM
 *  Author: Reem el-Areeny
 */ 
#include "UART.h"
#include "interrupt.h"

INTERRUPT_SERVICE_ROTINE(USART_RXC_vect){
	
}

INTERRUPT_SERVICE_ROTINE(USART_TXC_vect){
	
}

INTERRUPT_SERVICE_ROTINE(USART_UDRE_vect){
	
}

void UART_init(UART uart){
	/*Reset All Flags */
	UCSRA = TXC;
	
	UDR = INITIAL_ZERO;

	UCSRB = INITIAL_ZERO;  /*clear the register*/
	
	/* check which interrupts are enabled */
	//UCSRB |= uart.interrupt_mode;
	UCSRB &= uart.interrupt_mode;
			
	/* set the selected mode
	first select to work on UCSRC register
	and clear all the other bits */
	
	UCSRC = URSEL | uart.mode | uart.parity_mode | uart.stop_bits | uart.number_of_data_bits;
	
	/*set the baud rate*/
	UBRRH = INITIAL_ZERO;
	UBRRL = uart.baud_rate;
	
	UCSRB |= RXEN | TXEN; /*enable transmitting and receiving*/
}

void UART_transmit_byte(uint8_t byte){
	//while(UDRE == 0);
	while(!(UCSRA & UDRE));
	UDR = byte;
	while(!(UCSRA & TXC));
	UCSRA |= TXC;
}

uint8_t UART_receive_byte(){
	while(!(UCSRA & RXC));
	return UDR;
}

//set the baud rate
//handle 9 bits data
//check of flags
//implement ISR