/*
 * receiver.h
 *
 *  Created on: Oct 24, 2021
 *      Author: navinj
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include <inttypes.h>

/*
 * Register addresses
 */
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define RCC_APB2ENR (volatile uint32_t*) 0x40023844

#define NVIC_ISER0 (volatile uint32_t*) 0xE000E100
#define NVIC_ISER1 (volatile uint32_t*) 0xE000E104
#define NVIC_ICER0 (volatile uint32_t*) 0xE000E080
#define NVIC_ICER1 (volatile uint32_t*) 0xE000E084
#define NVIC_ICPR0 (volatile uint32_t*) 0xE000E180

void receiver_init();

/*
 * Starts the receiver counter
 */
void receiver_start();

/*
 * Stops the receiver counter
 */
void receiver_stop();

//resets receiver counter value
void receiver_resetValue();

//reset receiver flag
void receiver_resetFlag();

uint8_t receiver_decodeMan(uint8_t inputBuffer[]);

#endif /* RECEIVER_H_ */
