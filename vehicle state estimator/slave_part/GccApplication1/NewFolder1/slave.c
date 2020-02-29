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
	
#define START BTN_0
#define STOP BTN_1
#define TICK_TIME (0.016384)

	uint32_t static volatile over_flow=0;
	int main (){
		uint32_t distance =0,speed=0,speed_w=0,time_Count=0;
		
		
		
		SPI_SLAVE_INFO slave;
		slave. spi_i=SPI_I_EN;
		slave.spi_dir=SPI_DIR_LSB;
		slave.spi_idle=SPI_LOW_IDLE;
		slave.spi_sample=SPI_LEADING_PHASE;
		slave.clock_rate=SPI_CLOCK_RATE_4;
		slave.spi_speed_control=SPI_NORMAL_SPEED;
		init_slave(slave);
		
// 	    sevenSegInit(SEG_0);
// 	    sevenSegEnable(SEG_0);
		//char RX_data;
		
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
		
		 timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,
		T0_PRESCALER_1024, 0,0,
		T0_INTERRUPT_NORMAL);
		
         pushButtonInit(START);
         pushButtonInit(STOP);
	   //sevenSegWrite(SEG_0,1);
	   
	   while(1){
		   
		   UART_Write_String((uint8_t*)" watting :");
	   while(pushButtonGetStatus(START)==Released);
	   while(pushButtonGetStatus(START)==Pressed);
	    //sevenSegWrite(SEG_0,2);
	  UART_Write('\n');
	  UART_Write_String((uint8_t*)" starting :");
	  
	  speed=1;
// 	   	if (spi_flag==1){
// 			   timer0Start();  
// 		   speed= re_slave();
// 		   speed_w=speed;
// 		   	spi_flag=0;
// 			   UART_Write_String((uint8_t *)"sended speed :");
// 			   while(speed_w>0){
// 		   	UART_Write((speed_w%10)+48);
// 			//sevenSegWrite(SEG_0,(speed_w%10));
// 			   speed_w/=10;
// 			   }  
	   	
	 
	  
		while (pushButtonGetStatus(STOP)==Released){
			// sevenSegWrite(SEG_0,3);
				if (spi_flag==1){
				    spi_flag=0;
					distance=distance+((timer0Read()+(over_flow*256))*TICK_TIME);
					speed= re_slave();
					timer0Set(0);
					over_flow=0;
					}
				}
		while (pushButtonGetStatus(STOP)==Pressed);
		 //sevenSegWrite(SEG_0,4);
				timer0Stop();
				 UART_Write('\n');
				 UART_Write_String((uint8_t*)" Stop :");
				distance=distance+((timer0Read()+(over_flow*256))*TICK_TIME);
				time_Count=distance/speed;
				UART_Write('\n');
				UART_Write_String((uint8_t*)" speed :");
				UART_Write((speed)+48);
			//	speed_w=speed;
// 				while(speed_w>0){
// 					UART_Write((speed_w%10)+48);
// 					//sevenSegWrite(SEG_0,(speed_w%10));
// 					speed_w/=10;
// 				}
				UART_Write('\n');
				UART_Write_String((uint8_t*)"distance :");
				speed_w=distance;
				UART_Write(speed_w+48);
				
// 				
// 				while(speed_w>0){
// 					UART_Write((speed_w%10)+48);
// 					//sevenSegWrite(SEG_0,(speed_w%10));
// 					speed_w/=10;
// 				}
                 speed_w=time_Count;
				 UART_Write(speed_w+48);
				UART_Write('\n');
				UART_Write_String((uint8_t*)"time:");
				speed_w=time_Count;
// 				while(speed_w>0){
// 					UART_Write((speed_w%10)+48);
// 					//sevenSegWrite(SEG_0,(speed_w%10));
// 					speed_w/=10;
// 				}
				timer0Set(0);
				speed=0;
				distance=0;
				time_Count=0;
				
		}
			
			return 0;
		}


ISR(TIMER0_OVF_vect	){
	over_flow++;
}


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
