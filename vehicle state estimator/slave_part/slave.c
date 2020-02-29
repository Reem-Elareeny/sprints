/*
 * slave.c
 *
 * Created: 11/02/2020 12:14:01 ص
 *  Author: TOSHIBA
 */ 
#define  F_CPU 16000000
#include <util/delay.h>
#include "UART.h"
#include "spi.h"
#include "sevenSeg.h"
	
	
	int main (){
		SPI_SLAVE_INFO slave;
		slave. spi_i=SPI_I_EN;
		slave.spi_dir=SPI_DIR_LSB;
		slave.spi_idle=SPI_LOW_IDLE;
		slave.spi_sample=SPI_LEADING_PHASE;
		slave.clock_rate=SPI_CLOCK_RATE_4;
		slave.spi_speed_control=SPI_NORMAL_SPEED;
		init_slave(slave);
	    sevenSegInit(SEG_0);
	    sevenSegEnable(SEG_0);
		char RX_data;
		
		
		
		//uart init
		UART_cfg UART1_CFG;
		UART1_CFG.baudrate = 9600;
		UART1_CFG.dataBits = UART_Bits_8;
		UART1_CFG.mode = UART_Transceiver;
		UART1_CFG.parity = No_Parity;
		UART1_CFG.sampleEdge = RisingEdg;
		UART1_CFG.stopBits = StopBits_1;
		UART1_CFG.uartSync = UART_Async;
		UART1_CFG.uartInterrupts = OnRx;
		UART_Init(&UART1_CFG);
		
 
	   //PORTC_DIR=0xff;
	  // PORTC_DATA=0x00;
	  
	   sevenSegWrite(SEG_0,7);
	   
		while (1){
		
		 	if (spi_flag==1){
	    RX_data= re_slave();
			spi_flag=0;
		sevenSegWrite(SEG_0,RX_data);
		UART_Write(RX_data+48);
			}
		}
			
			
			return 0;
		}





	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//	 	int main (){
	// 		SPI_SLAVE_INFO slave;
	// 	 	slave. spi_i=SPI_pooling;
	// 	 	slave.spi_dir=SPI_DIR_LSB;
	// 	 	slave.spi_idle=SPI_LOW_IDLE;
	// 	 	slave.spi_sample=SPI_LEADING_PHASE;
	// 	 	slave.clock_rate=SPI_CLOCK_RATE_16;
	// 	 	slave.spi_speed_control=SPI_NORMAL_SPEED;
	// 	 	init_slave(slave);
	// SPCR=0b01100000;
	// 	 	//PORTA_DIR |=0xFF;
	// 		PORTD_DIR |=0xFF;
	// 	 	//PORTA_DATA=0x00;
	//
	// 	 	//uint8_t RX_data;
	//
	// 		while (1){
	//  	while (!(0x80&SPSR));
	// 	 TCNT0=(SPDR>>1);
	// 		PORTD_DATA=(SPDR>>1);
	// 			}
	// 	 	return 0;
	// 		}
	
	
	
	
	/*{
		PORTA_DATA|=(0x01);
		//_delay_ms(150);
		if (spi_flag==1){
			PORTA_DATA|=(0x02);
			//_delay_ms(150);
			RX_data =re_slave();
			PORTA_DATA|=(0x04);
			//_delay_ms(150);
			//PORTD_DATA=((PORTD_DATA&(0x0F))|(RX_data<<4));
			PORTD_DATA=RX_data;
			//_delay_ms(150);
			PORTA_DATA|=(0x08);
			//_delay_ms(150);
		}
		PORTA_DATA|=(0x10);
	}*/
	
// 	 init_MASTR(master);
// 	//uint8_t c = 0;
// 	
// 	tr_master(1);
// 	while (1){
// 		
// 		
// 		tr_master(2);
// 		_delay_ms(50);
// 		tr_master(3);
// 		_delay_ms(50);
// 		tr_master(4);
// 		_delay_ms(50);
// 		
// 		tr_master(7);
// 		_delay_ms(50);
// 		tr_master(8);
// 		_delay_ms(50);
// 		tr_master(1);
// 		_delay_ms(50);
// 	}
// 	
// 	return 0;
// }