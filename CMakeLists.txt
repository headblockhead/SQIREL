cmake_minimum_required(VERSION 3.12)

project(squirrel)

# Override this in your build of the library! Otherwise, it will default to 1 key.
add_compile_definitions(SQUIRREL_KEYCOUNT=1)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
        add_compile_options(-Og)
else()
       add_compile_options(-Os)
endif()

# Generate a static library archive.
add_library(squirrel STATIC
        src/squirrel.c
        src/squirrel_quantum.c
        src/squirrel_keyboard.c
        src/squirrel_key.c
        src/squirrel_consumer.c
        src/squirrel_init.c
        src/squirrel_keymap.c
        src/squirrel_split.c
        )

target_include_directories(squirrel PUBLIC include)
set_target_properties(squirrel PROPERTIES PUBLIC_HEADER include/squirrel.h)

if (BUILD_TESTING)
        add_subdirectory(tests)
endif()
