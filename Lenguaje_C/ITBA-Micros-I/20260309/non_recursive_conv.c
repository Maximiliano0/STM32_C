/*
 * Clase: Recursividad aplicada a filtrado por convolucion discreta
 * Implementacion no recursiva (iterativa)
 * Convolución discreta: salida[n] = sum_k entrada[n-k] * kernel[k]
 */

// Librerias
#include <stdio.h>

// Macros
#define MUESTRAS_ENTRADA 64
#define KERNEL_TAM 4
#define MUESTRAS_SALIDA (MUESTRAS_ENTRADA + KERNEL_TAM - 1)
#define GANANCIA_KERNEL 4

// Declaracion de funciones
void non_recursive_conv(const float entrada[MUESTRAS_ENTRADA],
                        const float kernel[KERNEL_TAM],
                        float salida[MUESTRAS_SALIDA]);

// Main                        
int main(void)
{
    // Misma forma de senal con sobremuestreo x4 (retencion por muestra).
    float entrada[MUESTRAS_ENTRADA] = {
        4,4,4,4, 6,6,6,6, 8,8,8,8, 7,7,7,7,
        6,6,6,6, 4,4,4,4, 2,2,2,2, 1,1,1,1,
        0,0,0,0, 1,1,1,1, 2,2,2,2, 4,4,4,4,
        6,6,6,6, 7,7,7,7, 8,8,8,8, 7,7,7,7
    };
    float kernel[KERNEL_TAM] = {1, 1, 1, 1};
    float salida[MUESTRAS_SALIDA] = {0};
    int i;

    non_recursive_conv(entrada, kernel, salida);

    printf("=== Convolucion no recursiva ===\n");
    printf("Entrada: ");
    for (i = 0; i < MUESTRAS_ENTRADA; i++) {
        printf("%.2f ", entrada[i]);
    }

    printf("\nKernel (normalizado /%d): ", GANANCIA_KERNEL);
    for (i = 0; i < KERNEL_TAM; i++) {
        printf("%.2f ", kernel[i]);
    }

    printf("\nSalida cruda: ");
    for (i = 0; i < MUESTRAS_SALIDA; i++) {
        printf("%.2f ", salida[i]);
    }

    printf("\nSalida normalizada: ");
    for (i = 0; i < MUESTRAS_SALIDA; i++) {
        printf("%.2f ", (float)salida[i] / GANANCIA_KERNEL);
    }

    printf("\n");

    return 0;
}


// Definicion de funciones
void non_recursive_conv(const float entrada[MUESTRAS_ENTRADA],
                        const float kernel[KERNEL_TAM],
                        float salida[MUESTRAS_SALIDA])
{
    int n;

    for (n = 0; n < MUESTRAS_SALIDA; n++) {
        int k;
        float acumulado = 0;
        int indice_entrada;

        // Para cada salida n, sumamos los productos validos entrada[n-k] * kernel[k]. 
        for (k = 0; k < KERNEL_TAM; k++) {
            indice_entrada = n - k;

            if ((indice_entrada >= 0) && (indice_entrada < MUESTRAS_ENTRADA)) {
                acumulado += entrada[indice_entrada] * kernel[k];
            }
        }

        salida[n] = acumulado;
    }

    return;
}