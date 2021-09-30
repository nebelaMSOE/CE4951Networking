/*
 * rotary.c
 *
 *  Created on: Feb 3, 2020
 *      Author: navinj
 *  Rotary encoder source file, including
 *  initialization definition and interrupt handlers
 */

#include "rotary.h"
#include "delay.h"
#include "tuner.h"
#include <inttypes.h>

/*
 * Initializes the rotary encoder to read input with interrupts
 * including setting input and pull-up, as well as enabling the external interrupts
 */
void rotary_init(){
	*RCC_AHB1ENR |= (1<<GPIOAEN);
	*RCC_APB2ENR |= (SYSCFGEN);

	*GPIOA_MODER &= ~(0x300000F);

	*GPIOA_PUPDR &= ~(0x300000F);
	*GPIOA_PUPDR |= (0x1000005);

	*SYSCFG_EXTICR1 &= ~(0xF);
	*SYSCFG_EXTICR4 &= ~(0xF);

	*EXTI_FTSR |= (0b1000000000001);

	*NVIC_ISER0 |= (1<<6);
	*NVIC_ISER1 |= (1<<8);
}

/*
 * Enables the external interrupts in NVIC
 * Allowing the ISR to run
 */
void rotary_enable(){
	*EXTI_IMR |= (0b1000000000001);
}

/*
 * Disables the external interupts in NVIC
 * The ISR's will not run
 */
void rotary_disable(){
	*EXTI_IMR &= ~(0b1000000000001);
}

/*
 * Interrupt handler to read rotary encoder rotation
 * reads 2 if clockwise, 0 if counterclockwise
 *
 * Currently setup to step up/down played notes in tuner
 */
void EXTI0_IRQHandler(void){
	*EXTI_PR |= (1);
	delay_1us(15);
	uint8_t rotary = (*GPIOA_IDR & 0b11);
	if (rotary == 2){
		//Clockwise
		tuner_stepUp();
	} else if (rotary == 0){
		//Counter-Clockwise
		tuner_stepDown();
	}
}

/*
 * Interrupt handler to read push of encoder
 *
 * Currently unused
 */
void EXTI15_10_IRQHandler(void){
	*EXTI_PR |= (1<<12);
	delay_1us(15);
	//Button Press
}
