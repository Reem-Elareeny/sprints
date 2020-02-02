/*
 * softwareDelay.c
 *
 * Created: 1/18/2020 4:15:13 PM
 *  Author: Reem el-Areeny
 */ 

#include "softwareDelay.h"

void softwareDelayMs(uint32_t u32_delay_in_ms){
	uint64_t index;
	volatile uint16_t dummy;
	for(index = 0; index< 300 * u32_delay_in_ms; index++){
		dummy++;
	}
}
