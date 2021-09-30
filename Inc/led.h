/*
 * Author: Andrew Nebel
 * Created: December 14 2019
 * File: led.h
 * Description: Defines constants related to
 * leds and GPIOB and outlines method for led operations.
 */

// Guards
#ifndef LED_H_
#define LED_H_

#include <inttypes.h>



#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
//Bit that enables GPIOB
#define GPIOBEN 1
//Base delay of 750ms
#define BASE_DELAY 750
//Addresses of GPIOB's control/data registers
#define GPIOB_MODER (volatile uint32_t*) 0x40020400
#define GPIOB_PUPDR (volatile uint32_t*) 0x4002040C
#define GPIOB_IDR (volatile uint32_t*) 0x40020410
#define GPIOB_ODR (volatile uint32_t*) 0x40020414
#define GPIOB_BSRR (volatile uint32_t*) 0x40020418

/*
 * led_init()
 * Enables the GPIOB in RCC_AHB1ENR
 * Sets LED0 - LED9 to output mode ("01")
 * Args: na
 * Return: na
 */
void led_init();

/*
 * led_allOn()
 * Turn on all leds
 * Args: na
 * Return: na
 */
void led_allOn();

/*
 * led_allOff()
 * Turn off all leds
 * Args: na
 * Return: na
 */
void led_allOff();


/*
 * led_on(uint8_t ledIndex)
 * Turn on specific led, prints error if out of range
 * Args: uint8_t ledIndex: index of led
 * Return: na
 */
void led_on(uint8_t ledIndex);

/*
 * led_off(uint8_t ledIndex)
 * Turn off specific led, prints error if out of range
 * Args: uint8_t ledIndex: index of led
 * Return: na
 */
void led_off(uint8_t ledIndex);


/*
 * led_scan()
 * Scans an led across and back at current speed
 * Args: na
 * Return: na
 */
void led_scan();

/*
 * led_flash()
 * Flash all of the lights 10 times at the current speed
 * Args: na
 * Return: na
 */
void led_flash();

/*
 * led_setSpeed(uint8_t speed)
 * Sets the speed to an integer 0-9, else print error
 * Args: uint8_t speed: speed
 * Return: na
 */
void led_setSpeed(uint8_t speed);

/*
 * led_incSpeed()
 * Increases speed by one if not at max value
 * Args: na
 * Return: na
 */
void led_incSpeed();

/*
 * led_decSpeed()
 * Decreases speed by one if not at min value
 * Args: na
 * Return: na
 */
void led_decSpeed();

/*
 * getCurrentSpeed()
 * Returns currentSpeed
 * Args: na
 * Return: currentSpeed
 */
uint8_t getCurrentSpeed();



#endif /* LED_H_ */
