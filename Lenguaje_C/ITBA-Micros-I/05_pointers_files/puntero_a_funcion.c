#include "stdio.h"
#include "stdlib.h"

// Prototipo de las fuciones
void fun_1 (int);
void fun_2 (int);
void fun_3 (int);


int main (void){
    int x;
    void (*fp)(int); // Declaracion de un puntero a funcion

    // Ejecuto funciones
    fp = fun_1; 
    (*fp)(x); //fun_1(x);

    // Ejecuto funciones
    fp =  fun_3; 
    (*fp)(x); //fun_3(x);
    
    return 0;
}

// Definicion de las funciones
void fun_1 (int aux){
    printf("Hola soy la funcion 1\n");
    return;
}

void fun_2 (int aux){
    printf("Hola soy la funcion 2\n");
    return;
}

void fun_3 (int aux){
    printf("Hola soy la funcion 3\n");
    return;
}