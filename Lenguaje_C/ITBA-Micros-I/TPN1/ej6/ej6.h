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

// Include guard
#ifndef EJ6_H
#define EJ6_H

// Definición del objeto vector
typedef struct vector{
    // Variables de instancia
    float x;
    float y;
    float z;
    // Metodos
    struct vector (*suma)(struct vector v1, struct vector v2);
    struct vector (*resta)(struct vector v1, struct vector v2);
    struct vector (*producto_externo)(struct vector v1, struct vector v2);
    float (*producto_interno)(struct vector v1, struct vector v2);
    float (*norma)(struct vector v1);
    void (*imprimir)(struct vector v1);
    struct vector (*cargar)(float x, float y, float z);
} vector_t;

// Constructor
vector_t crear_vector(float x, float y, float z);

// Funciones de métodos publicos
vector_t fsuma(vector_t v1, vector_t v2);
vector_t fresta(vector_t v1, vector_t v2);
vector_t fproducto_externo(vector_t v1, vector_t v2);
float fproducto_interno(vector_t v1, vector_t v2);
float fnorma(vector_t v);
void fimprimir(vector_t v);
vector_t fcargar(float x, float y, float z);

#endif // EJ6_H
