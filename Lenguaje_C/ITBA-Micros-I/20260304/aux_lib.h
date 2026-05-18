// Inclusión de Librerias
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Macros
#define _Buff_Size ((uint8_t) 128) // Tamaño del buffer de teclado
#define _Cant_Numeros ((uint8_t) 5) // Cantidad de números a ingresar

#define _NOK_ ((uint8_t) 0) // Tecla no válida
#define _OK_ ((uint8_t) 1) // Tecla válida

// Prototipos de funciones
int validate_digit(char digit);
int char_to_int(char digit);
void my_lib_printf(char *my_string, int cant);