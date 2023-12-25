cmake_minimum_required(VERSION 3.12)

project(squirrel VERSION 0.0.1 DESCRIPTION "Simple QMK Inspired Runtime Editable Library")

# Create files for CCLS
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Generate an executable
add_library(squirrel STATIC
        src/squirrel.c
        src/squirrel_quantum.c
        src/squirrel_keys.c
        )

target_include_directories(squirrel PRIVATE include)

set_target_properties(squirrel PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(squirrel PROPERTIES PUBLIC_HEADER include/squirel.h)
