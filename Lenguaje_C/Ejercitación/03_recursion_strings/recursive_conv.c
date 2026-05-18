/*
 * Clase: Recursividad aplicada a filtrado por convolucion discreta
 * Implementacion recursiva
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
void recursive_conv(const float entrada[MUESTRAS_ENTRADA],
                    const float kernel[KERNEL_TAM],
                    float salida[MUESTRAS_SALIDA],
                    int n);

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

    recursive_conv(entrada, kernel, salida, 0);

    printf("=== Convolucion recursiva ===\n");
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
        printf("%.2f ", salida[i] / GANANCIA_KERNEL);
    }

    printf("\n");

    return 0;
}


// Definicion de funciones
void recursive_conv(const float entrada[MUESTRAS_ENTRADA],
                    const float kernel[KERNEL_TAM],
                    float salida[MUESTRAS_SALIDA],
                    int n)
{
    int k;
    float acumulado = 0;

    if (n == MUESTRAS_SALIDA) {
        return;
    }

    // Para este n, calculo la suma de convolucion con un bucle simple en k.
    for (k = 0; k < KERNEL_TAM; k++) {
        int indice_entrada = n - k;

        if ((indice_entrada >= 0) && (indice_entrada < MUESTRAS_ENTRADA)) {
            acumulado += entrada[indice_entrada] * kernel[k];
        }
    }

    salida[n] = acumulado;

    // Recursion didactica: avanza al siguiente indice de salida.
    recursive_conv(entrada, kernel, salida, n + 1);

    return;
}
