/**************************************************************************************
 * Ejercicio 8 - 2025                                                                 *
 * 8-	Realize un programa que permita calcular la traza y determinante de una       *
 * matriz de números enteros con dimensión 3x3. Las operaciones deben realizare       *
 * mediante funciones que debe implementar e invocar desde el programa principal.     *                                                *
 **************************************************************************************/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Prototipos
float traza(int matriz[3][3]);
float determinante(int matriz[3][3]);

// Main
int main() {
    // Variables
    int matriz[3][3], i, j;
    float tra, det;

    // Ingreso de datos
    printf("Ingrese los valores de la matriz 3x3:\n");
    for(i = 0; i < 3; i++) {
        printf("Fila %d \n", i + 1);
        for (int j = 0; j < 3; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    // Impresion de la matriz
    printf("Matriz ingresada: \n");
    for(i=0; i<3 ;i++){
        printf("|\t");
        for(j=0;j<3;j++) printf("%d\t", matriz[i][j]);
        printf("|\n");
    }

    // Calculo de traza y determinante
    tra = traza(matriz);
    det = determinante(matriz);

    // Salida de datos
    printf("Traza de la matriz: %.2f\n", tra);
    printf("Determinante de la matriz: %.2f\n", det);

    return 0;
}

// Funciones
float traza(int matriz[3][3]) {
    float tra = 0;
    uint8_t i;
    for (i = 0; i < 3; i++) tra += matriz[i][i];
    return tra;
}

float determinante(int matriz[3][3]) {
    float det = 0;
    det = (matriz[0][0] * matriz[1][1] * matriz[2][2]) 
        + (matriz[0][1] * matriz[1][2] * matriz[2][0]) 
        + (matriz[0][2] * matriz[1][0] * matriz[2][1]) 
        - (matriz[0][2] * matriz[1][1] * matriz[2][0]) 
        - (matriz[0][0] * matriz[1][2] * matriz[2][1])
         - (matriz[0][1] * matriz[1][0] * matriz[2][2]);
    
    return det;
}
