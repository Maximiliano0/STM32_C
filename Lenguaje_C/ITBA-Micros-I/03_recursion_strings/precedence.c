// Librerías
#include <stdlib.h>
#include <stdio.h>

int main (void){
    int y = 4;
    int k = 10;
    int x; 
    char letra = 'a';

    // int y = 4, k = 10, x; 
    float y2 = 4, k2 = 10, x2;

    // Operador ()++
    printf("%c tamano de un char: %d\n", letra, sizeof(letra));
    letra++;
    printf("%c tamano de un char ??: %d\n", letra, sizeof(letra));
    letra+=2;
    printf("%c tamano de un char ??: %d\n", letra, sizeof(letra));

    getc(stdin);

    // Sin problemas
    x = k * y + 2; 
    printf("Sin parentesis x = %d\n", x);

    getc(stdin);
    
    x = (k * y) + 2; 
    printf("Con parentesis x = %d\n", x);

    getc(stdin);
    
    // Con problemas
    x = y / 2 * k;
    printf("Division sin parentesis x = %d\n", x);

    getc(stdin);

    // Corregido pero con casteo implicito
    x = y / (2 * k);
    printf("Division con parentesis x = %d\n", x);

    getc(stdin);

    // Corregido con casteo explicito
    x2 = y2 / (2 * k2);
    printf("Division con parentesis y casteo explicito x = %.2f\n", x2);

    getc(stdin);

    // Corrigiendo todo
    x2 = ((float) y) / (2 * k);
    printf("Corrigiendo todo x = %.2f\n", x2);

    getc(stdin);

    return 0;
}