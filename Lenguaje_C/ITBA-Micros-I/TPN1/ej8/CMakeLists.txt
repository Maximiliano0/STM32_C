cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(ej8 LANGUAGES C)

# Estándar de C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Ejecutable
add_executable(ej8 ej8.c)
