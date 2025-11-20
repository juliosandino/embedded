cmake_minimum_required(VERSION 3.13)
project(app C)

# Export compilation database for tools (clang-tidy, clangd, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Avoid try_compile creating executables (useful for cross-compiling)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

set(CMAKE_SYSTEM_NAME Generic)

# Compiler flags (from Makefile)
set(COMMON_C_FLAGS "-g -mcpu=cortex-m4 -mthumb -Wall -std=gnu11")
set(CMAKE_C_FLAGS "${COMMON_C_FLAGS} ${CMAKE_C_FLAGS}")

# Preprocessor defines (from Makefile)
add_compile_definitions(DEBUG NUCLEO_F411RE STM32 STM32F4 STM32F411RETx STM32F411xE)

# Include directories
include_directories(
  ${CMAKE_SOURCE_DIR}/chip_headers/CMSIS/Device/ST/STM32F4xx/Include
  ${CMAKE_SOURCE_DIR}/chip_headers/CMSIS/Include
  ${CMAKE_SOURCE_DIR}/include
)

# Source files
file(GLOB_RECURSE SRC_FILES
  ${CMAKE_SOURCE_DIR}/src/*.c
)

# Target executable. We'll set the suffix to .elf to match your Makefile output
add_executable(app ${SRC_FILES})
set_target_properties(app PROPERTIES
  OUTPUT_NAME "app"
  PREFIX ""
  SUFFIX ".elf"
)

# Linker script and map file (from Makefile)
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/stm32_ls.ld")
set(MAP_FILE "${CMAKE_SOURCE_DIR}/build/app.map")

# Linker flags: -nostdlib, use custom linker script, and emit map file
target_link_options(app PRIVATE -nostdlib -T ${LINKER_SCRIPT} -Wl,-Map=${MAP_FILE})

# Ensure the C standard is set for the target
target_compile_options(app PRIVATE -std=gnu11)
