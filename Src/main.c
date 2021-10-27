/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
  ******************************************************************************
  Call of tuner sequence in main function.
*/

#include "led.h"
#include "delay.h"
#include "uart_driver.h"
#include "collision.h"
#include "transmit.h"
#include "receiver.h"
#include <inttypes.h>
#include <stdio.h>

#define F_CPU 16000000UL

//max size of transmit array
#define ARSIZE 255

enum State {IDLE, BUSY, COLLISION};

enum State currentState = IDLE;

//value to keep track of voltage on A15

static uint32_t valueIn = 1;

//Receiver Variables
static uint32_t receive_pos = 0;
static uint8_t inputBuffer[17];
static uint8_t receive_done = 0;
static char sendToConsole;

//Transmission Variables
static char* data_ptr = (char*) 0; // the data being sent
static uint32_t transmit_len = 0; // the number of bytes
static uint32_t transmit_pos = 0; // byte offset
static uint32_t transmit_bit = 0; // bit offset

static uint32_t half_bit = 0; // which half-bit is being sent (0 for first, 1 for second)

static uint32_t sent = 0; // number of half-bits sent

static uint32_t nextChar = 0; // position to put next char

/*
 * Makes a timer structure with the base address of TIM2
 */

//interupt handlers

/*
 * EXTI15_10_IRQHandler()
 * Handles the interrupts for a signal edge
 * on pin A15
 * Args: na
 * Return: na
 */
void EXTI15_10_IRQHandler(void) __attribute__ ((isr));

/*
 * TIM2_IRQHandler()
 * Interrupt handler to handle interrupts
 * from the counter
 * Args: na
 * Return: na
 */
void TIM2_IRQHandler(void) __attribute__ ((isr));

/*
 * TIM3_IRQHandler()
 * Interrupt handler to handle interrupts
 * from transmitter timer
 * Args: na
 * Return: na
 */
void TIM3_IRQHandler(void) __attribute__ ((isr));

/*
 * TIM4_IRQHandler()
 * Interrupt handler to handle interrupts
 * from receiver timer
 * Args: na
 * Return: na
 */
void TIM4_IRQHandler(void) __attribute__ ((isr));


/*
 * E1: Any signal bus voltage edge
 * E2: Timer timeout when bus is logic-0
 * E3: Timer timeout when bus is logic-1
 * IDLE -> BUSY (E1)
 * BUSY -> COLLISION (E2)
 * BUSY -> IDLE (E3)
 * COLLISION -> BUSY (E1)
 */

int main(void)
{
	//Set up uart connection for 2000 baud
	init_usart2(2000, F_CPU);
	printf("CE4951 Networking Project");

	//Initialize leds
	led_init();
	//Initialize counter with timeout of 1.1ms
	counter_init();
	//Initialize pin PA15 and interrupts on any edge
	detect_init();
	// Initialize the transmitter
	init_transmitter();
	//Initialize the receiver
	receiver_init();

	//char test[2] = "Hi";
	//data_ptr = &test[0];
	//transmit_len = 2;
	transmit_pos = 0;
	half_bit = 0;

	//transmitter_start();
	//transmit_string(&test[0], 2);

	char transmitArray[ARSIZE];
	data_ptr = transmitArray;

	while(1){
		//look if there is anything new in uart
		if((*(USART_SR)&(1<<RXNE)) == (1<<RXNE)){

			transmitArray[nextChar] = usart2_getch();
			nextChar++;

			//if return character
			if (transmitArray[nextChar-1] == 0xa){
				transmit_len = nextChar-1;
				transmit_pos = 0;
				nextChar = 0;
				transmit_string(&transmitArray[transmit_pos], transmit_len);
			}
		}

		if(receive_done == 1){
			receive_done = 0;
			sendToConsole = (char)receiver_decodeMan(inputBuffer);
			printf("%c", sendToConsole);
		}

		switch (currentState)
		{
		case IDLE:
			//Left two LEDs on
			led_allOff();
			led_on(9);
			led_on(8);
			// Interrupt when E1

			break;

		case BUSY:
			//Middle two LEDs on
			led_allOff();
			led_on(5);
			led_on(4);
			//Interrupt when E2

			//Interrupt when E3

			break;

		case COLLISION:
			//Right two LEDs on
			led_allOff();
			led_on(1);
			led_on(0);
			//Interrupt when E1

			break;

		default:
			led_allOff();
			//Unexpected value for currentState
			//Resetting currentState to initial value
			currentState = IDLE;

			break;
		}
	}
}

