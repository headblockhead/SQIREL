cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_keyboard C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Default to Release build
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# If debug build, enable debug generation.
set(CMAKE_CXX_FLAGS_DEBUG "-g")
# If release build, enable optimizations.
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Create files for CCLS
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Require Pico SDK version 1.3.0
if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

# Add compiler flags
add_compile_options(-Wall # Enable all warnings
        -Wextra # Enable extra warnings
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        )

# Generate an executable
add_executable(pico_keyboard # Name of executable and target.
        ${CMAKE_CURRENT_LIST_DIR}/src/main.c # Entrypoint
        )

# Add USB configuration files
target_sources(pico_keyboard PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/tinyusb/usb_descriptors.c # Use USB descriptors in target and dependencies.
        )

target_include_directories(pico_keyboard PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/tinyusb) # Include tinyusb headers in target and dependencies.

# Pull in common dependencies
target_link_libraries(pico_keyboard pico_stdlib pico_unique_id tinyusb_device tinyusb_board pico_multicore hardware_gpio)

# Create map/bin/hex file etc.
pico_add_extra_outputs(pico_keyboard)
