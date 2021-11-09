#include "transmit.h"
#include <inttypes.h>
#include <stdlib.h>

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

// this is TIM3
static volatile TIM* tim = (TIM*) 0x40000400;

// this is TIM5
static volatile TIM* tim5 = (TIM*) 0x40000C00;

//static char* data_ptr = (char*) 0; // the data being sent
//static uint32_t transmit_len = 0; // the number of bytes
//static uint32_t transmit_pos = 0; // byte offset
//static uint32_t transmit_bit = 0; // bit offset
//
//static uint32_t half_bit = 0; // which half-bit is being sent (0 for first, 1 for second)
//
//static uint32_t sent = 0; // number of half-bits sent

void init_transmitter(void)
{
	*RCC_APB1ENR |= 1 << 1;
	*NVIC_ISER0 |= 1 << 29;

	*RCC_AHB1ENR |= (1<<GPIOCEN);

	//Set pin PC11 to output
	*GPIOC_MODER &= ~(0x3<<22);
	*GPIOC_MODER |= (0x1<<22);

	tim->ARR = 8000; // .5 ms
	tim->CCR1 = 8000; // .5 ms
	tim->DIER = 1;

	transmitter_setOutHigh();

	//tim5
	*RCC_APB1ENR |= 1 << 3;
	*NVIC_ISER0 |= 1 << 29;

	retransmitter_resetValueRandom();
	tim5->DIER = 1;

}

void transmit_string(char *data, uint32_t len)
{
//	data_ptr = data;
//	transmit_len = len;
//	transmit_pos = 0;
//	half_bit = 0;

	// start timer
	tim->CR1 |= 1;
}

/*
 * Starts the counter
 */
void transmitter_start(){
	tim->CR1 = 1;
}

void retransmitter_start(){
	tim5->CR1 = 1;
}

/*
 * Stops the counter
 */
void transmitter_stop(){
	tim->CR1 &= ~1;
}

void retransmitter_stop(){
	tim5->CR1 &= ~1;
}

//resets value of counter
void transmitter_resetValue(){
	tim->CNT = 0;
}

void retransmitter_resetValue(){
	tim5->CNT = 0;
}

//resets interrupt flag
void transmitter_resetFlag(){
	tim->SR &= ~1;
}

void retransmitter_resetFlag(){
	tim5->SR &= ~1;
}

void transmitter_setOutHigh(){
	*GPIOC_BSRR |= (1<<11);
}

void transmitter_setOutLow(){
	*GPIOC_BSRR |= (1<<27);
}

void retransmitter_resetValueRandom(){
	//generate random number between 0-1
	int n = (rand() % 200)/200;
	//set reset value as a time between 0-1 s;
	printf("Random delay is: %d", n);
	tim5->ARR = n*16000000; // 1 s
	tim5->CCR1 = n*16000000; // 1 s
}
