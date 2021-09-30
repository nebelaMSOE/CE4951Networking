/*
 * keypad.c
 *
 *      Author: livingston
 */

#include "keypad.h"
#include "delay.h"


void keypad_init(){
	//Enables the port
	*RCC_AHB1ENR |= (1<<GPIOCEN);

	//Sets KEY0 - KEY7 as Pull-Ups
	*GPIOC_PUPDR &= ~(0xFFFF);
	*GPIOC_PUPDR |= 0x5555;
}

uint8_t keypad_getKeyNoBlock(){

	uint8_t value = 0;
	uint8_t keycode = 0;

	//COLS to Inputs and ROWS to Outputs
	*GPIOC_MODER &= ~(0xFFFF);
	*GPIOC_MODER |= 0x5500;

	//Clears Rows in ODR
	*GPIOC_ODR &= ~0xFF;
	//Reads COLS in IDR
	value = (*GPIOC_IDR & 0xF);

	//if a button is pressed decode the key
	if (value != 0xF){
		//Copy COLS pattern from IDR to ODR
		*GPIOC_ODR &= ~0xFF;
		*GPIOC_ODR |= (*GPIOC_IDR & 0xF);

		//COLS to Output and ROWS to Inputs
		*GPIOC_MODER &= ~(0xFFFF);
		*GPIOC_MODER |= 0x0055;

		//Small delay (ensure you have this function)
		delay_1us(5);

		//Read ROWS from IDR
		value |= *GPIOC_IDR & 0xF0;

		//Decode Key
		switch (value){
		case 0b11101110 : keycode = 1; break;
		case 0b11101101 : keycode = 2; break;
		case 0b11101011 : keycode = 3; break;
		case 0b11100111 : keycode = 4; break;

		case 0b11011110 : keycode = 5; break;
		case 0b11011101 : keycode = 6; break;
		case 0b11011011 : keycode = 7; break;
		case 0b11010111 : keycode = 8; break;

		case 0b10111110 : keycode = 9; break;
		case 0b10111101 : keycode = 10; break;
		case 0b10111011 : keycode = 11; break;
		case 0b10110111 : keycode = 12; break;

		case 0b01111110 : keycode = 13; break;
		case 0b01111101 : keycode = 14; break;
		case 0b01111011 : keycode = 15; break;
		case 0b01110111 : keycode = 16; break;

		default: keycode = 255;
		}
	}

	return keycode;
}


uint8_t keypad_getKey(){

	uint8_t key, keycode;

	keycode = 0;

	while (keycode ==  0){
		//Check status of keypad
		key = keypad_getKeyNoBlock();
		if (key != 0) {
			//if key is pressed save which key
			keycode = key;
			//wait for the release of the key
			while (key != 0){
				key = keypad_getKeyNoBlock();
			}
		}
	}
	return keycode;
}

uint8_t keypad_getNum(uint8_t num){
	uint8_t out = 255;
	switch (num){
	case 1 : out = 1; break;
	case 2 : out = 2; break;
	case 3 : out = 3; break;
	case 5 : out = 4; break;
	case 6 : out = 5; break;
	case 7 : out = 6; break;
	case 9 : out = 7; break;
	case 10 : out = 8; break;
	case 11 : out = 9; break;
	default : out = 0; break;
	}
	return out;
}

char keypad_getChar(uint8_t num){
	char out;
	switch (num){
	case 1 : out = '1'; break;
	case 2 : out = '2'; break;
	case 3 : out = '3'; break;
	case 4 : out = 'A'; break;
	case 5 : out = '4'; break;
	case 6 : out = '5'; break;
	case 7 : out = '6'; break;
	case 8 : out = 'B'; break;
	case 9 : out = '7'; break;
	case 10 : out = '8'; break;
	case 11 : out = '9'; break;
	case 12 : out = 'C'; break;
	case 13 : out = '*'; break;
	case 15 : out = '#'; break;
	case 16 : out = 'D'; break;
	default : out = '0'; break;
	}
	return out;
}
