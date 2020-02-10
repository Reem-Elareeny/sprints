/*
 * CFile1.c
 *
 * Created: 10/02/2020 07:59:04 م
 *  Author: TOSHIBA
 */ 
#include "spi.h"

#define SPI_ENABLE 0x40
#define SPIF 0x80
// #define SPI_MASTER 0x10
// #define SPI_SLAVE 0x00

void init_MASTER(SPI_MASTER_INFO spi_master_init){
	SPCR=0x00;
	SPSR=0x00;
	 PORTB_DIR|=0x20|0x80|0x10;
	 PORTB_DIR&=~(0x40);
	// PORTB_DATA |=0x10;
	SPCR|=spi_master_init.spi_i
	     |SPI_ENABLE
		 |SPI_MASTER
		 |spi_master_init.spi_dir
	     |spi_master_init.spi_idle
		 | spi_master_init.spi_sample
		 |spi_master_init.clock_rate;	
		 SPSR|=SPI_DOUBLE_SPEED;
		
}



void init_slave(SPI_SLAVE_INFO spi_slave_init){
	SPCR=0x00;
	SPSR=0x00;
	SPCR|=spi_slave_init.spi_i
	|SPI_ENABLE
	|spi_slave_init.spi_dir
	|spi_slave_init.spi_idle
	|spi_slave_init.spi_sample
	|SPI_SLAVE;
	//|spi_slave_init.clock_rate
	SPSR|=SPI_DOUBLE_SPEED;
	PORTB_DIR&=~(0x20)&~(0x80)&~(0x10);
	PORTB_DIR|=(0x40);
	
}

void tr_master(char data){
		 //PORTB_DATA |=0x10;
         SPDR=data;
		 while((SPSR & SPIF) != 0);
		 data =SPSR;
		 data=SPDR;
	
}
char re_slave(void){
	//char data = 0;
	if((PORTB_PIN&0x10)!=1){
	 while((SPSR & SPIF) != 0);
	 //data =SPSR;
	 return SPDR;
	 }
}

void tr_slave (char data);
char  re_master (void);