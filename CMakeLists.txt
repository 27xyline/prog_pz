cmake_minimum_required(VERSION 3.16)
project(dynamic_array_part1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(dynamic_array
    src/DynamicArray.cpp
    src/main.cpp
)

target_include_directories(dynamic_array PRIVATE include)
target_compile_options(dynamic_array PRIVATE -Wall -Wextra -Wpedantic)
