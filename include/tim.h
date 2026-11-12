/**
 * @file tim.h
 * @brief Timer 2 (TIM2) based 1 Hz timebase.
 */

#include "stm32f4xx.h"
#ifndef TIM_H
#define TIM_H

#define SR_UIF (1U << 0)

/**
 * @brief Configure TIM2 to overflow once per second (1 Hz).
 *
 * Sets the prescaler and auto-reload value so the update flag (SR_UIF) is set
 * every second. Poll SR_UIF after calling this, or enable the TIM2 interrupt
 * in the NVIC if you prefer an ISR.
 */
void tim2_1hz_init(void);

#endif