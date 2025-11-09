#ifndef SYSTICK_H
#define SYSTICK_H

#include "stm32f4xx.h"

void systick_msec_delay(uint32_t delay);
void systick_sec_delay(uint32_t delay);

#endif