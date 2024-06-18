cmake_minimum_required(VERSION 3.12)

project(squirrel VERSION 0.0.1 DESCRIPTION "Simplified, runtime-configurable QMK as a library")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Debug/Development build enabled")
        # Create files for CCLS
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
        add_compile_options(-Og) # Enable debug optimizations
else()
       add_compile_options(-Os) # Enable size optimizations
endif()

# Generate a static library archive.
add_library(squirrel STATIC
        src/squirrel.c
        src/squirrel_quantum.c
        src/squirrel_keys.c
        src/squirrel_constructors.c
        )

target_include_directories(squirrel PRIVATE include)

set_target_properties(squirrel PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(squirrel PROPERTIES PUBLIC_HEADER include/squirel.h)

# Enable testing
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
        message(STATUS "Testing enabled")
        add_subdirectory(tests)
endif()

