/**
 * @file uart.h
 * @brief USART2 transmit-only driver used for debug output.
 */

#include "stm32f4xx.h"
#include <stdint.h>

#ifndef UART_H
#define UART_H

/**
 * @brief Initialize USART2 on PA2 at 115200 baud, 8N1.
 */
void uart_init();

/**
 * @brief Write a NUL-terminated string to USART2.
 *
 * Newline characters are preceded by a carriage return so output renders
 * correctly in serial terminals. Provided so printf output can be retargeted.
 *
 * @param s Pointer to the NUL-terminated string to send.
 * @return Always returns 0.
 */
int puts(const char *s);
#endif