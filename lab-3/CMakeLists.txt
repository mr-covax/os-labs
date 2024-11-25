cmake_minimum_required(VERSION 3.10)

project("OS Lab 3" VERSION 1.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED on)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -O0")

include_directories(include)

add_executable(Calc src/calc.c)
add_executable(Main src/main.c)