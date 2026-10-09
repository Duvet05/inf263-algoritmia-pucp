cmake_minimum_required(VERSION 4.0)
project(20190213_EX1_P4)

set(CMAKE_CXX_STANDARD 20)

add_executable(20190213_EX1_P4 main.cpp
        FuncionesAuxiliares.cpp
        FuncionesAuxiliares.h
        BibliotecaPila/funcionesPila.cpp
        BibliotecaPila/funcionesPila.h)
