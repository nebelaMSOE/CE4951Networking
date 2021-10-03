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
	/*
	 *
	 * test code to input capture on TIM2
	*NVIC_ISER0 |= (1<<28);

	*RCC_APB1ENR |= 1;

	*RCC_AHB1ENR |= 1;

	*GPIOA_MODER |= (0b10 << 30);

	*GPIOA_AFRH |= (0b0010 << 28);

	tim->CCMR1 |= (0b01);

	tim->CCMR1 |= (0b0011<<4);

	tim->CCER |= 0b1011;

	tim->DIER = 2;
	*/

	//Unmask interrupt
	*NVIC_ISER0 |= (1<<28);

	*RCC_APB1ENR |= 1;

	//Set timeout for 1.1ms
	tim->ARR = 17600;
	tim->CCR1 = 17600;

	//Enable interrupt
	tim->DIER = 2;

	tim->CCMR1 = (0b011<<4);

	tim->CCER = 1;
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
	*GPIOA_PUPDR &= ~(0xC0000000);
	*GPIOA_PUPDR |= (0x40000000);

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
 * Setup to check receive line and update state machine accordingly
 */
void TIM2_IRQHandler(void){
	tim->SR = ~(1<<1); //Clear flag
}

/*
 * Interrupt handler triggered on edge of PA15
 *
 * Should start a counter and move state to BUSY
 */
void EXTI15_10_IRQHandler(void){
	*EXTI_PR |= (1<<15); //Clear flag
}
