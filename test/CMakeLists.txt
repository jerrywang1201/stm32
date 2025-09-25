cmake_minimum_required(VERSION 3.20)
project(unit_tests C)

# Unity can be added as a submodule: tests/unity
add_library(unity STATIC unity/src/unity.c)
target_include_directories(unity PUBLIC unity/src)

# Put the pure C logic you want to test under modules/ or src/ to avoid direct register dependencies
add_executable(test_ringbuf test_ringbuf.c
    ../modules/uart2/ringbuf.c)   # Example: do you have a ring buffer?
target_include_directories(test_ringbuf PRIVATE
    ../modules/uart2
    unity/src)
target_link_libraries(test_ringbuf unity)

enable_testing()
add_test(NAME ringbuf COMMAND test_ringbuf)
