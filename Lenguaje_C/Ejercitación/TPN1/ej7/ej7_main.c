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
extern uint8_t fifo_1_buffer[FIFO_SIZE];

// Funcion principal
int main (void){
    // Creación de la FIFO
    fifo_t fifo_1 = fifo_create(fifo_1_buffer);
    uint8_t i; 

    // Inserción de elementos
    printf("Insercion de elementos\n");
    for(i=0; i<FIFO_SIZE+1; i++){
        fifo_1.push(i, &fifo_1);
        fifo_1.display(&fifo_1);
        getchar();
    }

    // Eliminación de elementos
    printf("Eliminacion de elementos\n");
    for(i=0; i<FIFO_SIZE; i++){
        fifo_1.pop(&fifo_1);
        fifo_1.display(&fifo_1);
        getchar();
    }

    return 0;
}