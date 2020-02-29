/*
 * CFile1.c
 *
 * Created: 10/02/2020 07:59:04 م
 *  Author: TOSHIBA
 */ 
#include "spi.h"
#define SPI_ENABLE 0x40
#define SPIF 0x80
#define GLOBEL_I_EN 0x80

#define SET_BIT(REG,BIT) (REG|=BIT)


uint8_t  volatile spi_flag=0;
void init_MASTR(SPI_MASTER_INFO spi_master_init){
	SPCR=0x00;
	SPSR=0x00;
	SPDR=0x00;

gpioPinDirection(GPIOB,BIT5|BIT7|BIT4,OUTPUT);
gpioPinDirection(GPIOB,BIT6,INPUT);
gpioPinWrite(GPIOB,BIT4,HIGH);
	PORTB_DATA |=0x10;
	SPCR|=spi_master_init.spi_i
	     |SPI_ENABLE
		 |SPI_MASTER
		 |spi_master_init.spi_dir
	     |spi_master_init.spi_idle
		 | spi_master_init.spi_sample
		 |spi_master_init.clock_rate;	
		 SPSR|=spi_master_init.spi_speed_control;
		 
		
}



void init_slave(SPI_SLAVE_INFO spi_slave_init){
	SPCR=0x00;
	SPSR=0x00;
	SPDR=0x00;
	SPCR|=spi_slave_init.spi_i
	|SPI_ENABLE
	|spi_slave_init.spi_dir
	|spi_slave_init.spi_idle
	|spi_slave_init.spi_sample
	|SPI_SLAVE;
	
	
	
	 gpioPinDirection(GPIOB,BIT5|BIT7|BIT4,INPUT);
	 gpioPinDirection(GPIOB,BIT6,OUTPUT);
	 
	 if (spi_slave_init.spi_i==SPI_I_EN)
	 SET_BIT(SREG,GLOBEL_I_EN);
}

void tr_master(char data){
	    
		PORTB_DATA &=~(0x10);
		 	   SPDR=data;
				TCNT0=SPDR;
				TCNT2=data;
		 while((SPSR&SPIF)==0);
		PORTB_DATA |=0x10;
}
char re_slave(void){
	char data=0;
	
	if (!(SPCR&SPI_I_EN))
	 while((SPSR&SPIF)==0);
	 
    data =SPSR;
	 data=SPDR;
	 return data;
         }

void tr_slave (char data);
char  re_master (void);

  ISR(SPI_STC_vect)
           {
		spi_flag=1;
		 	 	}