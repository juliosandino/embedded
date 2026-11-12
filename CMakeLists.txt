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
add_compile_definitions(
  DEBUG
  NUCLEO_F411RE
  STM32
  STM32F4
  STM32F411RETx
  STM32F411x
)

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
target_link_options(
  app
  PRIVATE -nostdlib -T ${LINKER_SCRIPT} -Wl,-Map=${MAP_FILE}
)

# Ensure the C standard is set for the target
target_compile_options(app PRIVATE -std=gnu11)

# ---------------------------------------------------------------------------
# Documentation (Doxygen)
# ---------------------------------------------------------------------------
# Generates API docs for src/ and include/ into build/docs/html.
# Requires the host `doxygen` binary; the target is skipped if it is not found.
find_package(Doxygen)
if(DOXYGEN_FOUND)
  # Doxygen Awesome CSS theme, downloaded at configure time.
  include(FetchContent)
  FetchContent_Declare(
    doxygen-awesome-css
    URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/tags/v2.5.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  FetchContent_MakeAvailable(doxygen-awesome-css)
  FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)

  set(DOXYGEN_PROJECT_NAME "app")
  set(DOXYGEN_PROJECT_BRIEF "Bare-metal STM32F411 learning project")
  set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs")
  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_GENERATE_LATEX NO)
  set(DOXYGEN_RECURSIVE YES)
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_EXTRACT_STATIC YES)
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md")
  set(DOXYGEN_EXCLUDE_PATTERNS
    "*/chip_headers/*"
    "*/build/*"
  )
  set(DOXYGEN_PREDEFINED
    DEBUG
    NUCLEO_F411RE
    STM32
    STM32F4
    STM32F411RETx
    STM32F411xE
  )

  # Doxygen Awesome theme: base layout with the treeview sidebar.
  set(DOXYGEN_GENERATE_TREEVIEW YES)
  set(DOXYGEN_DISABLE_INDEX NO)
  set(DOXYGEN_FULL_SIDEBAR NO)
  set(DOXYGEN_HTML_COLORSTYLE LIGHT)
  set(DOXYGEN_HTML_EXTRA_STYLESHEET "${AWESOME_CSS_DIR}/doxygen-awesome.css")

  doxygen_add_docs(docs
    "${CMAKE_SOURCE_DIR}/README.md"
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/include"
    COMMENT "Generating API docs with Doxygen"
  )
else()
  message(STATUS "Doxygen not installed - the 'docs' target is unavailable")
endif()
