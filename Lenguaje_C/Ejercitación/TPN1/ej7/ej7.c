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

// Includes
#include "ej7.h"

// Buffers de las FIFO
/*  Debe crearse un buffer global por cada FIFO a manejar   */
uint8_t fifo_1_buffer[FIFO_SIZE];

// Constructor
fifo_t fifo_create(uint8_t *buffer) {
    fifo_t fifo;

    // Inicialización de la FIFO
    fifo.data = buffer;
    fifo.head = 0;
    fifo.tail = 0;
    fifo.count = 0;
    
    // Métodos
    fifo.push = fifo_push;
    fifo.pop = fifo_pop;
    fifo.isEmpty = fifo_isEmpty;
    fifo.isFull = fifo_isFull;
    fifo.display = fifo_display;

    return fifo;
}

// Prototipos de funciones
uint8_t fifo_push(uint8_t to_insert, fifo_t *fifo) {
    
    // Verifica si la FIFO está llena
    if (fifo->isFull(fifo)) return FIFO_ERROR;

    // Inserta el elemento en "tail"
    fifo->data[fifo->tail] = to_insert;

    // Incrementa "tail" y "count"
    fifo->tail++;
    if (fifo->tail == FIFO_SIZE) fifo->tail = 0; // Buffer circular
    fifo->count++;

    return FIFO_OK;
}

uint8_t fifo_pop(fifo_t *fifo) {
    
    // Verifica si la FIFO está vacía
    if (fifo->isEmpty(fifo)) return FIFO_ERROR;

    // Incrementa "head" y "count"
    fifo->head++;
    if (fifo->head == FIFO_SIZE) fifo->head = 0; // Buffer circular
    fifo->count--;

    return FIFO_OK;
}

uint8_t fifo_isEmpty(fifo_t *fifo) {
    return ((fifo->count == 0) ? FIFO_EMPTY : FIFO_OK);
}

uint8_t fifo_isFull(fifo_t *fifo) {
    return ((fifo->count == FIFO_SIZE) ? FIFO_FULL : FIFO_OK);
}

void fifo_display(fifo_t *fifo) {
    uint8_t i;

    for(i=0; i<fifo->count; i++) {
        printf("Elemento %u: %u\n", i, fifo->data[(fifo->head + i) % FIFO_SIZE]);
    }
    printf("head: %u\t tail: %u\t count: %u\n", fifo->head, fifo->tail, fifo->count);

    return; 
}
