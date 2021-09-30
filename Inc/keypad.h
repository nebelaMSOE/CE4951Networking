/*
 * keypad.h
 *
 *      Author: livingston
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <inttypes.h>

//Important Register Addresses
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define GPIOCEN 2
#define GPIOC_MODER (volatile uint32_t*) 0x40020800
#define GPIOC_PUPDR (volatile uint32_t*) 0x4002080C
#define GPIOC_IDR (volatile uint32_t*) 0x40020810
#define GPIOC_ODR (volatile uint32_t*) 0x40020814
#define GPIOC_BSRR (volatile uint32_t*) 0x40020818

//Code to initialize the keypad
//	1. Turns on GPIOC Port
//  2. Enables pull-ups
extern void keypad_init();

//Returns the code for the current key pressed
//	0 - No key
//  1  2   3  4
//
//  5  6  7  8
//
//  9 10  11 12
//
//  13 14 15 16
// 255 - Error
// This function does not block the flow of the program
extern uint8_t keypad_getKeyNoBlock();

//Returns the code for the next pressed
//	0 - No key
//  1  2   3  4
//
//  5  6  7  8
//
//  9 10  11 12
//
//  13 14 15 16
// 255 - Error
// This function will block the flow of the program until a
//   key is pressed.
extern uint8_t keypad_getKey();

/*
 * Returns the number of the number key given the
 * key index, 0 if not a numbered key
 */
uint8_t keypad_getNum(uint8_t num);

/*
 * Returns the character of a key given the key index
 */
char keypad_getChar(uint8_t num);

#endif /* KEYPAD_H_ */
