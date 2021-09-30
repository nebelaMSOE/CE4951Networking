/*
 * delay.c
 *
 * Author: Joshua Navin
 * Delay functions using SYSTICK to delay
 * for a set amount of time
 */

#include <inttypes.h>
#include "delay.h"  //include declaration header file

/*
 * Delays for input number of milliseconds
 * n: input number of milliseconds to delay
 */
void delay_1ms(uint32_t n){
	uint32_t ticks = 16000;
	uint32_t count = 0;

	*STK_LOAD = ticks;

	*STK_VAL = 0;

	*STK_CTRL |= ((1<<EN)|(1<<CLKSOURCE));

	while (count < n){
		//Check count flag and if set, increment count by one
		if ((*STK_CTRL & (1<<COUNTFLAG)) == (1<<16)){
			count++;
		}
	}
}

/*
 * Delays for input number of microseconds
 * n: input number of microseconds to delay
 */
void delay_1us(uint32_t n){
	uint32_t ticks = 16;
	uint32_t count = 0;

	*STK_LOAD = ticks;

	*STK_VAL = 0;

	*STK_CTRL |= ((1<<EN)|(1<<CLKSOURCE));

	while (count < n){
		//Check count flag and if set, increment count by one
		if ((*STK_CTRL & (1<<COUNTFLAG)) == (1<<16)){
			count++;
		}
	}
}

/*
 * Delays for input number of seconds
 * n: input number of seconds to delay
 */
void delay_1s(uint32_t n){
	uint32_t ticks = 16000000;
	uint32_t count = 0;

	*STK_LOAD = ticks;

	*STK_VAL = 0;

	*STK_CTRL |= ((1<<EN)|(1<<CLKSOURCE));

	while (count < n){
		//Check count flag and if set, increment count by one
		if ((*STK_CTRL & (1<<COUNTFLAG)) == (1<<16)){
			count++;
		}
	}
}
