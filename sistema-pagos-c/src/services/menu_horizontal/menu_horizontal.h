#pragma once

#define Menu_Horizontal struct _Menu_Horizontal

struct _Menu_Horizontal{
    char titulo[50];
    char opciones[101][50];
    int opcionActual;
    int maxOpciones;
    char* stringVinculado;
};

Menu_Horizontal construirMenuHorizontal(char* titulo, char** opciones, int maxOpciones, int opcionActual);
void cargarOpciones(Menu_Horizontal* menu, char **opciones, int validos);
void moverIzquierda(Menu_Horizontal* menuHorizontal);
void moverDerecha(Menu_Horizontal* menuHorizontal);
char* mostrarTextoMenuHorizontal(Menu_Horizontal menuHorizontal);
void vincularString(Menu_Horizontal* menuHorizontal, char* string);
void moverOpcionMenuHorizontal(Menu_Horizontal* menu, int opcionActual, int tecla);