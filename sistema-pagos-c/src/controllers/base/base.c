#include "base.h"
#include "../../config/mensajes.h"
#include "../empleados/empleados.h"
#include "../pagos/pagos.h"
#include "../configuracion/configuracion.h"
#include "../empresa/empresa.h"
#include "../../services/menu/menu.h"

void salirMenuPrincipal()
{
    printf(SALIENDO);
}

/**
 * Menu principal
*/
void baseMenu()
{
    Menu menu;
    int cantidadOpciones = 5;
    char* nombres[] = {"Empleados", "Pagos", "Empresa", "Configuracion", "Salir"};
    void (*funciones[])() = {empleadosMenu, pagosMenu, empresaMenu, configuracionMenu, salirMenuPrincipal};

    do {
        menuDesplegar(&menu, MENU_PRINCIPAL_TITULO, nombres, funciones, cantidadOpciones);
    } while (menu.opcionActual != cantidadOpciones);
}
