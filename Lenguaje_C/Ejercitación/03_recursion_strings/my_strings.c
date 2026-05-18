#include <stdio.h>

int main() {
    char buffer[5];
    char demon[5] = {'1','3','4','a','2'};
    int i;

    printf("Enter a string: \n");
    fflush(stdin);
    fgets(buffer, 5, stdin);

    for(i=0; i<5; i++) {
        printf("%c ", buffer[i]);
    }
    printf("\n");

    // Si es que tomo con '\0' 
    printf("%s\n", buffer);

    // Intento comparar con el demonio
    printf("%s\n", demon);

    // Como sería mi propiro printf(%s)
    for(i=0; demon[i] != '\0'; i++) {
        printf("%c", demon[i]);
    }

    return(0);
}