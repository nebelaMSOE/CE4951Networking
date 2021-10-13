#ifndef TRANSMIT_H_
#define TRANSMIT_H_

#include <inttypes.h>

#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
#define NVIC_ISER0 (volatile uint32_t*) 0xE000E100

/*
 * Initialize the timer & interrupt for transmitting data
 */
void init_transmitter(void);

/*
 * transmit a string
 */
void transmit_string(char *data, uint32_t len);

#endif
