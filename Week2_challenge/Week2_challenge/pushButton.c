#include "pushButton.h"

void pushButtonInit(En_buttonId_t en_butotn_id){
	switch(en_butotn_id){
		case BTN_0:
			gpioPinDirection(BTN_0_GPIO,BTN_0_BIT, INPUT);
			break;
		case BTN_1:
			gpioPinDirection(BTN_1_GPIO,BTN_1_BIT,INPUT);
			break;
		case BTN_2:
			gpioPinDirection(BTN_2_GPIO,BTN_2_BIT,INPUT);
			break;
		case BTN_3:
			gpioPinDirection(BTN_3_GPIO,BTN_3_BIT,INPUT);
			break;
		default:
		break;
	}
}

En_buttonStatus_t pushButtonGetStatus(En_buttonId_t en_butotn_id){
	En_buttonStatus_t status = Released;
	switch(en_butotn_id){
		case BTN_0:
			status = gpioPinRead(BTN_0_GPIO,BTN_0_BIT);
			_delay_ms(200);
			//softwareDelayMs(200);
			break;
		case BTN_1:
			status = gpioPinRead(BTN_1_GPIO,BTN_1_BIT);
			_delay_ms(200);
			//softwareDelayMs(200);
			break;
		case BTN_2:
			status = gpioPinRead(BTN_2_GPIO,BTN_2_BIT);
			_delay_ms(200);
			//softwareDelayMs(200);
			break;
		case BTN_3:
			status = gpioPinRead(BTN_3_GPIO,BTN_3_BIT);
			_delay_ms(200);
			//softwareDelayMs(200);
			break;
		default:
			status = Released;
			break;
	}
	return status;	
}