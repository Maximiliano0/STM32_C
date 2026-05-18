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
#include <math.h>
#include <stdio.h>

// Constructor
vector_t crear_vector(float x, float y, float z)
{
    vector_t v;

    // Asignacion de variables de instancia
    v.x = x;
    v.y = y;
    v.z = z;
    
    // Asignacion de métodos
    v.suma = fsuma;
    v.resta = fresta;
    v.producto_externo = fproducto_externo;
    v.producto_interno = fproducto_interno;
    v.norma = fnorma;
    v.imprimir = fimprimir;
    v.cargar = fcargar;
    
    return (v);
}

// Funciones de métodos publicos
vector_t fsuma(vector_t v1, vector_t v2)
{
    vector_t v=crear_vector(0,0,0);

    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;
    
    return (v);
}

vector_t fresta(vector_t v1, vector_t v2)
{
    vector_t v=crear_vector(0,0,0);

    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;
    
    return (v);
}

vector_t fproducto_externo(vector_t v1, vector_t v2)
{
    vector_t v=crear_vector(0,0,0);

    v.x = v1.y*v2.z - v1.z*v2.y;
    v.y = v1.z*v2.x - v1.x*v2.z;
    v.z = v1.x*v2.y - v1.y*v2.x;
    
    return (v);
}

float fproducto_interno(vector_t v1, vector_t v2)
{
    return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

float fnorma(vector_t v)
{
    return (sqrt(v.x*v.x + v.y*v.y + v.z*v.z));
}

void fimprimir(vector_t v)
{
    printf("(%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
}

vector_t fcargar(float x, float y, float z)
{
    vector_t v=crear_vector(0,0,0);
    
    v.x = x;
    v.y = y;
    v.z = z;
    
    return (v);
}