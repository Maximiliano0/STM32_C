cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(ej5 LANGUAGES C)

# Estándar de C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Ejecutable
add_executable(ej5 ej5.c)
