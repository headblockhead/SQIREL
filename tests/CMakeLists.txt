include(CTest)
enable_testing()

include_directories(../include)

add_executable(keyboard_press_release keyboard_press_release.c ../src/squirrel_keyboard.c ../src/squirrel_quantum.c)
target_link_libraries(keyboard_press_release squirrel)
add_test(NAME keyboard_press_release COMMAND keyboard_press_release)

add_executable(keyboard_modifier_press_release keyboard_modifier_press_release.c ../src/squirrel_keyboard.c ../src/squirrel_quantum.c)
target_link_libraries(keyboard_modifier_press_release squirrel)
add_test(NAME keyboard_modifier_press_release COMMAND keyboard_modifier_press_release)

add_executable(quantum_passthrough_press_release quantum_passthrough_press_release.c ../src/squirrel_keyboard.c ../src/squirrel_quantum.c)
target_link_libraries(quantum_passthrough_press_release squirrel)
add_test(NAME quantum_passthrough_press_release COMMAND quantum_passthrough_press_release)
