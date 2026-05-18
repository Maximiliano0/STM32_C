#include "stdio.h"
#include "stdlib.h"

int main (void){
    int a = 2;
    int b = 1024;
    int *p;
    char *pc;
    void *pv; 

    // Dirección de variable a
    p = &a; 

    printf("Valor de a = %d\n", a);

    printf("Valor de p = %X\n", p);
    printf("Valor de la direccion de a = %X\n", &a);

    // Dirección de puntero p
    printf("Valor de la direccion de p = %X\n", &p);

    // Contenido de lo apuntado
    a = 3;
    printf("Valor de lo apuntado por p = %d\n", *p);
    printf("Valor de a = %d\n", a);

    *p = 4;
    printf("Valor de lo apuntado por p = %d\n", *p);
    printf("Valor de a = %d\n", a);

    // Mal uso de puntero
    p = ((int *)(&a))+ 1;
    printf("Valor de p = %X\n", p);
    *p = 5;
    printf("Valor de lo apuntado por p = %d\n", *p);

    // Trabajo con puntero a char
    b = 0x1234;
    pc = (char*) &b;

    printf("Valor de b = %X\n", b);
    printf("Valor de pc = %X\n", *pc);

    pc++;
    printf("Valor de pc = %X\n", *pc);

    // Void Pointer
    pv = (void *) &a;
    printf("Valor de pv = %d\n", *((int *)pv));

    

    return(0); 
}