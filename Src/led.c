/*
 * Author: Andrew Nebel
 * Created: December 14 2019
 * File: led.c
 * Description: Preforms various actions using the leds
 * including init and on/off.
 */

 //declaration header file
#include "led.h"
#include "delay.h"
#include <inttypes.h>
#include <stdio.h>

//Keeps track of current speed value
static uint8_t currentSpeed = 0;
//Keeps track of the delay set by speed entered, base 750ms
static uint16_t speedDelay = BASE_DELAY;

/*
 * led_init()
 * Enables the GPIOB in RCC_AHB1ENR
 * Sets LED0 - LED9 to output mode ("01")
 * Args: na
 * Return: na
 */
void led_init(){

	//Enables GPIOB in RCC_AHB1ENR
	*RCC_AHB1ENR |= (1<<GPIOBEN);

	//Enable lower 6 leds
	*GPIOB_MODER &= ~(0x3FFF<<10);
	*GPIOB_MODER |= (0x555<<10);

	//Enables upper 4 leds
	*GPIOB_MODER &= ~(0xFF<<24);
	*GPIOB_MODER |= (0x55<<24);

}

/*
 * led_allOn()
 * Turn on all leds
 * Args: na
 * Return: na
 */
void led_allOn(){
	//Set led output pins to 1
	*GPIOB_ODR |= ((0b111111<<5) | (0b1111<<12));
}

/*
 * led_allOff()
 * Turn off all leds
 * Args: na
 * Return: na
 */
void led_allOff(){
	//Set led output pins to 0
	*GPIOB_ODR &= ~((0b111111<<5) | (0b1111<<12));
}

/*
 * led_on(uint8_t ledIndex)
 * Turn on specific led, prints error if out of range
 * Args: uint8_t ledIndex: index of led
 * Return: na
 */
void led_on(uint8_t ledIndex){
	//Enables specific LED pin in BSRR set section
	switch (ledIndex) {
			case 0 : *GPIOB_BSRR |= (1<<5); break;
			case 1 : *GPIOB_BSRR |= (1<<6); break;
			case 2 : *GPIOB_BSRR |= (1<<7); break;
			case 3 : *GPIOB_BSRR |= (1<<8); break;
			case 4 : *GPIOB_BSRR |= (1<<9); break;
			case 5 : *GPIOB_BSRR |= (1<<10); break;
			case 6 : *GPIOB_BSRR |= (1<<12); break;
			case 7 : *GPIOB_BSRR |= (1<<13); break;
			case 8 : *GPIOB_BSRR |= (1<<14); break;
			case 9 : *GPIOB_BSRR |= (1<<15); break;
			default: printf("Args is out of range or not a number"); break;
	}
}

/*
 * led_off(uint8_t ledIndex)
 * Turn off specific led, prints error if out of range
 * Args: uint8_t ledIndex: index of led
 * Return: na
 */
void led_off(uint8_t ledIndex){
	//Disables specific LED pin via BSRR reset section
		switch (ledIndex) {
				case 0 : *GPIOB_BSRR |= (1<<21); break;
				case 1 : *GPIOB_BSRR |= (1<<22); break;
				case 2 : *GPIOB_BSRR |= (1<<23); break;
				case 3 : *GPIOB_BSRR |= (1<<24); break;
				case 4 : *GPIOB_BSRR |= (1<<25); break;
				case 5 : *GPIOB_BSRR |= (1<<26); break;
				case 6 : *GPIOB_BSRR |= (1<<28); break;
				case 7 : *GPIOB_BSRR |= (1<<29); break;
				case 8 : *GPIOB_BSRR |= (1<<30); break;
				case 9 : *GPIOB_BSRR |= (1<<31); break;
				default: printf("Args is out of range or not a number"); break;
		}
}

/*
 * led_scan()
 * Scans an led across and back at current speed
 * Args: na
 * Return: na
 */
void led_scan(){
	//Turn off all leds so scan can be seen
	led_allOff();

	//Led scan right
	for(int8_t i = 9; i>0; i--){
		//turn on led
		led_on(i);
		//delay based off of speed value
		delay_1ms(speedDelay);
		//turn off led
		led_off(i);
	}

	//Led scan left
	for(int8_t i = 0; i<10; i++){
			//turn on led
			led_on(i);
			//delay based off of speed value
			delay_1ms(speedDelay);
			//turn off led
			led_off(i);
		}

}

/*
 * led_flash()
 * Flash all of the lights 10 times at the current speed
 * Args: na
 * Return: na
 */
void led_flash(){
	//Turn off all leds so flash can be seen
	led_allOff();
	//repeat 10 times
	for(uint8_t i = 0; i<10; i++){
		//turn lights on
		led_allOn();
		//wait
		delay_1ms(speedDelay);
		//turn lights off
		led_allOff();
		//wait
		delay_1ms(speedDelay);
	}
}

/*
 * led_setSpeed(uint8_t speed)
 * Sets the speed to an integer 0-9, else print error
 * Args: uint8_t speed: speed
 * Return: na
 */
void led_setSpeed(uint8_t speed){
	//Check if speed is between 0-9
	if(speed>9 || speed<0){
		printf("Value for speed must be an integer between 0 and 9\n");
	} else {
		//Assigns new speed value
		currentSpeed = speed;
		//Assigns new delay value
		speedDelay = BASE_DELAY/currentSpeed;
	}
}

/*
 * led_incSpeed()
 * Increases speed by one if not at max value
 * Args: na
 * Return: na
 */
void led_incSpeed(){
	//Check if speed is at max
	if(currentSpeed == 9){
		printf("Speed is already at the max value of 9\n");
	} else {
		//increment speed
		currentSpeed++;
		//Assigns new delay value
	    speedDelay = BASE_DELAY/currentSpeed;
	    //Print speed increased
	    printf("Speed increased by 1\n");
	}
}

/*
 * led_decSpeed()
 * Decreases speed by one if not at min value
 * Args: na
 * Return: na
 */
void led_decSpeed(){
	//Check if speed is at its min
	if(currentSpeed == 0){
		printf("Speed is already at the min value of 0\n");
	} else {
		//decrement speed
		currentSpeed--;
		//Assigns new delay value
		speedDelay = BASE_DELAY/currentSpeed;
		//Print speed decreased
		printf("Speed decreased by 1\n");
	}
}

/*
 * getCurrentSpeed()
 * Returns currentSpeed
 * Args: na
 * Return: currentSpeed
 */
uint8_t getCurrentSpeed()
{
	return currentSpeed;
}


