/**************************************************************************************
 * Ejercicio 7 - 2025                                                                 *
 * Escriba una librería que implemente colas del tipo “FIFO” de tamaño FIFO_SIZE      *
 * donde se contemplen las siguientes operaciones:                                    *
 *      - Creación de la FIFO                                                         *
 *      - Inicialización de la FIFO                                                   *
 *      - Inserción de un elemento                                                    *
 *      - Eliminación de un elemento                                                  *
 *      - Revisión de si la FIFO esta vacía                                           *
 *      - Revisión de si la FIFO esta llena                                           *
 * La implementación debe realizarse mediante el uso de tipos de dato struct          *
 * y punteros a función.                                                              *
 **************************************************************************************/
#ifndef EJ7_H
#define EJ7_H

// Includes
#include <stdint.h>
#include <stdio.h>

// Macros
#define FIFO_SIZE 4
#define FIFO_OK 0
#define FIFO_ERROR 1
#define FIFO_EMPTY 0
#define FIFO_FULL 1

// Tipos
typedef struct handler_fifo{
    // Puntero al buffer de la FIFO
    uint8_t *data;
    // Indice al ultimo elemento extraido
    uint8_t head;
    // Indice al último elemento ingresado
    uint8_t tail;
    // Cantidad de elementos en la FIFO
    uint8_t count;
    // Métodos
    uint8_t (*push) (uint8_t to_insert, struct handler_fifo *fifo);
    uint8_t (*pop) (struct handler_fifo *fifo);
    uint8_t (*isEmpty)(struct handler_fifo *fifo);
    uint8_t (*isFull)(struct handler_fifo *fifo);
    void (*display)(struct handler_fifo *fifo);

} fifo_t;

// Constructor
fifo_t fifo_create(uint8_t *buffer);

// Prototipos de funciones
uint8_t fifo_push(uint8_t to_insert, fifo_t *fifo);
uint8_t fifo_pop(fifo_t *fifo);
uint8_t fifo_isEmpty(fifo_t *fifo);
uint8_t fifo_isFull(fifo_t *fifo);
void fifo_display(fifo_t *fifo);

#endif
