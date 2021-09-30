/*
 * timer.c
 *
 *  Created on: Jan 27, 2020
 *      Author: navinj
 *
 *  Implementation of timer3 functions, including setup, wave generation
 *  and helper functions to convert frequency to ticks
 */

#include "timer.h"
#include"delay.h"
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
 * Makes a timer structure with the base address of TIM3
 */
volatile TIM* tim = (TIM*) 0x40000400;

/*
 * Helper function to convert input frequency to
 * ticks to input into timer
 *
 * frequency: Input frequency to convert
 *
 * returns the ticks needed to output a square wave at the input frequency
 * when the timer is set to a prescale of 8
 */
static uint32_t frequencytoTicks(uint32_t frequency);

void timer_init(){

	*RCC_AHB1ENR |= (1<<1);

	*RCC_APB1ENR |= (1<<1);

	*GPIOB_MODER &= ~(0x300);
	*GPIOB_MODER |= (0x200);

	*GPIOB_AFRL |= (0x20000);

	tim->PSC = 7;

	tim->CCMR1 = (0b011<<4);

	tim->CCER = 1;

}

/*
 * Plays a sound at a given frequency for a given length
 *
 * frequency: input frequency to generate wave at
 * delay: how long to play the sound
 */
void timer_playSound(uint32_t frequency, uint32_t delay){

	tim->PSC = 7;

	uint32_t ticks = frequencytoTicks(frequency);

	tim->ARR = ticks;
	tim->CCR1 = ticks;

	tim->CCMR1 = (0b011<<4);

	tim->CCER = 1;

	tim->CR1 = 1;

	delay_1ms(delay);

	tim->CR1 = 0;

	delay_1ms(1);

}

/*
 * Sets a sound to play on the speaker when timer is enabled
 *
 * frequency: input frequency of sound to play
 */
void timer_setSound(uint32_t frequency){


	uint32_t ticks = frequencytoTicks(frequency);

	tim->ARR = ticks;
	tim->CCR1 = ticks;

}

/*
 * Enables the timer to play a continuous sound
 */
void timer_play(){
	tim->CR1 = 1;
}

/*
 * Disables the timer to stop sound
 */
void timer_stop(){
	tim->CR1 = 0;
}

static uint32_t frequencytoTicks(uint32_t frequency){
	return (1000000/frequency);
}
