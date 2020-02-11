/*
 * UART.h
 *
 * Created: 2/9/2020 7:50:00 PM
 *  Author: Reem el-Areeny
 */ 


#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "registers.h"
#include "UART.h"

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80
#define INITIAL_ZERO 0x00

#define RXC BIT7
#define TXC BIT6
#define UDRE BIT5
#define FE BIT4
#define DOR BIT3
#define PE BIT2
#define U2X BIT1
#define MPCM BIT0

#define RXCIE BIT7
#define TXCIE BIT6
#define UDRIE BIT5
#define RXEN BIT4
#define TXEN BIT3
#define UCSZ2 BIT2
#define RXB8 BIT1
#define TXB8 BIT0

#define URSEL BIT7
#define UMSEL BIT6
#define UPM1 BIT5
#define UPM0 BIT4
#define USBS BIT3
#define UCSZ1 BIT2
#define UCSZ0 BIT1
#define UCPOL BIT0

typedef enum UART_DATA_BITS_NUMBER{
	DATA_BITS_OF_5 = INITIAL_ZERO, DATA_BITS_OF_6 = BIT4, DATA_BITS_OF_7 = BIT5, DATA_BITS_OF_8 = BIT4 | BIT5, DATA_BITS_OF_9 = BIT4 | BIT5
}UART_DATA_BITS_NUMBER;

typedef enum UART_PARITY_MODE{
	PARITY_DISABLED = INITIAL_ZERO, PARITY_ENABLED_ODD = UPM1 | UPM0 , PARITY_ENABLED_EVEN = UPM1
}UART_PARITY_MODE;

typedef enum UART_MODE{
	ASYNCHRONOUS_MODE = INITIAL_ZERO, SYNCHRONOUS_MODE = UMSEL
}UART_MODE;

typedef enum UART_STOP_BITS_SITTING{
	UART_ONE_STOP_BIT = INITIAL_ZERO, UART_TWO_STOP_BITS = 0x08
}UART_STOP_BITS_SITTING;

typedef enum UART_INTERRUPT_MODES{
	UART_INTERRUPT_DISABLED = 0x1F, UART_RX_COMPLETE_INTERRUPT_ENABLE = RXCIE, UART_tX_COMPLETE_INTERRUPT_ENABLE = TXCIE, UDR_EMPTY_INTERRUPT_ENABLE = UDRIE
}UART_INTERRUPT_MODES;

typedef enum UART_BAUD_RATE{
	UART_BAUD_RATE_9600 = 103, UART_BAUD_RATE_115200 = 8
}UART_BAUD_RATE;

typedef struct UART{
	UART_INTERRUPT_MODES interrupt_mode;
	UART_DATA_BITS_NUMBER number_of_data_bits;
	UART_PARITY_MODE parity_mode;
	UART_MODE mode;
	UART_STOP_BITS_SITTING stop_bits;
	UART_BAUD_RATE baud_rate;
}UART;


extern void UART_init(UART);
extern void UART_transmit_byte(uint8_t);
extern uint8_t UART_receive_byte();

#endif /* UART_H_ */