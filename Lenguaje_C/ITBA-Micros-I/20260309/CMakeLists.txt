# CMakeLists.txt para el proyecto de recursividad
cmake_minimum_required(VERSION 3.16)

# Nombre del proyecto
project(Recursividad LANGUAGES C)

# Estándar de C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Ejecutable
add_executable(non_recursive non_recursive_conv.c)
add_executable(recursive recursive_conv.c)

# Como compilar (recomendado con comandos CMake)
# 1) Configurar el proyecto:
#    cmake -S . -B build
#
# 2) Compilar solo el ejecutable no recursivo:
#    cmake --build build --target non_recursive --config Release
#
# 3) Compilar solo el ejecutable recursivo:
#    cmake --build build --target recursive --config Release
#
# Nota:
# - En Visual Studio/Windows, --config Release es necesario.

