/*
 * counter.h
 *
 *  Created on: Oct 3, 2021
 *      Author: navinj
 *  Collision detection header file
 */

#ifndef COLLISION_H_
#define COLLISION_H_

#include <inttypes.h>

/*
 * Register addresses
 */
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define RCC_APB2ENR (volatile uint32_t*) 0x40023844
#define GPIOAEN 0
#define SYSCFGEN 1<<14

#define GPIOA_MODER (volatile uint32_t*) 0x40020000
#define GPIOA_OTYPER (volatile uint32_t*) 0x40020004
#define GPIOA_PUPDR (volatile uint32_t*) 0x4002000C
#define GPIOA_IDR (volatile uint32_t*) 0x40020010
#define GPIOA_ODR (volatile uint32_t*) 0x40020014
#define GPIOA_BSRR (volatile uint32_t*) 0x40020018
#define GPIOA_AFRH (volatile uint32_t*) 0x40020024

#define SYSCFG_EXTICR4 (volatile uint32_t*) 0x40013814

#define EXTI_IMR (volatile uint32_t*) 0x40013C00
#define EXTI_RTSR (volatile uint32_t*) 0x40013C08
#define EXTI_FTSR (volatile uint32_t*) 0x40013C0C
#define EXTI_PR (volatile uint32_t*) 0x40013C14

#define NVIC_ISER0 (volatile uint32_t*) 0xE000E100
#define NVIC_ISER1 (volatile uint32_t*) 0xE000E104
#define NVIC_ICER0 (volatile uint32_t*) 0xE000E080
#define NVIC_ICER1 (volatile uint32_t*) 0xE000E084
#define NVIC_ICPR0 (volatile uint32_t*) 0xE000E180

/*
 * Initializes the counter to use interrupts
 * and keep track of time
 */
void counter_init();

void detect_init();

/*
 * Starts the counter
 */
void counter_start();

/*
 * Stops the counter
 */
void counter_stop();

/*
 * Gets the millisecond count between start and stop of counter
 */
uint32_t counter_getCount();

//resets counter value
void counter_resetValue();

//reset counter flag
void counter_resetFlag();

#endif /* COLLISION_H_ */
