

/*
 * counter.c
 *
 *  Created on: Oct 3, 2021
 *      Author: navinj
 *
 * Collision detection source file, enables counter
 * to track edges, as well as edge detection on pin A15
 */

#include "collision.h"
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
 * keep track of time
 */
void counter_init(){

	//Unmask interrupt
	*NVIC_ISER0 |= (1<<28);

	*RCC_APB1ENR |= 1;

	//Set timeout for 1.1ms
	tim->ARR = 17600;
	tim->CCR1 = 17600;

	//Enable interrupt
	tim->DIER = 1;

	// tim->CCMR1 = (0b011<<4);

	// tim->CCER = 1;
}

/*
 * Init function to enable external interrupt
 * on pin PA15, triggering on any edge
 *
 */
void detect_init(){
	//Enable components
	*RCC_AHB1ENR |= (1<<GPIOAEN);
	*RCC_APB2ENR |= (SYSCFGEN);

	//Set A15 to input (Clear that part of the register)
	*GPIOA_MODER &= ~(0xC0000000);

	//Set A15 to pull up
//	*GPIOA_PUPDR &= ~(0xC0000000);
//	*GPIOA_PUPDR |= (0x40000000);
//	*GPIOA_OTYPER |= 1<<15;

	//Enable interrupt
	*SYSCFG_EXTICR4 &= ~(0xF000);

	//Enable trigger on both edges
	*EXTI_RTSR |= (1<<15);
	*EXTI_FTSR |= (1<<15);

	//Unmask interrupt
	*NVIC_ISER1 |= (1<<8);

	//Enable interrupt
	*EXTI_IMR |= (1<<15);
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
	tim->CR1 &= ~1;
}

/*
 * Returns the amount of milliseconds between start and stop of count
 */
uint32_t counter_getCount(){
	return timeTaken;
}

//resets value of counter
void counter_resetValue(){
	tim->CNT = 0;
}

//resets interrupt flag
void counter_resetFlag(){
	tim->SR &= ~1;
}
