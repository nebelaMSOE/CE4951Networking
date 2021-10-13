#include "transmit.h"
#include <inttypes.h>

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

// this is TIM3
static volatile TIM* tim = (TIM*) 0x40000400;

static char* data_ptr = (char*) 0; // the data being sent
static uint32_t transmit_len = 0; // the number of bytes
static uint32_t transmit_pos = 0; // byte offset
static uint32_t transmit_bit = 0; // bit offset

static uint32_t half_bit = 0; // which half-bit is being sent (0 for first, 1 for second)

static uint32_t sent = 0; // number of half-bits sent

void init_transmitter(void)
{
	*RCC_APB1ENR |= 1 << 1;
	*NVIC_ISER0 |= 1 << 29;

	tim->ARR = 8000; // .5 ms
	tim->CCR1 = 8000; // .5 ms
	tim->DIER = 1;

	// TODO: initialize a pin to transmit on
}

void transmit_string(char *data, uint32_t len)
{
	data_ptr = data;
	transmit_len = len;
	transmit_pos = 0;
	half_bit = 0;

	// start timer
	tim->CR1 |= 1;
}

void TIM3_IRQHandler(void)
{
	// clear flag
	tim->SR &= ~1;

	// we are done transmitting; turn stop timer
	if (transmit_pos == transmit_len && half_bit == 0) {
		tim->CR1 &= ~1;
		return;
	}

	char byte = data_ptr[transmit_pos];
	char bit = (byte & (0x80 >> transmit_bit));

	// TODO: properly handle current state

	int a; // remove this

	if (half_bit == 0) {
		// send first half_bit

		if (bit == 0) {
			// TODO: drive pin high
			a = 1;
		} else {
			// TODO: drive pin low
			a = 0;
		}

		half_bit = 1;
	} else {
		// send second half_bit

		if (bit == 0) {
			// TODO: drive pin low
			a = 0;
		} else {
			// TODO: drive pin high
			a = 1;
		}

		if (transmit_bit != 7) {
			transmit_bit += 1;
		} else {
			transmit_bit = 0;
			transmit_pos += 1;
		}
		half_bit = 0;
	}

	sent += 1;
}
