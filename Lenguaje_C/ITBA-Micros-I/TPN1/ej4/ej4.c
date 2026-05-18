/************************************************************************************************
 * Ejercicio 4 - 2025                                                                           *
 * Agregue al código del inciso (3) la posibilidad de validar pares (user, password)            *
 * almacenados en memoria. El programa de contemplar que los pares (user,password) pueden       *
 * cambiar ya que en futuras implementaciones los mismos serán obtenidos desde una base de      *
 * datos externa.                                                                               *
 * Como ejemplo se puede usar la siguiente "base de datos":                                     *
 * const user_t db[_MaxDB] = {                                                                  *
 *                     {"Micros&Control", "22.57"},                                             *
 *                     {"Douglas Adams", "42"},                                                 *
 *                     {"Jorge Luis Borges", "Aleph"},                                          *
 *                     {"Ursula K Leguin", "Terramar"}                                          *
 *                     };                                                                       *
 ************************************************************************************************/

// Librerías
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Macros
#define _User_MaxSize 40
#define _Password_MaxSize 10
#define _MaxDB 4

// Tipos de Datos
typedef struct{
    char user[_User_MaxSize];
    char password[_Password_MaxSize];
}user_t;

// Prototipo de Funciones

// Variables Globales
const user_t db[_MaxDB] = {
                      {"Micros&Control", "22.57"},
                      {"Douglas Adams", "42"},
                      {"Jorge Luis Borges", "Aleph"},
                      {"Ursula K Leguin", "Terramar"}
                      };

// Función principal
int main (void){
    char user[_User_MaxSize]={0}, pass[_Password_MaxSize]={0};
    uint8_t i = 0, j = 0;

    // Solicito el nombre de usuario
    printf("Ingrese el nombre de usuario: ");
    
    fgets(user, _User_MaxSize, stdin);
    for(i=0; user[i] != '\n'; i++); 
    user[i] = '\0';
    
    for(j=0; j<_MaxDB; j++){
        if(strcmp(user, db[j].user)==0) break;
    } 
    if(j == _MaxDB){
        printf("Usuario no encontrado en la DB\n");
        return 0;
    }
 
    // Solicito la contraseña
    printf("Ingrese la clave de usuario: ");
    
    fgets(pass, _Password_MaxSize, stdin);
    for(i=0; pass[i] != '\n'; i++); 
    pass[i] = '\0';
    
    if(strcmp(pass, db[j].password) != 0){
        printf("Password incorrecto\n");
        return 0;
    }

    printf(">>>>> Usuario y Password correctos <<<<<");
    return 0;
}


