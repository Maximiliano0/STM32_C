/************************************************************************************************
 * Ejercicio 5 - 2025                                                                           *
 * Escriba un programa que permanentemente solicite un número entero e imprima en pantalla      *
 * el promedio de los últimos 10 números ingresados hasta que el usuario ingrese la             *
 * palabra “EXIT”.                                                                              *
 ************************************************************************************************/

// Librerías
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Macros
#define _Key_Buff_Size 10
#define _Num_Key_Size 10
#define _OK 1
#define _NOK 0

// Función principal
int main (void){
    int numbers[_Num_Key_Size]={0}, sum = 0;
    char teclado[_Num_Key_Size]={0};
    uint8_t last = 0, i = 0, in_flag = _NOK;
    float prom = 0;

    while(1){
        printf("Ingrese un numero entero: ");
        
        // Tomo el número ingresado
        fgets(teclado, _Num_Key_Size, stdin);
        for(i=0; teclado[i] != '\n'; i++); 
        teclado[i] = '\0';

        // Verifico si es la palabra EXIT
        if(!strcmp(teclado, "EXIT")) return 0;

        // Verifico si es un número
        in_flag = _OK;
        for(i=0; teclado[i] != '\0'; i++){
            if((teclado[i] >= '0' && teclado[i] <= '9') || teclado[i] == '-') continue;
            else{
                printf(">> El valor ingresado no es un numero entero. <<\n");
                in_flag = _NOK;
                break;
                }
            }

        // Ingreso el número en el buffer circular
        if(in_flag == _OK){
            if(last < _Key_Buff_Size) last++;
            else last = 1;
            numbers[(last==0)? 0 : last-1] = atoi(teclado);  
        }

        // Muestro el buffer circular
        for(i=0; i<last; i++) printf("numbers[%d] = %d\t", i, numbers[i]);
        printf("\nlast: %u \n", last);

        // Calculo el promedio
        for(i=0, sum=0; i<last; i++) sum += numbers[i];
        prom = (float)sum/last;
        printf("El promedio de los ultimos 10 numeros ingresados es: %.2f\n", prom);

        } 

    return 0;
    }

