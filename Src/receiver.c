/*
 * receiver.c
 *
 *  Created on: Oct 24, 2021
 *      Author: navinj
 */

#include "receiver.h"
#include <inttypes.h>

typedef struct
{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CCMR1;
	uint32_t CCMR2;
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
	uint32_t CCR1;
} TIM;

// this is TIM4
static volatile TIM* tim = (TIM*) 0x40000800;

void receiver_init(){
	*RCC_APB1ENR |= 1 << 2;
	*NVIC_ISER0 |= 1 << 30;

	tim->ARR = 8000; // 1 ms
	tim->CCR1 = 8000; // 1 ms
	tim->DIER = 1;
}

/*
 * Starts the receiver counter
 */
void receiver_start(){
	tim->CR1 = 1;
}

/*
 * Stops the receiver counter
 */
void receiver_stop(){
	tim->CR1 &= ~1;
}

//resets receiver counter value
void receiver_resetValue(){
	tim->CNT = 0;
}

//reset receiver flag
void receiver_resetFlag(){
	tim->SR &= ~1;
}

uint8_t receiver_decodeMan(uint8_t inputBuffer[]){
	uint8_t output[8];
	uint8_t firstBit = 0;
	uint8_t secondBit = 0;

	for(int i = 0; i<16; i+=2){
		firstBit = inputBuffer[i];
		secondBit = inputBuffer[i+1];

		if(firstBit == 0 && secondBit == 1){
			output[i/2] = 1;
		}else{
			output[i/2] = 0;
		}
	}
	return output[0]<<7|output[1]<<6|output[2]<<5|output[3]<<4|output[4]<<3|output[5]<<2|output[6]<<1|output[7];
}
