// Librerías
#include <stdio.h>
#include <stdlib.h>

// Prototipo de la función
void bubble_sort(char *data, int size);

// Función principal
int main (void){
    // Variables locales
    char buffer[4] = {5,6,1,3};
    int i, j;

    // Muestro los números ingresados
    printf("Array Desordenado:\n");
    for(i=0; i < (sizeof(buffer)/sizeof(char)); i++) printf("buffer[%u]: %d\n", i, buffer[i]);

    // Ordeno los números
    bubble_sort(buffer, sizeof(buffer)/sizeof(char));

    // Muestro los números ordenados
    printf("\nArray Ordenado:\n");
    for(i=0; i < (sizeof(buffer)/sizeof(char)); i++) printf("buffer[%u]: %d\n", i, buffer[i]);

    return 0;
}

// Función para ordenar los números
void bubble_sort(char *array, int size){
    int i,j;
    int temp;

    for(i=0; i<size-1; i++){

        for(j=0; j<size-i-1; j++){

            if(array[j] > array[j+1]){
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }

            // Muestro los números entre los swaps
            printf("\nSwaps\n");
            for(int k=0; k<size; k++) printf("data[%u]: %d\n", k, array[k]);
            getchar();
            
        }
    
    printf("Nueva iteracion\n");
    getchar();
    system("clear");

    }
}