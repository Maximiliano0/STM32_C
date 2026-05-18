/*
 * void_pointer.c
 *
 * Un puntero void (void *) es un puntero que NO tiene tipo de dato asociado.
 * Puede apuntar a cualquier tipo de dato (int, char, float, struct, etc.)
 * 
 *   - Funciones genéricas que operan sobre cualquier tipo de dato
 *   - Callbacks con contexto (muy común en HAL, RTOS, drivers)
 *   - Manejo de buffers de memoria (memcpy, memset)
 * 
 */

#include <stdio.h>
#include <string.h>

// Prototipos
void generic_print(void *dato, char tipo);
void procesar_dato(void *dato, int size, void (*callback)(void *, int));
void duplicar_bytes(void *dato, int size);

// Programa Principal
int main(void) {

    int    entero = 42, n = 255, valor = 0xAABBCCDD, i;
    float  decimal = 3.14f, f = 2.718f;
    char   letra = 'A', c = 'Z';
    unsigned char buffer[4] = {0x01, 0x02, 0x03, 0x04};

    void *pv;


    /*  
        EJEMPLO 1: Asignación básica de void *
        Un void * puede almacenar la dirección de cualquier tipo
    */
    printf("\nEJEMPLO 1: Asignacion basica\n");

    // Apunta a un int
    pv = &entero;
    // Para leer el valor, DEBO castear al tipo correcto
    printf("entero = %d (via void*: %d)\n", entero, *((int *)pv));

    // Apunta a un float (mismo puntero, distinto tipo)
    pv = &decimal;
    printf("decimal = %.2f (via void*: %.2f)\n", decimal, *((float *)pv));

    // Apunta a un char
    pv = &letra;
    printf("letra = %c (via void*: %c)\n", letra, *((char *)pv));


    /*  
        EJEMPLO 2: Recorrido byte a byte de una variable
        Castear (void *) a (char *) permite recorrer cualquier variable byte a byte
        Esto es MUY útil en microcontroladores para inspeccionar registros
    */
    printf("\nEJEMPLO 2: Recorrido byte a byte \n");

    pv = &valor;

    printf("valor = 0x%X\n", valor);
    printf("Bytes en memoria (little-endian): ");
    for (i = 0; i < sizeof(int); i++) {
        // Casteo a char* para avanzar de a 1 byte
        printf("0x%02X ", *((unsigned char *)pv + i));
    }
    printf("\n");


    /*  
    EJEMPLO 3: Función genérica de impresión con indicador de tipo
        Se pasa el dato como void * y un char indicando el tipo
        Similar a cómo se configura un periférico que puede manejar distintos 
        anchos de dato (8-bit, 16-bit, 32-bit)  
    */
    printf("\nEJEMPLO 3: Print generico \n");

    generic_print(&n, 'i');   // 'i' = int
    generic_print(&f, 'f');   // 'f' = float
    generic_print(&c, 'c');   // 'c' = char


    /*
        EJEMPLO 4: Callback con void * (patrón muy usado en RTOS y HAL)
        En microcontroladores es muy común registrar una función callback
        que recibe un void * como contexto genérico.
        Ejemplo: HAL_UART_RegisterCallback(handle, callback, contexto)
    */
    printf("\nEJEMPLO 4: Callback con void * \n");

    printf("Buffer antes:  ");
    for(i = 0; i < 4; i++) printf("0x%02X ", buffer[i]);
    printf("\n");

    // Paso el buffer como void* y una función que lo procesa
    procesar_dato(buffer, 4, duplicar_bytes);

    printf("Buffer despues: ");
    for(i = 0; i < 4; i++) printf("0x%02X ", buffer[i]);
    printf("\n");

    return 0;
}


// Definición de funciones

/*
 * generic_print: Imprime un dato genérico según su tipo
 * Parámetros:
 *   dato: puntero void al dato
 *   tipo: 'i' para int, 'f' para float, 'c' para char
 * 
 * Si el tipo no coincide con el dato real, el comportamiento es indefinido.
 */
void generic_print(void *dato, char tipo) {
    switch (tipo) {
        case 'i':
            printf("(int)   %d\n", *((int *)dato));
            break;
        case 'f':
            printf("(float) %.2f\n", *((float *)dato));
            break;
        case 'c':
            printf("(char)  %c\n", *((char *)dato));
            break;
        default:
            printf("Tipo desconocido\n");
            break;
    }
}

/*
 * procesar_dato: Aplica una función callback sobre un bloque de datos
 * Parámetros:
 *   dato: puntero genérico al bloque de datos
 *   size: tamaño del bloque en bytes
 *   callback: puntero a función que recibe (void *, int)
 * 
 * Este patrón combina void * con punteros a función.
 *   - HAL de STM32 (callbacks de interrupción)
 *   - Drivers de periféricos
 */
void procesar_dato(void *dato, int size, void (*callback)(void *, int)) {
    callback(dato, size);
}

/*
 * duplicar_bytes: Duplica el valor de cada byte en un buffer
 * Recibe void * para ser compatible con procesar_dato()
 */
void duplicar_bytes(void *dato, int size) {
    int i;
    unsigned char *p = (unsigned char *)dato;
    for (i = 0; i < size; i++) {
        p[i] = p[i] * 2;
    }
}
