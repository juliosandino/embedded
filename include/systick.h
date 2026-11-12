/**
 * @file systick.h
 * @brief Blocking delays backed by the Cortex-M4 SysTick timer.
 */

#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

/**
 * @brief Block for the given number of milliseconds.
 * @param delay Number of milliseconds to wait.
 * @note Polls the SysTick COUNTFLAG; blocks with interrupts enabled.
 */
void systick_msec_delay(uint32_t delay);

/**
 * @brief Block for the given number of seconds.
 * @param delay Number of seconds to wait.
 * @note Polls the SysTick COUNTFLAG; blocks with interrupts enabled.
 */
void systick_sec_delay(uint32_t delay);

#endif
