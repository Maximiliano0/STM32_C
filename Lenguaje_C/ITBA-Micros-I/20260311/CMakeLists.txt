# Standar CMKAE C
cmake_minimum_required(VERSION 3.10)

# Proyecto
project(ordenamiento_prj C)

# Standar C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Ejecutable
add_executable(ordenamiento bubble_sort.c)
add_executable(circular circular_buffer.c)