cmake_minimum_required(VERSION 3.12)

project(squirrel VERSION 0.0.1 DESCRIPTION "Simplified, runtime-configurable QMK as a library")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Debug/Development build enabled")
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Autocomplete support
        add_compile_options(-Og) # Enable debug optimizations
elseif(CMAKE_BUILD_TYPE STREQUAL "Testing")
        message(STATUS "Testing enabled")
        include(CTest)
        enable_testing()

        include_directories(include)

        list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")
        if(CMAKE_COMPILER_IS_GNUCXX)
            include(CodeCoverage)
            APPEND_COVERAGE_COMPILER_FLAGS()
            setup_target_for_coverage_gcovr_html(squirrel squirrel_test coverage)
            list(APPEND GCOVR_EXCLUDES "tests/")
        endif()

        add_executable(keyboard_press_release tests/keyboard_press_release.c)
        target_link_libraries(keyboard_press_release squirrel)
        add_test(NAME keyboard_press_release COMMAND keyboard_press_release)

        add_executable(keyboard_modifier_press_release tests/keyboard_modifier_press_release.c)
        target_link_libraries(keyboard_modifier_press_release squirrel)
        add_test(NAME keyboard_modifier_press_release COMMAND keyboard_modifier_press_release)

        add_executable(quantum_passthrough_press_release tests/quantum_passthrough_press_release.c)
        target_link_libraries(quantum_passthrough_press_release squirrel)
        add_test(NAME quantum_passthrough_press_release COMMAND quantum_passthrough_press_release)

        add_executable(keyboard_get_keycodes tests/keyboard_get_keycodes.c)
        target_link_libraries(keyboard_get_keycodes squirrel)
        add_test(NAME keyboard_get_keycodes COMMAND keyboard_get_keycodes)

        add_executable(consumer_press_release tests/consumer_press_release.c)
        target_link_libraries(consumer_press_release squirrel)
        add_test(NAME consumer_press_release COMMAND consumer_press_release)

        add_executable(key tests/key.c)
        target_link_libraries(key squirrel)
        add_test(NAME key COMMAND key)

        add_executable(layer_press_release tests/layer_press_release.c)
        target_link_libraries(layer_press_release squirrel)
        add_test(NAME layer_press_release COMMAND layer_press_release)

        add_executable(consumer_activate_deactivate_get_consumer_code tests/consumer_activate_deactivate_get_consumer_code.c)
        target_link_libraries(consumer_activate_deactivate_get_consumer_code squirrel)
        add_test(NAME consumer_activate_deactivate_get_consumer_code COMMAND consumer_activate_deactivate_get_consumer_code)

        add_executable(keyboard_activate_deactivate_keycode tests/keyboard_activate_deactivate_keycode.c)
        target_link_libraries(keyboard_activate_deactivate_keycode squirrel)
        add_test(NAME keyboard_activate_deactivate_keycode COMMAND keyboard_activate_deactivate_keycode)

        add_executable(keyboard_activate_deactivate_get_modifier tests/keyboard_activate_deactivate_get_modifier.c)
        target_link_libraries(keyboard_activate_deactivate_get_modifier squirrel)
        add_test(NAME keyboard_activate_deactivate_get_modifier COMMAND keyboard_activate_deactivate_get_modifier)
else()
       add_compile_options(-Os) # Enable size optimizations
endif()

# Generate a static library archive.
add_library(squirrel STATIC
        src/squirrel.c
        src/squirrel_quantum.c
        src/squirrel_keyboard.c
        src/squirrel_key.c
        src/squirrel_consumer.c
        src/squirrel_init.c
        )

target_include_directories(squirrel PRIVATE include)

set_target_properties(squirrel PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(squirrel PROPERTIES PUBLIC_HEADER include/squirrel.h)
