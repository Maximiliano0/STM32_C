/************************************************************************************************
 * Ejercicio 10 - 2026                                                                          *
 * Escriba un programa sencillo que permita llevar el control de las ventas realizadas          *
 * por un comercio durante el dia. Los productos poseen un precio por unidad y pueden           *
 * repetirse en la lista, pero deben evitarse errores tipograficos (Pan, PAN, pan, etc).        *
 * Al finalizar el dia se debe imprimir el total de ganancias y el top 5 de los productos      *
 * mas consumidos. Implementacion con gestion de memoria dinamica.                              *
 ************************************************************************************************/

// Includes
#include "ej10.h"

// Funcion principal
int main(void) {
    // Variables locales
    nodo_t *head = NULL;    // Puntero al primer nodo de la lista
    nodo_t *encontrado;     // Puntero al nodo encontrado en busqueda
    char nombre[_Buff_Size] = {0};
    uint32_t unidades = 0;
    float precio;

    printf("---- Control de Ventas ----\n");
    printf("Ingrese 'FIN' para cerrar el dia.\n\n");

    while (1) {
        // Solicitar nombre del producto
        printf("Producto: ");
        fgets(nombre, _Buff_Size, stdin);
        // Elimino el '\n'
        nombre[strcspn(nombre, "\n")] = '\0';

        // Normalizo a minusculas para evitar errores tipograficos
        str_to_lower(nombre);

        // Verifico si se desea finalizar
        if (!strcmp(nombre, "fin")) break;

        // Solicitar cantidad
        printf("Cantidad: ");
        scanf("%u", &unidades);

        // Busco si el producto ya existe en la lista enlazada
        encontrado = buscar_producto(head, nombre);

        if (encontrado != NULL) {
            // Producto existente: sumo unidades al nodo encontrado
            encontrado->cantidad += unidades;
            printf(">> %s (x%u) - $%.2f c/u\n\n", encontrado->nombre, encontrado->cantidad, encontrado->precio);
        } else {
            // Producto nuevo: solicito precio
            printf("Precio unitario: ");
            scanf("%f", &precio);

            // Creo un nuevo nodo y lo inserto al inicio de la lista
            head = agregar_producto(head, nombre, precio, unidades);

            printf(">> Producto agregado.\n\n");
        }

        // Limpio el buffer de entrada (por el scanf)
        while (getchar() != '\n');
    }

    // Imprimo resumen del dia
    imprimir_resumen(head);

    // Libero todos los nodos de la lista enlazada
    liberar_lista(head);

    return 0;
}
