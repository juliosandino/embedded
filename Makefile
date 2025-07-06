# Simple Makefile to build all .c files into a final ELF application

# Compiler and flags
CC := arm-none-eabi-gcc
CFLAGS := -c -g -mcpu=cortex-m4 -mthumb -Wall
LDFLAGS := -nostdlib -T stm32_ls.ld *.o

# Source and object files
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

# Output ELF file
TARGET := app.elf

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)