#include "uart.h"
#include "systick.h"

#define GPIOAEN (1U << 0)
#define UART2EN (1U << 17)

#define DBG_UART_BAUDRATE 115200
#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define CR1_TE (1U << 3)
#define CR1_UE (1U << 13)
#define SR_TXE (1U << 7)

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
static void uart_write(int ch);

int __io_putchar(int ch)
{
    uart_write(ch);
    return ch;
}

void uart_init(void)
{
    // Enable clock access to GPIOA
    RCC->AHB1ENR |= GPIOAEN;

    // Set the mode of PA2 to alternate function
    // Alternate function is 1 0
    // PA 2 is bits 5 4
    GPIOA->MODER &= ~(1U << 4);
    GPIOA->MODER |= (1U << 5);

    // Set alternate function
    // Alternate function to set is AF7
    GPIOA->AFR[0] |= (1u << 8);
    GPIOA->AFR[0] |= (1u << 9);
    GPIOA->AFR[0] |= (1u << 10);
    GPIOA->AFR[0] &= ~(1u << 11);

    // Set alternate function

    // Enale clock access to USART2
    RCC->APB1ENR |= UART2EN;

    // Configure the UART baud rate
    uart_set_baudrate(APB1_CLK, DBG_UART_BAUDRATE);

    // Configure transmitter direction
    USART2->CR1 = CR1_TE;

    // Enable UART Module
    USART2->CR1 |= CR1_UE;

    // Clear the TC bit before starting
    USART2->SR &= ~(SR_TXE);
}

static void uart_write(int ch)
{
    // Make sure transmit data register is empty
    while (!(USART2->SR & SR_TXE))
    {
    }

    // Write data to the data register
    USART2->DR = (ch & 0xFF);
}

static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate)
{
    return ((periph_clk + (baudrate / 2U)) / baudrate);
}

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate)
{
    USART2->BRR = compute_uart_bd(periph_clk, baudrate);
}

// puts implementation for printf
int puts(const char *s)
{
    while (*s != '\0')
    {
        __io_putchar((uint8_t)*s);
        // Handle new line reset
        if (*s == '\n')
        {
            __io_putchar('\r');
        }
        s++;
    }
    return 0;
}