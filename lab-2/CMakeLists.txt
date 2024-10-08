cmake_minimum_required(VERSION 3.10)
project("OS Lab 2" VERSION 0.1)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED on)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(main src/main.c src/experiment.c)