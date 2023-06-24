#include "avisos.h";

void mostrarAviso(char* aviso) {
    int length = strlen(aviso);

    printf("\n");
    mostrarParteSuperiorAviso(length);
    mostrarParteMensajeAviso(aviso);
    mostrarParteInferiorAviso(length);
}

void mostrarParteSuperiorAviso(int length) {
    mostrarParteExtremaAviso(length);
    mostrarParteIntermediaAviso(length);    
}

void mostrarParteInferiorAviso(int length) {
    mostrarParteIntermediaAviso(length);
    mostrarParteExtremaAviso(length);
}

void mostrarParteExtremaAviso(int length) {
    char relleno[] = "###############################################################################";

    printf("%*.*s\n", length + 6, length + 6, relleno);
}

void mostrarParteIntermediaAviso(int length) {
    char rellenoEspacio[] = "                                                                            ";

    printf("#%*.*s#\n", length + 4, length + 4, rellenoEspacio);
}

void mostrarParteMensajeAviso(char* aviso) {
    printf("#  %s  #\n", aviso);
}