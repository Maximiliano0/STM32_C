// Como compilar: gcc keyboard_input.c aux_lib.c -o keyboard_input.exe

// Librerías
#include "aux_lib.h"

// Función principal
int main (void){
    // Variables locales
    char teclado[_Buff_Size] = {0};
    int  buffer[_Cant_Numeros] = {0};
    int i,k,j;
    
    // Solicitar los números
    printf("Ingrese %u numeros enteros: \n", _Cant_Numeros);
    fflush(stdin); // Limpio el buffer de entrada
    fgets(teclado, _Buff_Size, stdin); // Ingreso de datos
    
    // Parseo los datos
    for(i=0; (i<_Buff_Size) && (teclado[i]!='\n'); i++){

        // Verifico si es un número válido
        if(validate_digit(teclado[i])==_OK_) buffer[i] = char_to_int(teclado[i]);
        else{
            printf("Error: Caracter no valido: %c \n", teclado[i]);
            break;
        }
    }

    // Imprimo el buffer
    for(i=0; i<_Cant_Numeros; i++) printf("buffer[%u]: %d\n", i, buffer[i]);

    return(0);
}
