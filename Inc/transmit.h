#ifndef TRANSMIT_H_
#define TRANSMIT_H_

#include <inttypes.h>

//Memory and bit location defines
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
#define NVIC_ISER0 (volatile uint32_t*) 0xE000E100
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830

#define GPIOCEN 2

#define GPIOC_MODER (volatile uint32_t*) 0x40020800
#define GPIOC_PUPDR (volatile uint32_t*) 0x4002080C
#define GPIOC_IDR (volatile uint32_t*) 0x40020810
#define GPIOC_ODR (volatile uint32_t*) 0x40020814
#define GPIOC_BSRR (volatile uint32_t*) 0x40020818

/*
 * Initialize the timer & interrupt for transmitting data
 */
void init_transmitter(void);

/*
 * transmit a string
 */
void transmit_string(char *data, uint32_t len);

/*
 * Starts the counter
 */
void transmitter_start();

/*
 * Stops the counter
 */
void transmitter_stop();

//resets counter value
void transmitter_resetValue();

//reset counter flag
void transmitter_resetFlag();

void transmitter_setOutHigh();

void transmitter_setOutLow();

#endif
