/*
 * TMU.c
 *
 * Created: 2/24/2020 11:38:14 AM
 * Author : Ehab & Reem
 */ 

#include "../Services/TMU.h"

#define TASK1_ID			1
#define TASK1_SPEED		10

#define TASK2_ID			2
#define TASK2_SPEED		20

uint8_t gu8_count = 0;

void toggle_PORT_A (void)
{
	gu8_count++;
	PORTA_DIR = OUTPUT;
	PORTA_DATA ^= HIGH;
}

void toggle_PORT_B (void)
{
	PORTB_DIR = OUTPUT;
	PORTB_DATA ^= HIGH;
	
}

int main(void)
{
	
	ENABLE_GINT;
   
	TMU_Init();
	
	TMU_Start_Timer(TASK1_ID,toggle_PORT_A,TASK1_SPEED,PERIODIC);
	
	TMU_Start_Timer(TASK2_ID,toggle_PORT_B,TASK2_SPEED,PERIODIC);
	
    while (1) 
    {
		TMU_Dispatch();
		TCNT2 = gu8_count;
		if(gu8_count == 200){
			TMU_Stop_Timer(TASK2_ID);
		}	
    }
	
}

