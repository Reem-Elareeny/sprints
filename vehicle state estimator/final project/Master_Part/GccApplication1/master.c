/*
 * slave.c
 *
 * Created: 11/02/2020 12:14:01 ص
 *  Author: TOSHIBA
 */ 
#define  F_CPU 16000000

#include "pushButton.h"
#include "spi.h"
#include "UART.h"
#include <util/delay.h>




volatile  char in_spee=0,flag=0;


int main(){
	SPI_MASTER_INFO master;
	master. spi_i=SPI_pooling;
	master.spi_dir=SPI_DIR_LSB;
	master.spi_idle=SPI_LOW_IDLE;
	master.spi_sample=SPI_LEADING_PHASE;
	master.clock_rate=SPI_CLOCK_RATE_4;
	master.spi_speed_control=SPI_NORMAL_SPEED;
	init_MASTR(master);
	
	
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
	
	
	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);
	

	_delay_ms(50);
	
	
	
	
	
	while (flag!=1);
	_delay_ms(2);
	tr_master(in_spee);

	UART_Write((in_spee+48));
	
	while (1){
		
			if(pushButtonGetStatus(BTN_0)==Pressed)
			{
			while (pushButtonGetStatus(BTN_0)==Pressed);
				if (in_spee<10)
				{
					in_spee++;
					tr_master(in_spee);
					
					UART_Write((in_spee+48));

				}
			}
			if(pushButtonGetStatus(BTN_1)==Pressed){
				while (pushButtonGetStatus(BTN_1)==Pressed);
				if (in_spee>0)
				{
					in_spee--;
					tr_master(in_spee);
					UART_Write((in_spee+48));
					
				}
			}
		
		
		
	}
	
	

return 0;	
}
 	
	
	
	ISR(USART_RXC_vect)
	{
		in_spee = UDR;
		in_spee-=48;
		flag=1;
	}
	
	
	
