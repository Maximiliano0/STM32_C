/*****************************************************************************
 * upper.c  -  Conversion a mayuscula y aritmetica con caracteres
 *---------------------------------------------------------------------------*
 * Objetivo didactico:
 *   1) Definir una funcion que recibe un char y devuelve un char.
 *   2) Mostrar que los chars en C son numeros (codigos ASCII): se les puede
 *      restar, sumar y comparar como enteros.
 *   3) Comparar dos formas equivalentes de pasar de minuscula a mayuscula:
 *        a) Restar el literal 32  -> mas rapido de escribir pero "magico".
 *        b) Restar ('a' - 'A')    -> autoexplicativo y portable.
 *      Ambas dan el mismo resultado porque, en ASCII, 'a' = 'A' + 32.
 *
 * Compilar:  gcc upper.c -o upper
 ****************************************************************************/
#include <stdio.h>

char to_upper(char c);

int main(void)
{
    char in = 'l';

    char ucase = to_upper(in);
    printf("Uppercase: %c\n", ucase);

    return 0;
}

char to_upper(char c)
{
    char upper;

    // Forma a: numero "magico". Funciona pero hay que recordar de donde sale.
    upper = c - 32;
    // Forma b: equivalente pero autoexplicativa.
    //   Si c es 'a', entonces 'a' - ('a' - 'A') = 'A'.
    upper = c - ('a' - 'A');

    return(upper);
}