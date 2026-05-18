/************************************************************************************************
 * Ejercicio 6 - 2025                                                                           *
 * Escriba una librería que permita trabajar con vectores reales en R3, la misma debe permitir  *
 * realizar las siguientes operaciones:                                                         *
 *      - Norma de 1 vector                                                                     *
 *      - Suma entre 2 vectores                                                                 *
 *      - Resta entre 2 vectores                                                                *
 *      - Producto interno entre 2 vectores                                                     *
 *      - Producto externo entre 2 vectores                                                     *
 * La implementación debe realizarse mediante el uso de tipos de dato struct y                  *
 * punteros a función.                                                                          *
 ************************************************************************************************/

// Includes
#include "ej6.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Función principal
int main (void){
    // Instancio objetos
    vector_t v1=crear_vector(1,-2,1.5);
    vector_t v2=crear_vector(-1.3,0.5,-3);
    vector_t v3=crear_vector(0,0,0);

    // Imprimo los vectores
    printf("Vector 1: ");
    v1.imprimir(v1);
    printf("Vector 2: ");
    v2.imprimir(v2);

    // Realizo las operaciones
    printf("Suma de los vectores: ");
    v3 = v1.suma(v1,v2);
    v3.imprimir(v3);

    printf("Resta de los vectores: ");
    v3 = v3.resta(v1,v2);
    v3.imprimir(v3);

    printf("Producto interno de los vectores: %.2f\n", v1.producto_interno(v1,v2));

    printf("Producto externo de los vectores: ");
    v3 = v3.producto_externo(v1,v2);
    v3.imprimir(v3);

    printf("Norma del vector 1: %.2f\n", v1.norma(v1));
    printf("Norma del vector 2: %.2f\n", v2.norma(v2));


    return 0;
}