#include "stdio.h"
#include "stdlib.h"

#define _N 20

int main (void){
    char array[4] = {1, 2, 3, 4};
    char texto[][_N] = {"Borges","Conti","Bioy Casares","Sabato"};
    char c = 'F';
    char *p1 = &c;
    char **p2 = &p1;

    // Imprimir el valor de cada elemento del array
    printf("Valor del array[0] = %d\n", array[0]);
    printf("Valor del array[1] = %d\n", array[1]);
    printf("Valor del array[2] = %d\n", array[2]);
    printf("Valor del array[3] = %d\n", array[3]);

    // Como puntero
    printf("Valor del *(array) = %d\n", *array);
    printf("Valor del *(array + 1) = %d\n", *(array + 1));
    printf("Valor del *(array + 2) = %d\n", *(array + 2));
    printf("Valor del *(array + 3) = %d\n", *(array + 3));

    // int pointer
    printf("Valor del (int *)array = %X\n", *((int *)array));

    // Texto como array de caracteres
    printf("Valor del texto[0] = %s\n", texto[0]);
    printf("Valor del texto[1] = %s\n", texto[1]);
    printf("Valor del texto[2] = %s\n", texto[2]);
    printf("Valor del texto[3] = %s\n", texto[3]);

    // Texto como puntero a array de caracteres
    printf("Valor del *(texto) = %s\n", *texto);
    printf("Valor del *(texto + 1) = %s\n", *(texto + 1));
    printf("Valor del *(texto + 2) = %s\n", *(texto + 2));
    printf("Valor del *(texto + 3) = %s\n", *(texto + 3));

    // Acceso a un caracter específico
    printf("Valor del texto[0][0] = %c\n", texto[0][0]);
    printf("Valor del texto[1][0] = %c\n", texto[1][0]);
    printf("Valor del texto[2][0] = %c\n", texto[2][0]);
    printf("Valor del texto[3][0] = %c\n", texto[3][0]);

    // Acceso a un caracter específico usando punteros
    printf("Valor del *(*(texto) + 2) = %c\n", *(*(texto) + 2));
    printf("Valor del *(*(texto + 1) + 2) = %c\n", *(*(texto + 1) + 2));
    printf("Valor del *(*(texto + 2) + 2) = %s\n", &(*(*(texto + 2) + 2)));
    printf("Valor del *(*(texto + 3) + 2) = %c\n", *(*(texto + 3) + 2));

    // Imprimo puntero a puntero
    printf("Valor del p1 = %c\n", *p1);
    printf("Valor del p2 = %c\n", **p2);
    printf("Valor del *p2 = %X\n", *p2);

    return 0; 
}