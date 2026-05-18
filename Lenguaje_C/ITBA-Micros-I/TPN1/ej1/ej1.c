/************************************************************************************************
 * Ejercicio 1 - 2025                                                                           *
 * Escriba un programa que solicite 5 número enteros por teclado e imprima su valor medio.      *
 * Los 5 números deben estar separados por comas y ser signados hasta con 3 dígitos y su        *
 * ingreso realizarse en batch con la tecla enter. El programa debe imprimir en pantalla        *
 * los errores de ingreso cometidos por el usuario.                                             *
 ************************************************************************************************/

// Librerías
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Macros
#define _Buff_Size ((uint8_t) 128) // Tamaño del buffer de teclado
#define _Cant_Numeros ((uint8_t) 5) // Cantidad de números a ingresar
#define _Digitos ((uint8_t) 3) // Cantida de dígitos permitidos

// Teclas
#define _NOK_ ((uint8_t) 0)
#define _OK_ ((uint8_t) 1)

// Prototipos de funciones
uint8_t validate_digit(char digit);

// Función principal
int main (void){
    // Variables locales
    char teclado[_Buff_Size] = {0}, numero[_Digitos+2] = {0};
    int  data[_Cant_Numeros] = {0}, sum;
    uint8_t i,k,j;
    
    // Solicitar los números
    printf("Ingrese %u numeros enteros separados por comas: \n", _Cant_Numeros);
    fflush(stdin); // Limpio el buffer de entrada
    fgets(teclado, _Buff_Size, stdin); // Ingreso de datos
    
    // Parseo los datos
    for(i=0,k=0,j=0; (i<_Buff_Size) && (teclado[i]!='\n'); i=k){
        // Verifico si es valido o enter
        if(validate_digit(teclado[i])==_OK_){
            for(k=i; k<_Buff_Size; k++){
                // Si es ',' o '\n'
                if(teclado[k]==',' || teclado[k]=='\n'){
                    numero[k-i]='\0';
                    data[j++] = atoi(numero);
                    if(teclado[k]!='\n') k++;
                    break;
                }
                else numero[k-i]=teclado[k];
                // Verifico si el número no tiene ms digitos de los permitidos
                if(k-i+1>_Digitos){
                    printf("Error: Numero con mas de %u digitos\n", _Digitos);
                    break;
                }
            } 
            // Verifico si ingreso mas números de los permitidos
            if(j>_Cant_Numeros){
                printf("Error: Ingreso de mas de %u numeros\n", _Cant_Numeros);
                break;
            }
        }
        else{
            printf("Error: Caracter no valido: %c \n", teclado[i]);
            break;
        }
    }

    for(i=0; i<j; i++) printf("Numero %u: %d\n", i+1, data[i]);

    // Calculo el promedio
    for(i=0,sum=0; i<j; i++) sum+=data[i];
    printf("El promedio de los %u numeros ingresados es: %f\n", j, (float)sum/j);

    return 0;
}

// Función para validar un dígito
uint8_t validate_digit(char digit){
    // Verifico si es un número ',' o '-'
    if((digit<='9' && digit>='0') || digit=='-' || digit==',' || digit=='\n') return _OK_;
    else return _NOK_;
}