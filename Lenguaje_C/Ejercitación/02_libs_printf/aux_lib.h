/*****************************************************************************
 * aux_lib.h  -  Cabecera compartida por my_printf.c y keyboard_input.c
 *---------------------------------------------------------------------------*
 * Concepto: un .h declara la INTERFAZ (que ofrece la libreria), un .c
 * implementa el COMPORTAMIENTO. Quien usa la libreria solo necesita el .h.
 *
 * Esta cabecera centraliza:
 *   - Inclusiones estandar comunes (stdio, stdint, stdlib).
 *   - Macros de tamano de buffer (sirven como constantes globales).
 *   - Prototipos de funciones publicas implementadas en aux_lib.c.
 ****************************************************************************/

// Inclusion de Librerias
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Macros ("constantes" definidas en preprocesado)
#define _Buff_Size      ((uint8_t) 128) // Tamano del buffer de teclado
#define _Cant_Numeros   ((uint8_t) 5)   // Cantidad de numeros a ingresar

#define _NOK_           ((uint8_t) 0)   // Tecla no valida
#define _OK_            ((uint8_t) 1)   // Tecla valida

// Prototipos de funciones publicas (definidas en aux_lib.c / my_printf.c)
int  validate_digit(char digit);     // _OK_ si el caracter es un digito 0..9
int  char_to_int(char digit);        // convierte '0'..'9' -> 0..9
void my_lib_printf(char *my_string, int cant);  // imprime char por char