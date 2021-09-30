/*
 * lcd.c
 *
 *  Created on: Dec 18, 2019
 *      Author: navinj
 * Functions for the LCD, including non-global
 * helper functions
 */

#include <inttypes.h>
#include "lcd.h"
#include "delay.h"

/*
 * Helper function that sets up ports in GPIO
 */
static void port_setup(){
	*RCC_AHB1ENR |= ((1<<GPIOAEN)|(1<<GPIOCEN));

	*GPIOA_MODER &= ~(0xFFFF<<8);
	*GPIOA_MODER |= (0x5555<<8);

	*GPIOC_MODER &= ~(0x3F<<16);
	*GPIOC_MODER |= (0x15<<16);
}

/*
 * Helper function that writes an input
 * instruction to the LCD
 *
 * instr: instruction to write to LCD
 */
static void write_instr(uint8_t instr){
	*GPIOC_BSRR |= ((RS_CLR)|(RW_CLR)|(E_CLR));

	*GPIOC_BSRR |= (E_SET);

	*GPIOA_ODR &= ~(0x0FF0);
	*GPIOA_ODR |= (instr<<4);

	*GPIOC_BSRR |= (E_CLR);

	if ((instr == 1)||(instr == 2)||(instr == 3)){
		delay_1ms(2);
	} else {
		delay_1us(37);
	}
}

/*
 * Helper function to write input
 * data to LCD
 *
 * data: input data to write to LCD
 */
static void write_data(uint8_t data){
	*GPIOC_BSRR |= ((RS_SET)|(RW_CLR)|(E_CLR));

	*GPIOC_BSRR |= (E_SET);

	*GPIOA_ODR &= ~(0x0FF0);
	*GPIOA_ODR |= (data<<4);

	*GPIOC_BSRR |= (E_CLR);

	delay_1us(37);
}

/*
 * Initializes the LCD:
 * Sets up ports and writes startup
 * instruction sequence
 */
void lcd_init(){
	port_setup();

	delay_1ms(40);

	//Write startup sequence
	write_instr(0x38);
	write_instr(0x38);
	write_instr(0x0F);
	write_instr(0x01);
	write_instr(0x06);
}

/*
 * Writes clear command to LCD
 */
void lcd_clear(){
	write_instr(0x01);
}

/*
 * Writes home command to LCD
 */
void lcd_home(){
	write_instr(0x02);
}

/*
 * Moves the cursor to user specified position
 * using zero based row and column inputs
 *
 * row: zero based row input
 * column: zero based column input
 */
void lcd_setPosition(uint8_t row, uint8_t column){
	uint8_t pos = 0x80;
	if (row == 0){
		pos += 0x40;
	}
	pos += column;
	write_instr(pos);
}

/*
 * Prints all characters in array "string" to LCD
 * Returns number of characters written
 *
 * string: input string as a char array
 */
uint8_t lcd_printString(char string[]){
	uint8_t charprinted = 0;
	uint8_t arraypointer = 0;
	char printchar = string[arraypointer];
	while (printchar != 0){
		write_data(printchar);
		arraypointer++;
		printchar = string[arraypointer];
		charprinted++;
	}
	return charprinted;
}

/*
 * Prints input char, "character" to the LCD
 *
 * character: char to write to LCD
 */
void lcd_printChar(char character){
	write_data(character);
}

/*
 * Converts input integer "num" to ascii and
 * prints it to the LCD
 *
 * num: number to write to LCD
 */
void lcd_printNum(uint32_t num){
	char buffer[50];
	sprintf(buffer, "%d", (int)num);
	lcd_printString(buffer);
}
