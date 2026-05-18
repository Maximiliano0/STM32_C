/************************************************************************************************
 * Ejercicio 3 - 2025                                                                           *
 * Escriba un programa el cual valide el nombre de usuario y la password del mismo solicitadas  *
 * por pantalla con user: Micros&Control y password: 22.57.                                     *
 ************************************************************************************************/

// Librerías
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Macros
#define _User_MaxSize 20
#define _Password_MaxSize 10

// Tipos de Datos

// Prototipo de Funciones

// Variables Globales
const char _User_OK[] = "Micros&Control";
const char _Password_OK[] = "22.57";

// Función principal
int main (void){
    char user[_User_MaxSize]={0}, pass[_Password_MaxSize]={0};
    uint8_t i = 0;

    // Solicito el nombre de usuario
    printf("Ingrese el nombre de usuario: ");
    
    fgets(user, _User_MaxSize, stdin);
    for(i=0; user[i] != '\n'; i++); 
    user[i] = '\0';
    
    if(strcmp(user, _User_OK) != 0){
        printf("Usuario incorrecto\n");
        return 0;
    }

    // Solicito la contraseña
    printf("Ingrese la clave de usuario: ");
    
    fgets(pass, _Password_MaxSize, stdin);
    for(i=0; pass[i] != '\n'; i++); 
    pass[i] = '\0';
    
    if(strcmp(pass, _Password_OK) != 0){
        printf("Password incorrecto\n");
        return 0;
    }

    printf(">>>>> Usuario y Password correctos <<<<<");
    return 0;
}


