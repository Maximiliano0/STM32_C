cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(ej6 LANGUAGES C)

# Estándar de C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Ejecutable (main + librería)
add_executable(ej6 ej6_main.c ej6.c)
