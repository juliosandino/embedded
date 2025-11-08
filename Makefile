# Simple Makefile to build all .c files into a final ELF application

# Output ELF file
TARGET := app.elf
MAP_FILE := app.map
CMSIS_DEVICE_INCLUDE_DIR := chip_headers/CMSIS/Device/ST/STM32F4xx/Include
CMSIS_STANDARD_INCLUDE_DIR := chip_headers/CMSIS/Include
DEFINE := -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE

# Compiler and flags
CC := arm-none-eabi-gcc
CFLAGS := -c -g -mcpu=cortex-m4 -mthumb -Wall -std=gnu11 -I$(CMSIS_DEVICE_INCLUDE_DIR) -I$(CMSIS_STANDARD_INCLUDE_DIR) -Iinclude $(DEFINE)
LDFLAGS := -nostdlib -T stm32_ls.ld -Wl,-Map=$(MAP_FILE)

# Source and object files
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))

# Output ELF file
TARGET := app.elf

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

load:
	openocd -f board/st_nucleo_f4.cfg