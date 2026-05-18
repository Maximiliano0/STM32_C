/*****************************************************************************
 * aux_lib.c  -  Implementacion de las funciones declaradas en aux_lib.h
 *---------------------------------------------------------------------------*
 * Concepto: el .c "materializa" las funciones cuya firma esta en el .h.
 * El compilador genera un objeto (aux_lib.o) que luego se enlaza con los
 * objetos de las aplicaciones que usen la libreria.
 ****************************************************************************/

// Librerias (incluye la propia cabecera para que el compilador valide
// que las firmas coinciden con los prototipos publicados)
#include "aux_lib.h"

// validate_digit:  _OK_ si `digit` es un caracter '0'..'9', _NOK_ en otro caso.
// Aprovecha que en ASCII los digitos '0'..'9' son consecutivos: 0x30..0x39.
int validate_digit(char digit){

    // Verifico si es un numero
    if(digit<='9' && digit>='0') return _OK_;

    else return _NOK_;
}

// char_to_int:  '0'..'9'  ->  0..9 numericos.
// Truco clasico: como '0' es ASCII 0x30, restar '0' da el dia decimal real.
int char_to_int(char digit){
    return ((int) (digit - '0'));
}