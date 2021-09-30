/*
 * counter.h
 *
 *  Created on: Feb 3, 2020
 *      Author: navinj
 *  counter header file to allow for timing of certain actions
 */

#ifndef COUNTER_H_
#define COUNTER_H_

#include <inttypes.h>

/*
 * Register addresses
 */
#define NVIC_ISER0 (volatile uint32_t*) 0xE000E100
#define	NVIC_ICPR0 (volatile uint32_t*) 0xE000E280
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840

/*
 * Initializes the counter to use interrupts
 * and keep track of time in milliseconds
 */
void counter_init();

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

#endif /* COUNTER_H_ */
