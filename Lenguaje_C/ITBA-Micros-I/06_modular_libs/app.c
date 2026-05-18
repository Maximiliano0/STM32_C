#include "my_lib.h"

// Variables globales publicas
extern char token[_MAXTOKEN];

// Variables globales publicas
char poema[] = "Tenue rey, sesgo alfil, encarnizada reina,\n"
               "torre directa y peon ladino\n"
               "sobre lo negro y blanco del camino\n"
               "buscan y libran su batalla armada.\n"
               "\n"
               "No saben que la mano senalada\n"
               "del jugador gobierna su destino,\n"
               "no saben que un rigor adamantino\n"
               "sujeta su albedrio y su jornada.\n"
               "\n"
               "Tambien el jugador es prisionero\n"
               "(la sentencia es de Omar) de otro tablero\n"
               "de negras noches y de blancos dias.\n"
               "\n"
               "Dios mueve al jugador, y este, la pieza.\n"
               "Que Dios detras de Dios la trama empieza\n"
               "de polvo y tiempo y sueno y agonia?\n";

// Main function
int main(void){
    int cant, index, acc=0, end=1;
    char buffer[_MAXTOKEN];

    
    while(end){
        // Separar Palabras (funcion)
        end = separar_palabras(poema, buffer);
        // Veo si es el token jugador
        if(strcmp(buffer, token) == 0) acc++;
        //printf("acc: %d\n", acc);
    }

    // Imprimir resultado
    printf("La palabra '%s' aparece %d veces en el poema.\n", token, acc);

    return 0;
}
