cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(ej7 LANGUAGES C)

# Estándar de C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Ejecutable (main + librería)
add_executable(ej7 ej7_main.c ej7.c)

