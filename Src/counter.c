/*
 * counter.c
 *
 *  Created on: Feb 3, 2020
 *      Author: navinj
 *
 * Counter source file, with functions to initialize the counter
 * for time tracking in milliseconds
 */

#include "counter.h"
#include "maze.h"
#include <inttypes.h>

/*
 * Structure for memory mapped timer registers
 */
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

/*
 * Makes a timer structure with the base address of TIM2
 */
volatile TIM* tim = (TIM*) 0x40000000;

/*
 * Keeps track of the time between start and stop
 * in milliseconds
 */
static uint32_t timeTaken = 0;

/*
 * Initializes the counter to use interrupts and
 * keep track of time in milliseconds
 */
void counter_init(){
	*NVIC_ISER0 |= (1<<28);

	*RCC_APB1ENR |= 1;

	tim->ARR = 16000;
	tim->CCR1 = 16000;

	tim->DIER = 2;

	tim->CCMR1 = (0b011<<4);

	tim->CCER = 1;
}

/*
 * Starts the counter
 */
void counter_start(){
	timeTaken = 0;
	tim->CR1 = 1;
}

/*
 * Stops the counter
 */
void counter_stop(){
	tim->CR1 = 0;
}

/*
 * Returns the amount of milliseconds between start and stop of count
 */
uint32_t counter_getCount(){
	return timeTaken;
}

/*
 * Interrupt handler to handle interrupts
 * from the counter
 *
 * Setup to increment the milliseond count in the maze game
 */
void TIM2_IRQHandler(void){
	tim->SR = ~(1<<1);
	timeTaken++;
}
