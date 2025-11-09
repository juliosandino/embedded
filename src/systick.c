#include "systick.h"

#define CTRL_ENABLE (1U << 0)
#define CTRL_DISABLE (0U << 0)
#define CTRL_CLCKSRC (1U << 2)
#define CTRL_COUNTFLAG (1U << 16)

/* By default, the frequency of the mcu is 16 Mhz */
// NOTE: It appears to be actually running a 2 Mhz from experimentation
#define ONE_MSEC_LOAD 2000
#define ONE_SEC_LOAD ONE_MSEC_LOAD * 1000

// Helper functions
static void systick_delay_helper(uint32_t load, uint32_t delay);

void systick_msec_delay(uint32_t delay)
{
    systick_delay_helper(ONE_MSEC_LOAD, delay);
}

void systick_sec_delay(uint32_t delay)
{
    systick_delay_helper(ONE_SEC_LOAD, delay);
}

static void systick_delay_helper(uint32_t load, uint32_t delay)
{
    // Load number into the systick load register
    SysTick->LOAD = load - 1;

    // Clear the current value register
    SysTick->VAL = 0;

    // Select internal clock source
    SysTick->CTRL = CTRL_CLCKSRC;

    // Enable the clock
    SysTick->CTRL = CTRL_ENABLE;

    for (uint32_t i = 0; i < delay; i++)
    {
        while ((SysTick->CTRL & CTRL_COUNTFLAG) == 0)
        {
        }
    }

    // Disable the clock
    SysTick->CTRL = CTRL_DISABLE;
}