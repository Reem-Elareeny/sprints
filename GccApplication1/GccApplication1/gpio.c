#include  "gpio.h"

void gpioPortDirection(uint8_t u8_port, uint8_t u8_direction){

	switch(u8_port){
		case GPIOA:
			PORTA_DIR = u8_direction;
			break;
		case GPIOB:
			PORTB_DIR = u8_direction;
			break;
		case GPIOC:
			PORTC_DIR = u8_direction;
			break;
		case GPIOD:
			PORTD_DIR = u8_direction;
			break;
		default:
		break;
	}
}

void gpioPortWrite(uint8_t u8_port, uint8_t u8_value){
	
	switch(u8_port){
		case GPIOA:
			PORTA_DATA = u8_value;
			break;
		case GPIOB:
			PORTA_DATA = u8_value;
			break;
		case GPIOC:
			PORTA_DATA = u8_value;
			break;
		case GPIOD:
			PORTA_DATA = u8_value;
			break;
		default:
		break;
	}	

}

void gpioPortToggle(uint8_t u8_port){
	switch(u8_port){
		case GPIOA:
			PORTA_DATA = ~(PORTA_DATA);
			break;
		case GPIOB:
			PORTB_DATA = ~(PORTA_DATA);
			break;
		case GPIOC:
			PORTC_DATA = ~(PORTA_DATA);
			break;
		case GPIOD:
			PORTD_DATA = ~(PORTA_DATA);
			break;
		default:
		break;
	}		
	
}

uint8_t gpioPortRead(uint8_t u8_port){
	uint8_t PORT_VALUE = 0;
	  switch(u8_port){
		case GPIOA:
			PORT_VALUE = PORTA_PIN;
			break;
		case GPIOB:
			PORT_VALUE = PORTB_PIN;
			break;
		case GPIOC:
			PORT_VALUE = PORTC_PIN;
			break;
		case GPIOD:
			PORT_VALUE = PORTC_PIN;
			break;
		default:
		break;
	}
	return PORT_VALUE;
}

void gpioPinDirection(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_direction){
   if(u8_direction == OUTPUT){
	   switch(u8_port){
			case GPIOA:
				PORTA_DIR |= u8_pins;
				break;
			case GPIOB:
				PORTB_DIR |= u8_pins;
				break;
			case GPIOC:
				PORTC_DIR |= u8_pins;
				break;
			case GPIOD:
				PORTD_DIR |= u8_pins;
				break;
			default:
			break;
		}
   }else if(u8_direction == INPUT){
	   switch(u8_port){
		case GPIOA:
			PORTA_DIR &= ~(u8_pins);
			break;
		case GPIOB:
			PORTB_DIR &= ~(u8_pins);
			break;
		case GPIOC:
			PORTC_DIR &= ~(u8_pins);
			break;
		case GPIOD:
			PORTD_DIR &= ~(u8_pins);
			break;
		default:
		break;   
		}
	}
}
void gpioPinWrite(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_value){
   if(u8_value == OUTPUT){
		switch(u8_port){
			case GPIOA:
				PORTA_DATA |= u8_pins;
				break;
			case GPIOB:
				PORTB_DATA |= u8_pins;
				break;
			case GPIOC:
				PORTC_DATA |= u8_pins;
				break;
			case GPIOD:
				PORTD_DATA |= u8_pins;
				break;
			default:
			break;
		}
	}else if(u8_value == INPUT){
		switch(u8_port){
		case GPIOA:
			PORTA_DATA &= ~(u8_pins);
			break;
		case GPIOB:
			PORTB_DATA &= ~(u8_pins);
			break;
		case GPIOC:
			PORTC_DATA &= ~(u8_pins);
			break;
		case GPIOD:
			PORTD_DATA &= ~(u8_pins);
			break;
		default:
		break;   
		}
	}
}

void gpioPinToggle(uint8_t u8_port, uint8_t u8_pins){
	switch(u8_port){
		case GPIOA:
			PORTA_DATA ^=(1 >> u8_pins);
			break;
		case GPIOB:
			PORTB_DATA &= ~(u8_pins);
			break;
		case GPIOC:
			PORTC_DATA &= ~(u8_pins);
			break;
		case GPIOD:
			PORTD_DATA &= ~(u8_pins);
			break;
		default:
		break;   
	}
}

uint8_t gpioPinRead(uint8_t u8_port, uint8_t u8_pin){
	uint8_t PIN_VALUE = 0;
	switch(u8_port){
		case GPIOA:
			PIN_VALUE = (PORTA_PIN & u8_pin);
			break;
		case GPIOB:
			PIN_VALUE = (PORTB_PIN & u8_pin);
			break;
		case GPIOC:
			PIN_VALUE = (PORTC_PIN & u8_pin);
			break;
		case GPIOD:
			PIN_VALUE = (PORTD_PIN & u8_pin);
			//PIN_VALUE = PORTD_PIN & (1 << u8_pin);
			break;
		default:
			break;
		}
}
