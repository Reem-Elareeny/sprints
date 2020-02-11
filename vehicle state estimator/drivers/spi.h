/*
 * IncFile1.h
 *
 * Created: 10/02/2020 07:43:50 م
 *  Author: TOSHIBA
 */ 
#include "registers.h"

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80
#define INITIAL_ZERO 0x00

#ifndef INCFILE1_H_
#define INCFILE1_H_

typedef enum {
	SPI_I_EN =0x80,
	SPI_polling =0x00
	}SPI_I;

typedef enum {
	SPI_DIR_LSB =0x20,
	SPI_DIR_MSB =0x00
}SPI_DIR;

typedef enum {
	SPI_MASTER =0x10,
	SPI_SLAVE =0x00
}SPI_MODE;

typedef enum {
	SPI_HIGH_IDLE =0x08,
	SPI_LOW_IDLE =0x00
}SPI_IDLE;

typedef enum {
	SPI_LEADING_PHASE =0x08,
	SPI_TRALING_PHASE =0x00
}SPI_SAMPLE;

typedef enum {
	SPI_CLOCK_RATE_4  =0x00,
	SPI_CLOCK_RATE_16  =0x01,
	SPI_CLOCK_RATE_64  =0x02,
	SPI_CLOCK_RATE_128  =0x03
}SPI_CLOCK_RATE;
typedef enum {
	SPI_NORMAL_SPEED = 0x00,
	SPI_DOUBLE_SPEED  =0x01
}SPI_SPEED_CONTROL;
typedef struct  {
	SPI_I spi_i;
    SPI_DIR spi_dir;
	//SPI_MODE spi_mode;
	SPI_IDLE spi_idle;
	SPI_SAMPLE  spi_sample;
	SPI_CLOCK_RATE clock_rate;
	SPI_SPEED_CONTROL spi_speed_control;
	}SPI_MASTER_INFO;
	
	typedef struct  {
		SPI_I spi_i;
		SPI_DIR spi_dir;
		//SPI_MODE spi_mode;
		SPI_IDLE spi_idle;
		SPI_SAMPLE  spi_sample;
		//SPI_CLOCK_RATE clock_rate;
		//SPI_SPEED_CONTROL spi_speed_control;
	}SPI_SLAVE_INFO;
	
void init_MASTER(SPI_MASTER_INFO spi_init);

void init_slave(SPI_SLAVE_INFO);
void tr_master(char data);
char re_slave(void);

 void tr_slave (char data);
 char re_master (void);





#endif /* INCFILE1_H_ */