#include "gpio.h"
#define INIT_VALUE (0x00)

void gpioPortDirection(uint8_t u8_port, uint8_t u8_direction){//corrected

	switch (u8_port){
		case GPIOA :
			PORTA_DIR=u8_direction;
			break;
			
			case GPIOB :
			PORTB_DIR =u8_direction;
			break;
			
			case GPIOC :
			PORTC_DIR=u8_direction;
			break;
			
			case GPIOD :
			PORTC_DIR=u8_direction;
			break;
	}
}

void gpioPortWrite(uint8_t u8_port, uint8_t u8_value){
	
	switch (u8_port){
		case GPIOA :
			PORTA_DATA=u8_value;
			break;
			
			case GPIOB :
			PORTB_DATA=u8_value;
			break;
			
			case GPIOC :
			PORTC_DATA=u8_value;
			break;
			
			case GPIOD :
			PORTD_DATA=u8_value;
			break;
}
}

 void gpioPortToggle(uint8_t u8_port){
	switch (u8_port){
		case GPIOA :
			PORTA_DATA=~PORTA_DATA;
			break;
			
			case GPIOB :
			PORTB_DATA=~PORTB_DATA;
			break;
			
			case GPIOC :
			PORTC_DATA=~PORTC_DATA;
			break;
			
			case GPIOD :
			PORTD_DATA=~PORTD_DATA;
			break;
}
}

uint8_t gpioPortRead(uint8_t u8_port){

	uint8_t u8_port_data=INIT_VALUE;

	switch (u8_port){
		
		case GPIOA :
			u8_port_data=PORTA_PIN;
			break;
			
			case GPIOB :
		    u8_port_data=PORTB_PIN;
			break;
			
			case GPIOC :
			u8_port_data=PORTC_PIN;
			break;
			
			case GPIOD :
			u8_port_data=PORTD_PIN;
			break;
			}
			return u8_port_data;
}
void gpioPinDirection(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_direction){
	
	switch (u8_port){
		case GPIOA :
	 switch (u8_direction){
		 case INPUT:
		 PORTA_DIR&=(~u8_pins);
		 break;
		 case OUTPUT:
		 PORTA_DIR|=	u8_pins;
		 break;
	 }
			break;
			case GPIOB :	
		 switch (u8_direction){
		 case INPUT:
			PORTB_DIR&=(~u8_pins);
		    break;
		 case OUTPUT:
		     PORTB_DIR|=	u8_pins;
			 break;
			 }
		
			break;
			
			case GPIOC :
			 switch (u8_direction){
				 case INPUT:
				 PORTC_DIR&=(~u8_pins);
				 break;
				 case OUTPUT:
				 PORTC_DIR|=	u8_pins;
				 break;
			 }
     
			break;
			
			case GPIOD :
		 switch (u8_direction){
			 case INPUT:
			 PORTD_DIR&=(~u8_pins);
			 break;
			 case OUTPUT:
			 PORTD_DIR|=	u8_pins;
			 break;
		 }
			break;
	}
	
	}


void gpioPinWrite(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_value){
	
	switch (u8_port){	 
		 case GPIOA :
		 
		switch(u8_value){
			
			case HIGH:
		PORTA_DATA|=u8_pins;
		     break;
			case LOW :
			PORTA_DATA&=(~u8_pins);
			break;
		}
		break;
		
			case GPIOB :
			
			switch(u8_value){
				
				case HIGH:
				PORTB_DATA|=u8_pins;
				break;
				case LOW :
				PORTB_DATA&=(~u8_pins);
				break;
			}
			break;
			
			case GPIOC :
		switch(u8_value){
			
			case HIGH:
			PORTC_DATA|=u8_pins;
			break;
			case LOW :
			PORTC_DATA&=(~u8_pins);
			break;
		}
		break;
			
			case GPIOD :
		switch(u8_value){
			
			case HIGH:
			PORTD_DATA|=u8_pins;
			break;
			case LOW :
			PORTD_DATA&=(~u8_pins);
			break;
		}
		break;
		}
		}
		

void gpioPinToggle(uint8_t u8_port, uint8_t u8_pins){
	
	switch (u8_port){
		
		case GPIOA :
	PORTA_DATA^=u8_pins;
			break;
			
			case GPIOB :
	PORTB_DATA^=u8_pins;
			
			case GPIOC :
	PORTC_DATA^=u8_pins;

			break;
			
			case GPIOD :
	 PORTD_DATA^=u8_pins;

			break;
	}
	
}

uint8_t gpioPinRead(uint8_t u8_port, uint8_t u8_pin){
	uint8_t u8_port_data=INIT_VALUE;
	
	switch (u8_port){
	
		case GPIOA :
	u8_port_data=u8_pin & PORTA_PIN;
			break;
			
			case GPIOB :
	u8_port_data=u8_pin&PORTB_PIN;
	         break;
			
			case GPIOC :
    u8_port_data=u8_pin &PORTC_PIN;
			break;
			
 			case GPIOD :
    u8_port_data=u8_pin &PORTD_PIN;
			break;
	}
	
	if(u8_port_data>LOW)
      return HIGH ;
	  else 
	  return LOW ;

}
			
			
			
		
