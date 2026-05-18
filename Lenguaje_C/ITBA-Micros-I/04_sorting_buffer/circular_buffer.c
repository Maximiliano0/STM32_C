// Librerías
#include <stdio.h>
#include <stdlib.h>

// Macros
#define _Key_Buff_Size 3
#define _Num_Key_Size 4

// Función principal
int main (void){
    int numbers[_Key_Buff_Size]={0};
    char teclado[_Num_Key_Size]={0};
    int pr = 0, i = 0;

    while(1){
        printf("Ingrese un numero entero: ");
        
        // Tomo el número ingresado
        fgets(teclado, _Num_Key_Size, stdin);
        for(i=0; teclado[i] != '\n'; i++); 
        teclado[i] = '\0';


        if(pr < _Key_Buff_Size) pr++;
        else pr = 1;
        numbers[(pr==0)? 0 : pr-1] = atoi(teclado);    

        // Muestro el buffer circular
        for(i=0; i<_Key_Buff_Size; i++) printf("numbers[%d] = %d\n", i, numbers[i]);
        printf("\nproximo: %u \n", pr);
        } 

    return 0;
    }

