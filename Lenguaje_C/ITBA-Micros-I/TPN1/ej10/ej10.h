/************************************************************************************************
 * Ejercicio 10 - 2026                                                                          *
 * Escriba un programa sencillo que permita llevar el control de las ventas realizadas          *
 * por un comercio durante el dia. Los productos poseen un precio por unidad y pueden           *
 * repetirse en la lista, pero deben evitarse errores tipograficos (Pan, PAN, pan, etc).        *
 * Al finalizar el dia se debe imprimir el total de ganancias y el top 5 de los productos      *
 * mas consumidos. Implementacion con lista enlazada y memoria dinamica.                        *
 ************************************************************************************************/

// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

// Macros
#define _Buff_Size  ((uint8_t) 64)
#define _Top        ((uint8_t) 5)
#define _OK         ((uint8_t) 1)
#define _NOK        ((uint8_t) 0)

// Nodo de la lista enlazada de productos
typedef struct nodo {
    char        nombre[_Buff_Size];  // Nombre del producto
    float       precio;              // Precio unitario
    uint32_t    cantidad;            // Cantidad vendida
    struct nodo *next;               // Puntero al siguiente nodo
} nodo_t;

// Prototipos
void    str_to_lower(char *str);
nodo_t *buscar_producto(nodo_t *head, const char *nombre);
nodo_t *agregar_producto(nodo_t *head, const char *nombre, float precio, uint32_t unidades);
void    imprimir_resumen(nodo_t *head);
void    liberar_lista(nodo_t *head);
