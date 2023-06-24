#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu_horizontal.h"
#include "../../config/teclas.h"

/**
 * Contruye un menu horizontal con las opciones pasadas por parametro
*/
Menu_Horizontal construirMenuHorizontal(char* titulo, char** opciones, int maxOpciones, int opcionActual) {
    Menu_Horizontal menu;
    strcpy(menu.titulo, titulo);
    cargarOpciones(&menu, opciones, maxOpciones);
    menu.opcionActual = opcionActual;
    menu.maxOpciones = maxOpciones;

    return menu;
}

/** 
 * Se carga el array de opciones del menu con las opciones pasadas por parametro
*/
void cargarOpciones(Menu_Horizontal* menu, char **opciones, int validos) {
    for(int i = 0; i < validos; i++) {
        strcpy(menu->opciones[i], opciones[i]);
    }
}

/**
 * Mueve la opcion actual del menu a la izquierda y cambia el string vinculado al texto del menu actual con la opcion seleccionada
*/
void moverIzquierda(Menu_Horizontal* menuHorizontal) {
    if(menuHorizontal->opcionActual > 1)  {
        menuHorizontal->opcionActual--;
        char* texto = mostrarTextoMenuHorizontal(*menuHorizontal);
        strcpy(menuHorizontal->stringVinculado, texto);
        free(texto);
    }
}

/**
 * Muve la opcion actual del menu a la derecha y cambia el string vinculado al texto del menu actual con la opcion seleccionada
*/
void moverDerecha(Menu_Horizontal* menuHorizontal) {
    if(menuHorizontal->opcionActual < menuHorizontal->maxOpciones)  {
        menuHorizontal->opcionActual++;
        char* texto = mostrarTextoMenuHorizontal(*menuHorizontal);
        strcpy(menuHorizontal->stringVinculado, texto);
        free(texto);
    }
}

/**
 * Muestra el texto del menu actual con la opcion seleccionada
*/
char* mostrarTextoMenuHorizontal(Menu_Horizontal menuHorizontal) {
    char* resultado = malloc(sizeof(char) * 50);
    int opcionActual = menuHorizontal.opcionActual;

    strcpy(resultado, menuHorizontal.titulo);
    if(opcionActual > 1) strcat(resultado, "< ");
    strcat(resultado, menuHorizontal.opciones[opcionActual - 1]);
    if(opcionActual < menuHorizontal.maxOpciones) strcat(resultado, " >");

    return resultado;
}

/**
 * Vincula una direccion de memoria de un string para que se modifique al modificar el menu
*/
void vincularString(Menu_Horizontal* menuHorizontal, char* string) {
    menuHorizontal->stringVinculado = string;

    strcpy(menuHorizontal->stringVinculado, mostrarTextoMenuHorizontal(*menuHorizontal));
}


/**
 * Mueve la opcion actual del menu horizontal segun la tecla presionada
*/
void moverOpcionMenuHorizontal(Menu_Horizontal* menu, int opcionActual, int tecla) {
    if(tecla == FLECHA_IZQUIERDA) {
        moverIzquierda(menu);
        return;
    }
    if(tecla == FLECHA_DERECHA) {
        moverDerecha(menu);
        return;
    }
}