/************************************************************************************************
 * Ejercicio 10 - 2026                                                                          *
 * Funciones de la libreria de control de ventas.                                               *
 * Implementacion con lista enlazada y memoria dinamica usando malloc.                          *
 ************************************************************************************************/

// Includes
#include "ej10.h"

/************************************************************************************************
 * str_to_lower: convierte un string a minusculas                                               *
 ************************************************************************************************/
void str_to_lower(char *str) {
    for (uint32_t i = 0; str[i] != '\0'; i++)
        str[i] = (char)tolower((unsigned char)str[i]);
}

/************************************************************************************************
 * buscar_producto: recorre la lista enlazada buscando un nodo por nombre                       *
 * Retorna el puntero al nodo si lo encuentra, NULL si no existe                                *
 ************************************************************************************************/
nodo_t *buscar_producto(nodo_t *head, const char *nombre) {
    nodo_t *actual = head;
    while (actual != NULL) {
        if (!strcmp(actual->nombre, nombre))
            return actual;
        actual = actual->next;
    }
    return NULL;
}

/************************************************************************************************
 * agregar_producto: crea un nuevo nodo y lo inserta al inicio de la lista                      *
 * Retorna el nuevo head de la lista                                                            *
 ************************************************************************************************/
nodo_t *agregar_producto(nodo_t *head, const char *nombre, float precio, uint32_t unidades) {
    // Reservo memoria para el nuevo nodo
    nodo_t *nuevo = (nodo_t *)malloc(sizeof(nodo_t));
    if (nuevo == NULL) {
        printf("Error: sin memoria disponible.\n");
        return head;
    }

    // Cargo los datos del producto
    strcpy(nuevo->nombre, nombre);
    nuevo->precio = precio;
    nuevo->cantidad = unidades;

    // Linkeo el nuevo nodo al inicio de la lista
    nuevo->next = head;

    return nuevo;
}

/************************************************************************************************
 * contar_nodos: cuenta la cantidad de nodos en la lista enlazada                               *
 ************************************************************************************************/
static uint32_t contar_nodos(nodo_t *head) {
    uint32_t cant = 0;
    while (head != NULL) {
        cant++;
        head = head->next;
    }
    return cant;
}

/************************************************************************************************
 * imprimir_resumen: imprime el total de ganancias y el top 5 de productos mas vendidos         *
 ************************************************************************************************/
void imprimir_resumen(nodo_t *head) {
    float total = 0;
    uint32_t i, j, top;
    nodo_t *actual;

    if (head == NULL) {
        printf("\nNo se registraron ventas.\n");
        return;
    }

    // Cuento los nodos
    uint32_t cant = contar_nodos(head);

    // Calculo el total de ganancias
    printf("\n---- Resumen del dia ----\n");
    actual = head;
    while (actual != NULL) {
        float subtotal = actual->precio * actual->cantidad;
        printf("  %-20s x%-5u $%.2f c/u = $%.2f\n",
               actual->nombre, actual->cantidad, actual->precio, subtotal);
        total += subtotal;
        actual = actual->next;
    }
    printf("  ------------------------------------\n");
    printf("  TOTAL: $%.2f\n\n", total);

    // Armo un arreglo auxiliar de punteros a nodos para ordenar el top 5
    nodo_t **arr = (nodo_t **)malloc(cant * sizeof(nodo_t *));
    actual = head;
    for (i = 0; i < cant; i++) {
        arr[i] = actual;
        actual = actual->next;
    }

    // Ordeno por cantidad (bubble sort descendente)
    for (i = 0; i < cant - 1; i++) {
        for (j = 0; j < cant - 1 - i; j++) {
            if (arr[j]->cantidad < arr[j + 1]->cantidad) {
                nodo_t *tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }

    // Imprimo top 5
    top = (cant < _Top) ? cant : _Top;
    printf("---- Top %u productos mas vendidos ----\n", top);
    for (i = 0; i < top; i++) {
        printf("  %u. %-20s (%u unidades)\n",
               i + 1, arr[i]->nombre, arr[i]->cantidad);
    }

    // Libero el arreglo auxiliar de punteros
    free(arr);
}

/************************************************************************************************
 * liberar_lista: recorre la lista enlazada y libera cada nodo                                  *
 ************************************************************************************************/
void liberar_lista(nodo_t *head) {
    nodo_t *actual = head;
    nodo_t *siguiente;
    while (actual != NULL) {
        siguiente = actual->next;
        free(actual);
        actual = siguiente;
    }
}
