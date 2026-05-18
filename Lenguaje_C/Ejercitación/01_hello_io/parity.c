/*****************************************************************************
 * parity.c  -  Funciones y alcance (scope) de variables locales
 *---------------------------------------------------------------------------*
 * Objetivo didactico:
 *   1) Declarar y definir una funcion (prototipo + cuerpo).
 *   2) Pasar parametros por valor: la funcion recibe una COPIA del argumento.
 *   3) Entender que las variables locales (como `parity` dentro de
 *      parity_ccheck) solo existen DENTRO de la funcion que las declara.
 *      La referencia a `parity` desde main da error de compilacion: ese
 *      error es DELIBERADO para mostrar el concepto de scope.
 *   4) Detectar paridad con el operador AND bit a bit (n & 1).
 *
 * Compilar:  gcc parity.c -o parity
 * NOTA: este archivo NO compila tal cual (error en main al usar `parity` y
 *       el typo `parity_ccheck` vs el comentario `parity_check`). Esos
 *       errores son parte de la clase. Comenta la linea que falla para
 *       que compile.
 ****************************************************************************/
#include <stdio.h>

// Declaracion (prototipo) de la funcion: el compilador necesita saber
// que existe antes de que main la llame.
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