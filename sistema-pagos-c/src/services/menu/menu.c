#include "menu.h"
#include <stdio.h>
#include <conio.h>
#include "../../config/teclas.h"
#include "../../config/commands.h"

/**
 * Esta funcion se encarga del flujo completo para desplegar y mostrar un menu por consola
 * @param nombre El nombre del menu
 * @param nombres Los nombres de las opciones del menu
 * @param funciones Las funciones que se ejecutaran al seleccionar una opcion. Deben tener el mismo orden que los nombres. Son callbacks
 * @param n_opciones La cantidad de opciones que tiene el menu
*/
void menuDesplegar(Menu* menu, char* nombre, char* nombres[], void (*funciones[])(), int n_opciones)
{
    // Reservo memoria para las opciones
    Opcion* opciones = malloc(sizeof(Opcion) * n_opciones);

    // Creo las opciones
    menuCrearOpciones(opciones, n_opciones, nombres, funciones);

    // Creo el menu
    menuCrear(menu, nombre, opciones, n_opciones);
    // Ejecuto el listener del menu para mover entre opciones
    menuMoverse(menu, NULL);
    // Ejecuto la opcion seleccionada
    menuEjecutar(menu);

    // Libero la memoria
    free(opciones);
}

void menuCrear(Menu* menu, char* nombre, Opcion* opciones, int n_opciones)
{
    // Inicializo el menu
    menu->nombre = nombre;
    menu->opciones = opciones;
    menu->n_opciones = n_opciones;
    menu->opcionActual = 1;
}

/**
 * Muestra el menu por consola
*/
void menuMostrar(Menu* menu)
{
    printf("%s\n", menu->nombre);

    // Recorro las opciones del menu y las muestro. Cuando llego a la opcion actual, la muestro entre corchetes para destacar
    for (int i = 0; i < menu->n_opciones; i++)
    {
        Opcion opcion = menu->opciones[i];
        if (i + 1 == menu->opcionActual)
            printf("  [%s]\n", opcion.nombre);
        else
            printf("  %s\n", opcion.nombre);
    }
}

/**
 * Escucha las teclas presionadas por el usuario para moverse entre las opciones del menu.
 * Ejecuta un callback cuando se presiona una tecla usado para mostrar informacion adicional. (Como el caso del menu horizontal)
*/
void menuMoverse (Menu* menu, void (*callbackTecla)(int opcionalActual, int numero))
{
    int opcion = menu->opcionActual;
    int tecla = 0;

    while(tecla != ENTER)
    {
        system(CLEAR);
        menuMostrar(menu);

        tecla = getch();

        if(tecla == FLECHA_ARRIBA)
        {
            opcion--;
            if(opcion < 1)
                opcion = menu->n_opciones;
        }
        else if(tecla == FLECHA_ABAJO)
        {
            opcion++;
            if(opcion > menu->n_opciones)
                opcion = 1;
        }

        if(callbackTecla) callbackTecla(opcion, tecla);

        menu->opcionActual = opcion;
    }
}

/**
 * Ejectua la funcion de la opcion seleccionada
*/
void menuEjecutar(Menu* menu)
{
    Opcion opcion = menu->opciones[menu->opcionActual - 1];

    if(opcion.funcion != NULL) {
        opcion.funcion();
    }
}

/**
 * Crea las opciones del menu a partir de los nombres y las funciones
*/
void menuCrearOpciones(Opcion* opciones, int n_opciones, char* nombres[], void (*funciones[]))
{
    for (int i = 0; i < n_opciones; i++)
    {
        Opcion opcion;
        // Si hay funciones, las asigno. Si no, asigno NULL. Debido a que sino va a dar error al acceder a un indice de un array NULL
        if(funciones != NULL) menuCrearOpcion(&opcion, nombres[i], funciones[i]);
        else menuCrearOpcion(&opcion, nombres[i], NULL);
        opciones[i] = opcion;
    }
}

/**
 * Crea una opcion del menu a partir de un nombre y una funcion
*/
void menuCrearOpcion(Opcion* opcion, char* nombre, void (*funcion)())
{
    opcion->nombre = nombre;
    opcion->funcion = funcion;
}
