# testing binary
add_executable(test test.c)
target_link_libraries(test PRIVATE squirrel)

enable_testing()

add_test(NAME test COMMAND $<TARGET_FILE:test>)
