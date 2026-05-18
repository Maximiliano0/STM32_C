/************************************************************************************************
 * Ejercicio 10 - 2025                                                                          *
 * Escriba un programa el cual pida por pantalla el nombre del usuario y lo imprima en          *
 * mayúsculas en forma permanente solo pudiendo salir mediante la señal SIGINT, tras la cual    *
 * debe despedirse al usuario. El programa debe imprimir en pantalla los errores de             *
 * ingreso cometidos por el usuario, ya que no serán válidos los nombres que contengan números  *
 * o carácteres especiales.                                                                     *
 ************************************************************************************************/

// Librerías
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>

// Macros
#define _Buffer_Size ((uint8_t) 50) 
#define is_mayus(c) (c >= 'A' && c <= 'Z')? 1 : 0
#define is_minus(c) (c >= 'a' && c <= 'z')? 1 : 0

// Tipos de Datos
typedef enum estados_t{
    INIT,
    ESPERANDO,
    VALIDANDO,
    ERROR
} estados_t;

// Prototipo de Funciones

// handler de la señal SIGINT
void handler_sigint(int sig) {
    // Mensaje de despedida
    printf("\n>>>>> Muchas gracias por utilizar el programa. <<<<<\n");
    // Finalización del programa
    exit(0);
}

// Función principal
int main (void){
   estados_t estado = INIT; // static?
   char nombre[_Buffer_Size] = {0}, mayusculas[_Buffer_Size] = {0};
   uint8_t i = 0;

   // Asignación de Handler para la señal SIGINT
   signal(SIGINT, handler_sigint);

   // Loop Infinito
   while (1) {

    switch (estado)
    {
    case INIT:
        printf(">>>>> Programa Inicializado <<<<<\n");
        printf("Por favor, ingrese su nombre: ");
        estado = ESPERANDO;
        break;
    
    case ESPERANDO:
        // Leo teclado    
        if(fgets(nombre, _Buffer_Size, stdin) == NULL) {
            printf("Error: No se pudo leer el nombre.\n");
            estado = ERROR;
            break;
        }
        estado = VALIDANDO;
        break;
    
    case VALIDANDO:
        //Reviso nombre ingresado
        for (i = 0; (nombre[i]!='\n') && (estado!=ERROR); i++) {
            if(!(is_mayus(nombre[i]) || is_minus(nombre[i]))) {
                printf("Error: El nombre no puede contener numeros ni caracteres especiales.\n");
                estado = ERROR;
                break;
            }
            else{
                if (is_mayus(nombre[i])) {
                    mayusculas[i] = nombre[i];
                } else {
                    mayusculas[i] = nombre[i] - ('a'- 'A');
                }
            }
        }
        if (estado==ERROR) break;
        // Termino String
        mayusculas[i] = '\0';
        printf("Nombre en Mayusculas: %s\n", mayusculas);
        printf("Por favor, ingrese su nombre: ");
        estado = ESPERANDO;
        break;
    
    case ERROR:
        printf(">>>>> Presione una tecla para continuar <<<<<\n");
        getchar();
        estado = INIT;
        break;
    
    default:
        estado = ERROR;
        break;
    }


    // Delay de 1 segundo
    sleep(1);
    }

    return 0;
}


