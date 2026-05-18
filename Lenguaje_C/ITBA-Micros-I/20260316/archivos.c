#include "stdio.h"
#include "stdlib.h"

int main(void) {
    int aux; 
    FILE *p_original, *p_copia;

    // Punteros a archivos
    p_original = fopen("golum.jpg", "rb");
    p_copia = fopen("golum_copy.jpg", "wb");

    // Copio archivos con funciones standar
    while ((aux = fgetc(p_original)) != EOF) {
        printf("%x", aux);
        fputc(aux, p_copia);
    }

    // Declaro que ya no uso esos punteros
    fclose(p_original);
    fclose(p_copia);
    return 0;
}