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
//#include "sevenSeg.h"
#include "pushButton.h"	
#include "timers.h"	
#include <stdio.h>	
#define START BTN_0
#define STOP BTN_1
#define TICK_TIME (0.016384)
static volatile uint16_t over_flow=0;
uint8_t speed = 0,timer = 0,timer_counter = 0, distance = 0;
uint8_t * str[50];
	
	int main (){
		
		
// 		uint32_t distance =0,speed=0,speed_w=0,time_Count=0;
// 		
		
		
		SPI_SLAVE_INFO slave;
		slave. spi_i=SPI_I_EN;
		slave.spi_dir=SPI_DIR_LSB;
		slave.spi_idle=SPI_LOW_IDLE;
		slave.spi_sample=SPI_LEADING_PHASE;
		slave.clock_rate=SPI_CLOCK_RATE_4;
		slave.spi_speed_control=SPI_NORMAL_SPEED;
		init_slave(slave);
		

		
		//uart init
		UART_cfg UART1_CFG;
		UART1_CFG.baudrate = 9600;
		UART1_CFG.dataBits = UART_Bits_8;
		UART1_CFG.mode = UART_Transceiver;
		UART1_CFG.parity = No_Parity;
		UART1_CFG.sampleEdge = RisingEdg;
		UART1_CFG.stopBits = StopBits_1;
		UART1_CFG.uartSync = UART_Async;
		UART1_CFG.uartInterrupts = UART_No_Interrupts;
		UART_Init(&UART1_CFG);
		
timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_1024,0x00,0x00,T0_POLLING);

         pushButtonInit(START);
         pushButtonInit(STOP);
	   //sevenSegWrite(SEG_0,1);
	   
	   while(1){
		   
		    UART_Write_String((uint8_t*)" watting :");
			
	   while(pushButtonGetStatus(START)==Released);
	   while(pushButtonGetStatus(START)==Pressed);
	                timer0Start();
	  UART_Write('\n');
	  UART_Write('\r');
						
	  UART_Write_String((uint8_t*)" starting ...");
	// speed=1; 
	  
// 	   	if (spi_flag==1){	
// 			   
// 			   spi_flag = 0;  
// 			    
// 		   speed= re_slave();
// 		   
// 	  sprintf(str , "  received speed:  %d" , speed);
// 			   UART_Write_String(str);
// 		                  }
		while (pushButtonGetStatus(STOP)==Released){
			
			if(spi_flag == 1){
				spi_flag = 0;
				speed = re_slave();
				sprintf((char *)str,"  received speed:  %d",speed);
				UART_Write('\n');
				UART_Write('\r');
				UART_Write_String((uint8_t*)str);
			}
				
				if((TIFR |= BIT0)){
					TIFR |= BIT0;
					
					timer_counter ++ ;
					timer0Set(131);
			
					if(timer_counter == 13){
						
						distance += speed;
						timer_counter = 0;
						timer++;
					}
				}
			}
		
		while (pushButtonGetStatus(STOP)==Pressed);
		 
				sprintf((char *)str,"   speed:  %d",speed);
				UART_Write('\n');
				UART_Write('\r');
						
				UART_Write_String((uint8_t*)str);
				sprintf((char *)str,"   Time:  %d",timer);
				UART_Write('\n');
				UART_Write('\r');
						
				UART_Write_String((uint8_t*)str);
				sprintf((char *)str,"   distance:  %d",distance);
				UART_Write('\n');
				UART_Write('\r');
						
				UART_Write_String((uint8_t*)str);
				timer0Stop();
				timer = 0;
				distance = 0;
				timer0Set(0x00);
				UART_Write('\n');
				UART_Write('\r');
		}
			
			return 0;
		}


// ISR(TIMER0_OVF_vect	){
// 	over_flow++;
// }


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
