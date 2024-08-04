include(CTest)
enable_testing()

add_executable(test1 test1.c)
target_link_libraries(test1 squirrel)
add_test(NAME testname COMMAND test1)
