/*
 * DIO.c
 *
 * Created: 2/15/2020 10:42:57 PM
 *  Author: Reem el-Areeny
 */ 

#include "DIO.h"

/*
*Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
*Output: No output
*In/Out:
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS_t DIO_init (DIO_Cfg_t *DIO_info){
	ERROR_STATUS_t  au8_status = E_Ok;
	if(DIO_info == NULL){
		au8_status |= E_Nok;
	}else{
		if(DIO_info->dir == OUTPUT){
			switch(DIO_info->GPIO){
				case GPIOA:
					PORTA_DIR |= DIO_info->pins;
					break;
				case GPIOB:
					PORTB_DIR |= DIO_info->pins;
					break;
				case GPIOC:
					PORTC_DIR |= DIO_info->pins;
					break;
				case GPIOD:
					PORTD_DIR |= DIO_info->pins;
					break;
				default:
					au8_status = E_Nok;
					break;
			}
		}else if(DIO_info->dir == INPUT){
			switch(DIO_info->GPIO){
				case GPIOA:
					PORTA_DIR &= ~(DIO_info->pins);
					break;
				case GPIOB:
					PORTB_DIR &= ~(DIO_info->pins);
					break;
				case GPIOC:
					PORTC_DIR &= ~(DIO_info->pins);
					break;
				case GPIOD:
					PORTD_DIR &= ~(DIO_info->pins);
					break;
				default:
					au8_status = E_Nok;
					break;
			}
		}else{
			au8_status = E_Nok;
		}
	}
	return au8_status;
}

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: No output
*In/Out: No In/Out
*Description: This function can set the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS_t DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value){
	ERROR_STATUS_t  au8_status = E_Ok;
	if(value == HIGH){
		switch(GPIO){
			case GPIOA:
				PORTA_DATA |= pins;
				break;
			case GPIOB:
				PORTB_DATA |= pins;
				break;
			case GPIOC:
				PORTC_DATA |= pins;
				break;
			case GPIOD:
				PORTD_DATA |= pins;
				break;
			default:
				au8_status = E_Nok;
				break;
			}
		}else if(value == LOW){
			switch(GPIO){
				case GPIOA:
					PORTA_DATA &= ~(pins);
					break;
				case GPIOB:
					PORTB_DATA &= ~(pins);
					break;
				case GPIOC:
					PORTC_DATA &= ~(pins);
					break;
				case GPIOD:
					PORTD_DATA &= ~(pins);
					break;
				default:
					au8_status = E_Nok;
					break;
			}
		}else{
			au8_status = E_Nok;
		
	}
	return au8_status;
}

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: data -> the acquired data wether it was PORT data or pins data
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS_t DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data){
	ERROR_STATUS_t au8_status = E_Ok;
		switch(GPIO){
			case GPIOA:
				*data = (PORTA_PIN & pins);
				break;
			case GPIOB:
				*data = (PORTB_PIN & pins);
				break;
			case GPIOC:
				*data = (PORTC_PIN & pins);
				break;
			case GPIOD:
				*data = (PORTD_PIN & pins);
				break;
			default:
				au8_status = E_Nok;
				break;
		}
	return au8_status;
}

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS_t DIO_Toggle (uint8_t GPIO, uint8_t pins){
	ERROR_STATUS_t  au8_status = E_Ok;
	switch(GPIO){
		case GPIOA:
			PORTA_DATA ^= pins;
			break;
		case GPIOB:
			PORTB_DATA ^= pins;
			break;
		case GPIOC:
			PORTC_DATA ^= pins;
			break;
		case GPIOD:
			PORTD_DATA ^= pins;
			break;
		default:
			au8_status = E_Nok;
			break;
	}
	return au8_status;
}