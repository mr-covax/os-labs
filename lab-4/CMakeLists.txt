cmake_minimum_required(VERSION 3.10)

project("OS Lab 4" VERSION 1.0)

set(CMAKE_C_STANDARD 17)

add_library(first SHARED libs/first.c)
target_link_libraries(first m)

add_library(second SHARED libs/second.c)
target_link_libraries(second m)

add_executable(main src/main.c)
target_link_libraries(main dl m)

set_target_properties(first second PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
