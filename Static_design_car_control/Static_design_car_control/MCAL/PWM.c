/*
 * PWM.c
 *
 * Created: 2/18/2020 3:11:10 AM
 *  Author: Reem el-Areeny
 */ 

#include  "PWM.h"

/***********************************************************************/
/*					               LOCAL DEFINES		     	  				     */
/***********************************************************************/
#define PWM_CH1A_CLEAR_ON_COMAPARE_MATCH					0x80
#define PWM_CH1B_CLEAR_ON_COMAPARE_MATCH					0x20

#define TCCR1A_WF_GEN_PHASE_CORRECT_MODE_10				0x02
#define TCCR1B_WF_GEN_PHASE_CORRECT_MODE_10				0x10



static uint16_t gu16_PWM_prescaler = CLEAR_VALUE;


/************************************************************************/
/*							  PWM FUNCTIONS' IMPLEMENTAIONS		               */
/************************************************************************/
/*
* Function: Error_State Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);                         
* Type: public                                                                  
* Input parameters: Pwm_Cfg Structure (channel number, Prescaler)               
* Return type : void          
* Description: initialize the PWM configuration                                 
*/
 ERROR_STATUS_t Pwm_Init(Pwm_Cfg_s *Pwm_Cfg){
	ERROR_STATUS_t  au8_status = E_Ok;
	DIO_Cfg_t DIO_info = {GPIOD, BIT4 | BIT5, OUTPUT};
	if(Pwm_Cfg == NULL){
		au8_status = E_Nok;
	}else{
		
		/*select compare output & Waveform generation mode*/
		TCCR1A = PWM_CH1A_CLEAR_ON_COMAPARE_MATCH | TCCR1A_WF_GEN_PHASE_CORRECT_MODE_10;
		TCCR1B = TCCR1B_WF_GEN_PHASE_CORRECT_MODE_10;
		/*initialize output pins*/

		DIO_init(&DIO_info);

		switch(Pwm_Cfg->Channel){
			case PWM_CH1A:
				TCCR1A |= PWM_CH1A_CLEAR_ON_COMAPARE_MATCH | TCCR1A_WF_GEN_PHASE_CORRECT_MODE_10;
				TCCR1B |= TCCR1B_WF_GEN_PHASE_CORRECT_MODE_10;				
				break;
			case PWM_CH1B:
				TCCR1A |= PWM_CH1B_CLEAR_ON_COMAPARE_MATCH | TCCR1A_WF_GEN_PHASE_CORRECT_MODE_10;
				TCCR1B |= TCCR1B_WF_GEN_PHASE_CORRECT_MODE_10;
				break;
			default:
				au8_status = E_Nok;
				break;
		}

		/* set the prescaler */
		gu16_PWM_prescaler = Pwm_Cfg->Prescaler;

		}
	return au8_status;
 }


 /* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);
 * Type: public
 * Input parameters: Channel ID, Duty cycle(0:100)
 * Return type : Error State
 *
 * Description: starts the PWM on the dedicated channel with the required duty
 *				cycle and frequency
 *-------------------------------------------------------
 *(IN timer 0) there are only 5 available Frequencies:
 *-------------------------------------------------------
 *Frequency (NO-Prescaler) --> 31,372HZ
 *Frequency (Prescaler 8) --> 3,921HZ
 *Frequency (Prescaler 64) --> 490HZ
 *Frequency (Prescaler 256) --> 122HZ
 *Frequency (Prescaler 1024) --> 31HZ
*--------------------------------------------------------
*(IN timer 1) there are only 7 available Frequencies:
*-------------------------------------------------------
 *Frequency (NO-Prescaler) --> HZ
 *Frequency (Prescaler 8) --> HZ
 *Frequency (Prescaler 64) --> HZ
 *Frequency (Prescaler 256) --> HZ
 *Frequency (Prescaler 1024) --> HZ
 *--------------------------------------------------------
 *(IN timer 2) there are only 7 available Frequencies:
 *-------------------------------------------------------
 *Frequency (NO-Prescaler) --> 31,372HZ
 *Frequency (Prescaler 8) --> 3,921HZ
 *Frequency (Prescaler 32) --> 980HZ
 *Frequency (Prescaler 64) --> 490HZ
 *Frequency (Prescaler 128) --> 245HZ
 *Frequency (Prescaler 256) --> 122HZ
 *Frequency (Prescaler 1024) --> 31HZ
 *-------------------------------------------------------
 *((all this calculations are for phase correct mode))
 *all this calculation for F_CPU 16MHz
 */
 ERROR_STATUS_t Pwm_Start(uint8_t Channel,uint8_t Duty,uint8_t Frequncy){
	 ERROR_STATUS_t au8_status = E_Ok;
	

	if(Frequncy != Frequncy_100HZ || gu16_PWM_prescaler != PWM_PRESCALER_1024){
		 au8_status = E_Nok;
	}else{
		/*set the prescaler*/
	 	TCCR1B |= PRESCALER_1024;
		/*calculate the OCR value for the given duty cycle*/
		ICR1 = ICR_VALUE_100HZ;
		switch(Channel){
			case PWM_CH1A:
				/* load OCR values into High & Low registers*/
				 OCR1A = ((uint32_t)Duty * ICR_VALUE_100HZ) / 100;
				break;
			case PWM_CH1B:
				/* load OCR values into High & Low registers*/
				OCR1B = ((uint32_t)Duty * ICR_VALUE_100HZ) / 100;
				break;
			default:
				au8_status = E_Nok;
		}
	}
	 return au8_status;
 }

/*
* Function: Error_State Pwm_Stop(uint8_t channel);
* Type: public
* Input parameters: channel ID
* Return type : Error state
*
* Description: responsible of Stopping the PWM by clearing the prescaler
*				of the corresponding channel
*/
 ERROR_STATUS_t Pwm_Stop(uint8_t Channel){
	
 	ERROR_STATUS_t  au8_status = E_Ok;
 	/*disable the clock*/
	TCCR1B |= PWM_PRESCALER_NO;
 	return au8_status;
}


 ERROR_STATUS_t Pwm_Update(uint8_t Channel,uint8_t Duty,uint8_t Frequncy){
	 ERROR_STATUS_t  au8_status = E_Ok;
	 if(gu16_PWM_prescaler != PWM_PRESCALER_1024){
		au8_status = E_Nok;
	 }else{
		Pwm_Stop(Channel);
		Pwm_Start(Channel,Duty,Frequncy);
	 }

	 if(Frequncy != Frequncy_100HZ || gu16_PWM_prescaler != PWM_PRESCALER_1024){
		au8_status = E_Nok;
	}else{
		 /*set the prescaler*/
		 TCCR1B |= PRESCALER_1024;
		 /*calculate the OCR value for the given duty cycle*/
		 ICR1 = ICR_VALUE_100HZ;
		 switch(Channel){
			 case PWM_CH1A:
			 /* load OCR values into High & Low registers*/
			 OCR1A = ((uint32_t)Duty * ICR_VALUE_100HZ) / 100;
			 break;
			 case PWM_CH1B:
			 /* load OCR values into High & Low registers*/
			 OCR1B = ((uint32_t)Duty * ICR_VALUE_100HZ) / 100;
			 break;
			 default:
			 au8_status = E_Nok;
		 }
	 }
	 return au8_status;
 }
