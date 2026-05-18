// printf()
#include <stdio.h>
// Types
#include <stdint.h>

int main(void) {

    // Imprime "Hola, mundo!" en la consola
    /* Comentario muy largo
    que ocupa varias líneas*/
    printf("Hola, mundo!");

    /*      SIZEOF      */

    // Sizeof 
    printf("\n%d\n", sizeof(int));
    printf("%d\n", sizeof(int16_t));
    printf("%d\n", sizeof(int32_t));
    
    // Flotante
    printf("%d\n", sizeof(float));
    printf("%d\n", sizeof(double));

    // CHAR
    printf("%d\n", sizeof(char));
    printf("%d\n", sizeof(uint8_t));

    printf("%d\n", '0');
    printf("%c\n", '0');
    
    printf("%d\n", 'A');
    printf("%c\n", 'A');

    return(0);
}