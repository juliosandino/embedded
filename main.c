/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

// 1: Define base address for peripherals
#define PERIPH_BASE			(0x40000000UL)
// 2: Offset for AHB1 peripheral bus
#define AHB1PERIPH_OFFSET	(0x00020000UL)
// 3: Base address for AHB1 peripherals
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET)
// 4: Offset for GPIOA
#define GPIOA_OFFSET		(0x0UL)
// 5: Base address for GPIOA
#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET)
// 6: Offset for RCC
#define RCC_OFFSET			(0x3800UL)
// 7: Base address for RCC
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)
// 8: Offset for AHB1EN register
#define AHB1EN_R_OFFSET		(0x30UL)
// 9: Address of AHB1EN register
#define RCC_AHB1EN_R 	(*(volatile unsigned int*) (RCC_BASE + AHB1EN_R_OFFSET))
// 10: Offset for mode register
#define MODE_R_OFFSET		(0x00UL)
// 11: Address of GPIOA mode register
#define GPIOA_MODE_R 	(*(volatile unsigned int*) (GPIOA_BASE + MODE_R_OFFSET))
// 12: Offset for output data register
#define OD_R_OFFSET			(0x14UL)
// 13: Address of GPIOA output data register
#define GPIOA_OD_R		(*(volatile unsigned int*) (GPIOA_BASE + OD_R_OFFSET))
// 14: Bit mask for enabling GPIOIA (bit 0)
#define GPIOAEN			(1U << 0)
// 15: Bit mask for GPIOA pin 5
#define PIN5			(1U << 5)
// 16: Alias for PIN5 representing LED pin
#define LED_PIN			PIN5

int main(void)
{
	// Enable the clock access for GPIOA
	RCC_AHB1EN_R |= GPIOAEN;

	// Configure pin PA5 as output pin
	// set bit 10 as 1
	// set bit 11 as 0
	GPIOA_MODE_R |= (1U << 10);
	GPIOA_MODE_R &= ~(1U << 11);

	while (1) {
		// set output high for PA5
		// Using XOR operator to toggle off and on, and make it blink.
		GPIOA_OD_R ^= LED_PIN;
		
		for (int i = 0; i < 2000000 ; i++) {
			;
		}
	}
}
