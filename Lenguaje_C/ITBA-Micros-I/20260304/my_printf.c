// Como compilar: gcc my_printf.c aux_lib.c -o my_printf.exe

// Librerías
#include "aux_lib.h"

// Macros
#define buffer_length ((uint8_t) 10) // Tamaño del buffer

int main (void){
    char my_string[buffer_length]="ITBA"; // Local al main
    int index; 

    // Imprimir buffer completo
    for(index = 0; index < buffer_length ; index++){
        printf("%c", my_string[index]);
    }
    printf("\n");

    // Imprimir String en forma adecuada
    for(index = 0; my_string[index] != '\0' ; index++){
        printf("%c", my_string[index]);
    }
    printf("\n");
    printf("\n");

    // Sizeof
    printf("Sizeof CHAR: %d\n", sizeof(char));
    printf("Sizeof INT: %d\n", sizeof(int));
    printf("Sizeof FLOAT: %d\n", sizeof(float));
    printf("Sizeof DOUBLE: %d\n", sizeof(double));
    
    printf("Sizeof STRING: %d\n", sizeof(my_string));
    printf("CANTIDAD DE BYTES: %d\n", sizeof(my_string)/sizeof(char));
    printf("CANTIDAD DE INTS: %d\n", sizeof(my_string)/sizeof(int));

    // Otra forma "mas portable"
    for(index = 0; index < (sizeof(my_string)/sizeof(char)) ; index++){
        printf("%c", my_string[index]);
    }
    printf("\n");
    printf("\n");
    
    // Llamar a MI FUNCION printf
    printf("Con mi funcion printf\n");
    my_lib_printf(my_string, buffer_length);


    return(0); 
}