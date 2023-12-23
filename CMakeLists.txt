cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_keyboard C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Create files for CCLS
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Require Pico SDK version 1.3.0
if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        )

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

add_executable(pico_keyboard
        ${CMAKE_CURRENT_LIST_DIR}/src/main.c
        )

# Add USB libraries
target_sources(pico_keyboard PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/usb_descriptors.c
        )

target_include_directories(pico_keyboard PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src)

# Pull in common dependencies
target_link_libraries(pico_keyboard PUBLIC pico_stdlib pico_unique_id tinyusb_device tinyusb_board pico_multicore hardware_gpio)

# Create map/bin/hex file etc.
pico_add_extra_outputs(pico_keyboard)
