#pragma once

#define Menu struct _Menu
#define Opcion struct _Opcion

struct _Menu {
    char *nombre;
    Opcion *opciones;
    int opcionActual;
    int n_opciones;
};

struct _Opcion {
    char *nombre;
    void (*funcion)(); // callback a ejecutar
};

void menuDesplegar(Menu* menu, char* nombre, char* nombres[], void (*funciones[])(), int n_opciones);
void menuCrear(Menu* menu, char* nombre, Opcion* opciones, int n_opciones);
void menuMostrar(Menu* menu);
void menuMoverse (Menu* menu, void (*callbackTecla)(int opcionalActual, int numero));

void menuCrearOpciones(Opcion* opciones, int n_opciones, char* nombres[], void (*funciones[]));
void menuCrearOpcion(Opcion* opcion, char* nombre, void (*funcion)());
void menuEjecutar(Menu* menu);