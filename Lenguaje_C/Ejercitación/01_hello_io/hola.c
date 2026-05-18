/*****************************************************************************
 * hola.c  -  Primer programa en C
 *---------------------------------------------------------------------------*
 * Objetivo didactico:
 *   1) Compilar y ejecutar un programa C minimo (printf + return).
 *   2) Mostrar la diferencia entre comentarios de una linea (//) y de bloque (slash-star ... star-slash).
 *   3) Explorar el operador sizeof aplicado a tipos basicos (int, float,
 *      double, char) y a los tipos de ancho fijo de <stdint.h> (int16_t,
 *      int32_t, uint8_t). Esto introduce el concepto de "el tamano de un
 *      tipo depende del compilador y arquitectura", clave en embebidos.
 *   4) Diferenciar entre imprimir un caracter como char (%c) y como entero
 *      (%d): los caracteres son numeros (codigos ASCII).
 *
 * Compilar:  gcc hola.c -o hola
 * Ejecutar:  ./hola
 ****************************************************************************/

// printf()
#include <stdio.h>
// Tipos de ancho fijo (int8_t, uint16_t, ...): garantizan el tamano sin importar la plataforma
#include <stdint.h>

int main(void) {

    // Imprime "Hola, mundo!" en la consola (sin salto de linea final)
    /* Comentario de bloque:
       puede ocupar varias lineas. Util para describir un algoritmo entero. */
    printf("Hola, mundo!");

    /*      SIZEOF      */

    // Sizeof 
    printf("\n%d\n", sizeof(int));
    printf("%d\n", sizeof(int16_t));
    printf("%d\n", sizeof(int32_t));
    
    // Flotante
    printf("%d\n", sizeof(float));
    printf("%d\n", sizeof(double));

    // CHAR
    printf("%d\n", sizeof(char));
    printf("%d\n", sizeof(uint8_t));

    printf("%d\n", '0');
    printf("%c\n", '0');
    
    printf("%d\n", 'A');
    printf("%c\n", 'A');

    return(0);
}