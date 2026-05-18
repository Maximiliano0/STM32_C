// Librerías
#include "aux_lib.h"

// Función para validar un dígito
int validate_digit(char digit){
    
    // Verifico si es un número
    if(digit<='9' && digit>='0') return _OK_;

    else return _NOK_;
}

// Función para convertir un caracter a entero
int char_to_int(char digit){
    return ((int) (digit - '0'));
}