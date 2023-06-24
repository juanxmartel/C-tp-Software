#include "../../config/mensajes.h"
#include "../../services/empleados/empleados.h"
#include "../../services/menu/menu.h"
#include "../../services/configuracion/configuracion.h"
#include "../../services/menu_horizontal/menu_horizontal.h"
#include "./configuracion.h"
#include "../../utils/array/array.h"
#include "string.h";

// Opciones del menu horizontal
const char *opcionesFormatoFecha[] = {"dd/mm/aaaa", "mm/dd/aaaa", "aaaa/mm/dd", "letras"};
const char *opcionesFormatoNumeros[] = {"numeros", "letras"};
char *numeros[101]; // Los numeros del 1 al 100 para los porcentajes

// Se crea un array de menus horizontales para poder acceder a ellos desde cualquier funcion
Menu_Horizontal menusHorizontal[4];

/**
 * Guarda la configuracion en el archivo en base a las opciones seleccionadas en el menu
*/
void guardarConfiguracionMenu() {
    Configuracion configuracion;
    configuracion.formatoFechas = menusHorizontal[0].opcionActual - 1;
    configuracion.formatoNumeros = menusHorizontal[1].opcionActual - 1;
    configuracion.porcentajeAntiguedad = menusHorizontal[2].opcionActual - 1;
    configuracion.porcentajeImpuestos = menusHorizontal[3].opcionActual - 1;
    guardarConfiguracion(&configuracion);
}

/**
 * Menu de configuracion
*/
void configuracionMenu() {
    Menu menu;
    int cantidadOpciones = 5;

    llenarArrayDeNumeros(numeros, 101); // Se llena el array de numeros del 1 al 100

    // Se lee la configuracion del archivo
    Configuracion configuracion;
    bool configuracionLeida = obtenerConfiguracion(&configuracion);

    // Se contruyen los menus horizontales con sus opciones en base a la configuracion leida
    menusHorizontal[0] = construirOpcionFormatoFecha(configuracionLeida ? configuracion.formatoFechas + 1 : 1);
    menusHorizontal[1] = construirOpcionFormatoNumeros(configuracionLeida ? configuracion.formatoNumeros + 1 : 1);
    menusHorizontal[2] = construirOpcionPorcentajeAntiguedad(configuracionLeida ? configuracion.porcentajeAntiguedad + 1 : 1);
    menusHorizontal[3] = construirOpcionPorcentajeImpuestos(configuracionLeida ? configuracion.porcentajeImpuestos + 1 : 1);

    /* Se vinculan los strings de las opciones con los nombres de los textos de los menus horizontales
     La vinculacion hace que cuando se cambie de opcion en el menu horizontal, 
     se cambie el texto del menu debido a que se vincula la direccion de memoria del string 
     con el texto del menu horizontal y el menu esta apuntando a esa direccion de memoria
    */
    char** nombres = cargarArrayDeStrings();
    vincularString(&menusHorizontal[0], nombres[0]);
    vincularString(&menusHorizontal[1], nombres[1]);
    vincularString(&menusHorizontal[2], nombres[2]);
    vincularString(&menusHorizontal[3], nombres[3]);
    strcpy(nombres[4], "Guardar y volver al menu principal");
    
    do {
        // Se crea un array de opciones para poder pasarle al menu
        Opcion* opciones = malloc(sizeof(Opcion) * cantidadOpciones);

        // Se llena el array de opciones con las opciones de los menus horizontales
        menuCrearOpciones(opciones, cantidadOpciones, nombres, NULL);

        // Se crea el menu con las opciones
        menuCrear(&menu, "Configuracion", opciones, cantidadOpciones);

        // Se muestran los menus horizontales en el menu y se le pasa la funcion para moverse entre las opciones horizontales
        menuMoverse(&menu, mover);

        free(opciones);
    } while (menu.opcionActual != cantidadOpciones && getch()); //

    // Se borran los arrays de strings
    borrarArrayDeStrings(nombres, 10);
    borrarArrayDeStrings(numeros, 101);

    // Si se selecciono la ultima opcion, se guarda la configuracion
    if(menu.opcionActual == cantidadOpciones) {
        guardarConfiguracionMenu();
    }
}

/**
 * Se rellena el array de numeros del 1 al 100 en formato string con un % al final
*/
void llenarArrayDeNumeros(char* numeros[], int validos) {
    for(int i = 0; i < validos; i++){
        numeros[i] = malloc(sizeof(char) * 5);
        sprintf(numeros[i], "%d", i);
        strcat(numeros[i], "%");
    }
}

/**
 * @function 
 * Se crea el menu horizontal con las opciones de antiguedad.
 * @param opcionActual La opcion actual seleccionada
*/
Menu_Horizontal construirOpcionPorcentajeAntiguedad(int opcionActual) {
    Menu_Horizontal menu = construirMenuHorizontal(
        "Porcentaje bonus antiguedad salarios: ", 
        numeros, 
        101, 
        opcionActual
    );

    return menu;
}

/**
 * Se crea el menu horizontal con las opciones de impuestos
 * @param opcionActual La opcion actual seleccionada
*/
Menu_Horizontal construirOpcionPorcentajeImpuestos(int opcionActual) {
    Menu_Horizontal menu = construirMenuHorizontal(
        "Porcentaje impuestos salarios: ", 
        numeros, 
        101, 
        opcionActual
    );

    return menu;
}

/**
 * Se crea el menu horizontal con las opciones de formato de fecha
 * @param opcionActual La opcion actual seleccionada
*/
Menu_Horizontal construirOpcionFormatoFecha(int opcionActual) {
    Menu_Horizontal menu = construirMenuHorizontal(
        "Cambiar formato fecha: ", 
        opcionesFormatoFecha, 
        4, 
        opcionActual
    );

    return menu;
}

/**
 * Se crea el menu horizontal con las opciones de formato de numeros
 * @param opcionActual La opcion actual seleccionada
*/
Menu_Horizontal construirOpcionFormatoNumeros(int opcionActual) {
    Menu_Horizontal menu = construirMenuHorizontal(
        "Cambiar formato de numeros: ", 
        opcionesFormatoNumeros, 
        2, 
        opcionActual
    );

    return menu;
}

/**
 * Funcion para pasar como callback que vincula el string de la opcion con el nombre del texto del menu horizontal
*/
void mover(int opcionActual, int tecla) {
    moverOpcionMenuHorizontal(&menusHorizontal[opcionActual - 1], opcionActual, tecla);
}