/*
 * rotary.h
 *
 *  Created on: Feb 3, 2020
 *      Author: navinj
 * Rotary encoder header file, including memory addresses
 * and initialization functions
 */

#ifndef ROTARY_H_
#define ROTARY_H_

#include <inttypes.h>

/*
 * Memory addresses
 */
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define RCC_APB2ENR (volatile uint32_t*) 0x40023844
#define GPIOAEN 0
#define SYSCFGEN 1<<14

#define GPIOA_MODER (volatile uint32_t*) 0x40020000
#define GPIOA_PUPDR (volatile uint32_t*) 0x4002000C
#define GPIOA_IDR (volatile uint32_t*) 0x40020010
#define GPIOA_ODR (volatile uint32_t*) 0x40020014
#define GPIOA_BSRR (volatile uint32_t*) 0x40020018

#define SYSCFG_EXTICR1 (volatile uint32_t*) 0x40013808
#define SYSCFG_EXTICR4 (volatile uint32_t*) 0x40013814

#define EXTI_IMR (volatile uint32_t*) 0x40013C00
#define EXTI_FTSR (volatile uint32_t*) 0x40013C0C
#define EXTI_PR (volatile uint32_t*) 0x40013C14

#define NVIC_ISER0 (volatile uint32_t*) 0xE000E100
#define NVIC_ISER1 (volatile uint32_t*) 0xE000E104
#define NVIC_ICER0 (volatile uint32_t*) 0xE000E080
#define NVIC_ICER1 (volatile uint32_t*) 0xE000E084
#define NVIC_ICPR0 (volatile uint32_t*) 0xE000E180

/*
 * Initializes the rotary encoder to read
 * input with interrupts
 *
 * Still need to turn on interrupts in NVIC with other function call
 */
void rotary_init();

/*
 * Enables the interrupts in NVIC
 */
void rotary_enable();

/*
 * Disables the interrupts in NVIC
 */
void rotary_disable();

#endif /* ROTARY_H_ */
