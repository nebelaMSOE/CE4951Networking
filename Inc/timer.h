/*
 * timer.h
 *
 *  Created on: Jan 27, 2020
 *      Author: navinj
 *
 * 	Header file for timer3 related functions
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <inttypes.h>

#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
#define GPIOBEN 1
#define GPIOB_MODER (volatile uint32_t*) 0x40020400
#define GPIOB_AFRL (volatile uint32_t*) 0x40020420

/**
 * Initializes the timer for square wave generation
 * turning on the GPIO ports and the timer
 */
void timer_init();

/**
 * Sets up the timer and sends a square wave with the frequency
 * "frequency" and plays that sound for "delay" milliseconds
 */
void timer_playSound(uint32_t frequency, uint32_t delay);

/*
 * Sets the frequency "frequency" of the sound that the
 * timer will play when enabled
 */
void timer_setSound(uint32_t frequency);

/*
 * Enables the timer so a sound will play continuously
 */
void timer_play();

/*
 * Stops the timer so no sound will be playing
 */
void timer_stop();

#endif /* TIMER_H_ */
