#include "pagos.h"
#include "../../config/mensajes.h"
#include "../../services/menu/menu.h"
#include "../../services/pagos/pagos.h"
#include "../../services/empleados/empleados.h"
#include "../../config/commands.h"
#include "../empleados/empleados.h"

/**
 * Guarda un pago en el archivo
*/
void pagoCargarUno() {
    system(CLEAR);

    printf(INGRESAR_DATOS_PAGO);

    bool resultado = pagoGuardar();

    if(resultado) {
        printf(PAGO_GUARDADO);
    } else {
        printf(PAGO_ERROR_GUARDADO);
    }
}

/**
 * Elimina un pago del archivo
*/
void eliminarPago() {
    system(CLEAR);

    int id;
    printf(PAGO_LEER_ID);
    leerInt(&id);

    pagoEliminarPorId(id);

    printf(PAGO_ELIMINADO);
}

/**
 * Muestra todos los pagos en el archivo
*/
void verPagos() {
    system(CLEAR);

    printf(PAGOS_CARGADOS);

    pagosLeerArchivo();
}

/**
 * Muestra todos los pagos de un empleado en el archivo
*/
void verPagosDeEmpleado() {
    system(CLEAR);

    int id = desplegarSeleccionDeEmpleado();

    if(id == -1) {
        return;
    }

    printf(PAGOS_EMPLEADO, id);

    pagosLeerArchivoPorEmpleadoId(id);
}

/**
 * Muestra todos los pagos pendientes a los empleados del archivo
*/
void verPagosPendientes()
{
    system(CLEAR);

    printf(PAGOS_PENDIENTES);

    empleadoMostrarPagosPendientesDelMes();
}

/**
 *  Vuelve al menu anterior
*/
void volverAtrasPagos()
{
    printf(VOLVIENDO);
}

/**
 * Sale del programa
*/
void salirPagos()
{
    printf(SALIENDO);
}

/**
 * Despliega el menu de pagos
*/
void pagosMenu() {
    Menu menu;
    int cantidadOpciones = 7;

    char* nombres[] = {
        "Crear pago",
        "Eliminar pago", 
        "Ver pagos",
        "Ver pagos de empleado", 
        "Ver pagos pendientes", 
        "Volver", 
        "Salir"
    };

    void (*funciones[])() = {
        pagoCargarUno, 
        eliminarPago,
        verPagos, 
        verPagosDeEmpleado,
        verPagosPendientes, 
        volverAtrasPagos, 
        salirPagos
    };

    do {
        menuDesplegar(&menu, MENU_PAGOS_TITULO, nombres, funciones, cantidadOpciones);
        printf(CUALQUIER_TECLA_VOLVER);
    } while (menu.opcionActual != cantidadOpciones - 1 && menu.opcionActual != cantidadOpciones && getch()); // 

    if (menu.opcionActual == cantidadOpciones)
        exit(0);
}