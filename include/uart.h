#include "stm32f4xx.h"
#include <stdint.h>

#ifndef UART_H
#define UART_H

void uart_init();
int puts(const char *s);
#endif