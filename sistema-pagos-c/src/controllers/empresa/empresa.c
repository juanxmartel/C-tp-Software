#include "empresa.h"
#include "../../config/mensajes.h"
#include "../../services/menu/menu.h"
#include "../../services/empresa/empresa.h"

/**
 * Muestra la informacion obtenida en el archivo de empresa
*/
void mostrarInfoEmpresa() {
    Empresa empresa;
    obtenerInfoEmpresa(&empresa);

    mostrarEmpresa(empresa);
}

/**
 * Permite modificar la informacion de la empresa
*/
void modificarInfoEmpresa() {
    Empresa empresa;
    obtenerInfoEmpresa(&empresa);

    modificarEmpresa(&empresa);
}

/**
 * Vuelve al menu anterior
*/
void volverAtrasEmpresa()
{
    printf(VOLVIENDO);
}

/**
 * Sale del programa
*/
void salirEmpresa()
{
    printf(SALIENDO);
}

/**
 * Menu de empresa
*/
void empresaMenu() {
    Menu menu;
    int cantidadOpciones = 4;

    char* nombres[] = {
        "Ver informacion de empresa",
        "Modificar informacion de empresa",
        "Volver", 
        "Salir"
    };

    void (*funciones[])() = {
        mostrarInfoEmpresa, 
        modificarInfoEmpresa,
        volverAtrasEmpresa, 
        salirEmpresa
    };

    do {
        menuDesplegar(&menu, MENU_PAGOS_TITULO, nombres, funciones, cantidadOpciones);
        printf(CUALQUIER_TECLA_VOLVER);
    } while (menu.opcionActual != cantidadOpciones - 1 && menu.opcionActual != cantidadOpciones && getch()); // 

    if (menu.opcionActual == cantidadOpciones)
        exit(0);
}