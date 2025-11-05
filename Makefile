# Simple Makefile to build all .c files into a final ELF application

# Output ELF file
TARGET := app.elf
MAP_FILE := app.map

# Compiler and flags
CC := arm-none-eabi-gcc
CFLAGS := -c -g -mcpu=cortex-m4 -mthumb -Wall -std=gnu11
LDFLAGS := -nostdlib -T stm32_ls.ld -Wl,-Map=$(MAP_FILE)

# Source and object files
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

# Output ELF file
TARGET := app.elf

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

load:
	openocd -f board/st_nucleo_f4.cfg