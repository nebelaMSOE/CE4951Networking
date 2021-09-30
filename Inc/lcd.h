/*
 * lcd.h
 *
 *  Created on: Dec 18, 2019
 *      Author: navinj
 * Header file for LCD functions
 */

#ifndef LCD_H_
#define LCD_H_

#include <inttypes.h>
#include <stdio.h>

//Memory and bit location defines
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830

#define GPIOAEN 0
#define GPIOCEN 2

#define GPIOA_MODER (volatile uint32_t*) 0x40020000
#define GPIOA_PUPDR (volatile uint32_t*) 0x4002000C
#define GPIOA_IDR (volatile uint32_t*) 0x40020010
#define GPIOA_ODR (volatile uint32_t*) 0x40020014
#define GPIOA_BSRR (volatile uint32_t*) 0x40020018

#define GPIOC_MODER (volatile uint32_t*) 0x40020800
#define GPIOC_PUPDR (volatile uint32_t*) 0x4002080C
#define GPIOC_IDR (volatile uint32_t*) 0x40020810
#define GPIOC_ODR (volatile uint32_t*) 0x40020814
#define GPIOC_BSRR (volatile uint32_t*) 0x40020818

#define RS_SET 1<<8
#define RS_CLR 1<<24
#define RW_SET 1<<9
#define RW_CLR 1<<25
#define E_SET 1<<10
#define E_CLR 1<<26

/*
 * lcd_init
 * 	Initializes the LCD
 * 	Configures ports and writes startup sequence
 * 	of commands to LCD
 * 	No return
 */
void lcd_init();

/*
 * lcd_clear
 * 	Writes the clear command to the LCD
 * 	CLears display and returns cursor to home position
 * 	No return
 */
void lcd_clear();

/*
 * lcd_home
 * 	Writes command to the LCD
 * 	Returns cursor to home position
 * 	No return
 */
void lcd_home();

/*
 * lcd_setPosition
 * 	Sets the cursor to a specified position
 * 	row- zero based row location
 * 	column- zero based column location
 * 	No return
 */
void lcd_setPosition(uint8_t row, uint8_t column);

/*
 * lcd_printString
 *	Accepts "string," a null terminated character array
 *	and prints all of the characters to the LCD
 *	Returns number of characters printed
 */
uint8_t lcd_printString(char string[]);

/*
 * lcd_printChar
 * 	Accepts char "character" and prints it to the LCD
 * 	No return
 */
void lcd_printChar(char character);

/*
 * lcd_printNum
 * 	Accepts 32-bit integer "num," converting it to ascii
 * 	and printing it to the LCD
 * 	No return
 */
void lcd_printNum(uint32_t num);

#endif /* LCD_H_ */
