cmake_minimum_required(VERSION 3.12)

project(sqirel VERSION 0.0.1 DESCRIPTION "Simple QMK Inspired Runtime Editable Library")

# Create files for CCLS
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Generate an executable
add_library(sqirel STATIC
        src/sqirel.c
        src/sqirel_quantum.c
        src/sqirel_keys.c
        )

target_include_directories(sqirel PRIVATE include)

set_target_properties(sqirel PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(sqirel PROPERTIES PUBLIC_HEADER include/squirel.h)
