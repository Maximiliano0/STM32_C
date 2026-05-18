#include "my_lib.h"

// Variables globales publicas
char token[_MAXTOKEN] = "jugador";

// Variables globales privadas

// Definiciones de funciones
int separar_palabras(char *poema, char *buffer){
    static int pindice = 0;
    int bindice = 0;

    // Pregunto no es el  '\0' o es una letra
    while(poema[pindice] != '\0' && 
        ((poema[pindice]>='a' && poema[pindice]<='z') || 
        (poema[pindice]>='A' && poema[pindice]<='Z')) ){
            
        buffer[bindice] = poema[pindice];
        pindice++;
        bindice++;
    }
    buffer[bindice] = '\0';
    if(poema[pindice] == '\0') return 0;
    else{
        pindice++;
        return 1;
    }
}