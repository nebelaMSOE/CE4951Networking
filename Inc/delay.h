/*
 * delay.h
 *
 * Author: navinj
 * Header file for delay functions
 */

//include guards
#ifndef DELAY_H_
#define DELAY_H_

#include <inttypes.h>

//Systick Register Addresses
#define STK_CTRL (volatile uint32_t*) 0xE000E010
#define STK_LOAD (volatile uint32_t*) 0xE000E014
#define STK_VAL (volatile uint32_t*) 0xE000E018

//Bit locations in STK_CTRL
#define EN 0
#define TICKINT 1
#define CLKSOURCE 2
#define COUNTFLAG 16

/*
 * delay_1ms
 * 		Busy wait for n ms
 *
 * 		For n iterations
 * 			load number of cycles for 1 ms
 * 			set one to enable and clock source
 *
 * 			wait for countflag to be set
 */
void delay_1ms(uint32_t n);

/*
 * delay_1us
 * Uses Systick to delay for
 * n number of microseconds
 */
void delay_1us(uint32_t n);

/*
 * delay_1s
 * Uses Systick to delay for
 * n number of seconds
 */
void delay_1s(uint32_t n);


#endif /* DELAY_H_ */
