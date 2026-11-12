/**
 * @file gpio.h
 * @brief Onboard LED and user button control for the STM32 Nucleo-F411RE.
 */

#ifndef GPIO_H
#define GPIO_H

#include "stm32f4xx.h"
#include "stdbool.h"

/**
 * @brief Configure the onboard LED (PA5) as a push-pull output.
 */
void led_init(void);

/**
 * @brief Turn the onboard LED on.
 */
void led_on(void);

/**
 * @brief Turn the onboard LED off.
 */
void led_off(void);

/**
 * @brief Toggle the onboard LED.
 */
void led_toggle(void);

/**
 * @brief Configure the user button (PC13) as an input.
 */
void button_init(void);

/**
 * @brief Read the current state of the user button.
 *
 * The button is active-low (it reads low when pressed).
 *
 * @return true when the button is pressed, false otherwise.
 */
bool get_button_state(void);

#endif