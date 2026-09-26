cmake_minimum_required(VERSION 3.16)

project(LAB1_2025_02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(pregunta1 pregunta1.cpp)
add_executable(pregunta2 pregunta2.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(pregunta1 PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(pregunta2 PRIVATE -Wall -Wextra -Wpedantic)
endif()
