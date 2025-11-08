#include "gpio.h"

// LED
#define GPIOAEN     (1U<<0)
#define LED_PIN     (1U<<5)
#define LED_BS5     (1U<<5)     /* Bit Set Pin 5*/
#define LED_BR5     (1U<<21)    /* Bit Reset Pin 5*/

// BUTTON
#define GPIOCEN     (1U<<2)
#define BTN_PIN     (1U<<13)

/* ONBOARD LED FUNCTIONALITY */

void led_init(void)
{
    /* Enable Clock Access to PORT A */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA5 mode as output mode */
    GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);
}

void led_on(void)
{
    GPIOA->BSRR |= LED_BS5;
}

void led_off(void)
{
    GPIOA->BSRR |= LED_BR5;
}

void led_toggle(void)
{
    GPIOA->ODR ^= LED_PIN;
}

// BUTTON INIT
// Button maps to PC13 (Port C Pin 13)
void button_init(void)
{
    /* Enable Clock Access for PORT C */
    RCC->AHB1ENR |= GPIOCEN;

    /* Set PC13 mode as input mode */
    GPIOC->MODER &= (0U << 26);
	GPIOC->MODER &= (0U << 27);
}

// Note: BTN is active low
//       So if it's pressed, then it is 0 (low)
bool get_button_state(void)
{
    if (GPIOC->IDR & BTN_PIN) {
        return false;
    }

    return true;
}