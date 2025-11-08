#ifndef GPIO_H
#define GPIO_H

#include "stm32f4xx.h"
#include "stdbool.h"

// led
void led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);

// button
void button_init(void);
bool get_button_state(void);

#endif