/*
 * TIM2_IRQHandler()
 * Interrupt handler to handle interrupts
 * from the counter
 * Args: na
 * Return: na
 */
void TIM2_IRQHandler(void){
	counter_stop();
	counter_resetValue();
	counter_resetFlag();
	//get value on pin A15
	valueIn = (*GPIOA_IDR & 0x8000) >> 15;

	if(currentState == BUSY){
		//if busy and E2 move to collision
		if(valueIn == 0){
			currentState = COLLISION;
			//if busy and E3 move to idle
		} else if (valueIn == 1){
			currentState = IDLE;
		}
	}

}

/*
 * EXTI15_10_IRQHandler()
 * Handles the interrupts for a signal edge
 * on pin A15
 * Args: na
 * Return: na
 */
void EXTI15_10_IRQHandler(void){
	//verify interrupt on pin 15
	if((*EXTI_PR) & (1<<15)){
		//clear interrupt
		*EXTI_PR |= 1<<15;

		receiver_stop();
		receiver_resetValue();
		receiver_resetFlag();

		//Handle receipt of first edge of received signal
		if(receive_pos == 0){
			valueIn = (*GPIOA_IDR & 0x8000) >> 15;
			inputBuffer[receive_pos++] = !valueIn;
			inputBuffer[receive_pos++] = valueIn;
		}else{
			valueIn = (*GPIOA_IDR & 0x8000) >> 15;
			inputBuffer[receive_pos++] = valueIn;
		}

		if(receive_pos == 17){
			receive_pos = 0;
			receive_done = 1;
		}else{
			receiver_start();
		}

		switch (currentState)
				{
				case IDLE:
					//if idle and E1 move to busy
					currentState = BUSY;
					//reset counter value to 0
					counter_resetValue();
					//start counter
					counter_start();
					break;

				case COLLISION:
					//if collision and E1 move to busy
					currentState = BUSY;
					//reset counter value to 0
					counter_resetValue();
					//start counter
					counter_start();
					break;

				case BUSY:
					counter_stop();
					counter_resetValue();
					counter_resetFlag();
					counter_start();
					break;

				default:
					// this should never happen
					led_allOff();
					//Unexpected value for currentState
					//Resetting currentState to initial value
					currentState = IDLE;
					//stop counter
					counter_stop();

					break;
				}
	}
}

void TIM3_IRQHandler(void)
{
	// clear flag
	transmitter_resetFlag();

	// we are done transmitting; turn stop timer
	if (transmit_pos == transmit_len && half_bit == 0) {
		transmitter_setOutHigh();
		transmitter_stop();
		return;
	}

	char byte = data_ptr[transmit_pos];
	char bit = (byte & (0x80 >> transmit_bit));

	if(currentState != COLLISION){

		if (half_bit == 0) {
			// send first half_bit

			if (bit == 0) {
				//Set output pin to high
				transmitter_setOutHigh();
			} else {
				//Set output pin to low
				transmitter_setOutLow();
			}

			half_bit = 1;
		} else {
			// send second half_bit

			if (bit == 0) {
				//Set output pin to low
				transmitter_setOutLow();
			} else {
				//Set output pin to high
				transmitter_setOutHigh();
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
}

void TIM4_IRQHandler(void){
	receiver_stop();
	receiver_resetValue();
	receiver_resetFlag();

	valueIn = (*GPIOA_IDR & 0x8000) >> 15;

	inputBuffer[receive_pos++] = valueIn;

	if(receive_pos == 17){
		receive_pos = 0;
		receive_done = 1;
	}else{
		receiver_start();
	}
}
