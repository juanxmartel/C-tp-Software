#include "array.h"

char** cargarArrayDeStrings() {
    char** matriz = malloc(sizeof(char*) * 10);
    for(int i = 0; i < 10; i++) {
        matriz[i] = malloc(sizeof(char) * 50);
    }

    return matriz;
}

void borrarArrayDeStrings(char** matriz, int dimensionX) {
    for(int i = 0; i < dimensionX; i++) {
        free(matriz[i]);
    }
    free(matriz);
}