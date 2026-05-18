#include <stdio.h>

// Declaración de la función parity_check
int parity_ccheck(int);

int main(void){
    // Variables locales a main
    int my_num1 = 5;
    int my_num2;

    // Llamo a la función parity_check y guardo el resultado en my_num2
    my_num2 = parity_ccheck(my_num1);

    // Imprime el resultado de la función parity_check
    if(my_num2 == 0){
        printf("El numero es par.\n");
    } else {
        printf("El numero es impar.\n");
    }

    // Que pasa si pregunto por parity
    printf("El valor de parity es: %d\n", parity);

    // Retorno ERROR CODE 
    return(0);
}

// Definición de la función parity_check
int parity_ccheck(int dummy){
    // Variables locales a parity_check
    int parity=0;

    // Me fijo si el número es par o impar
    parity = (dummy & 1) ? 1 : 0;

    // Retorno el valor de parity
    return(parity);
}