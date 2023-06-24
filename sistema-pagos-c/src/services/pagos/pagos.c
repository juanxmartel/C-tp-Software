#include "pagos.h"
#include "stdio.h"
#include "../../utils/number/number.h"
#include "../../utils/string/string.h"
#include "../../utils/fecha/fecha.h"
#include "../archivos/archivos.h"
#include "../../config/mensajes.h"
#include "../../config/pathFiles.h"
#include "../empleados/empleados.h"
#include "../empresa/empresa.h"
#include "../../controllers/empleados/empleados.h"

// ------------------ Carga en memoria ------------------
Pago pagoCrear()
{
    Pago pago;

    pagoCargar(&pago);

    pago.activo = true;

    return pago;
}

void pagoCargar(Pago *pago)
{
    pagoLeerId(pago);
    pagoLeerIdEmpleado(pago);

    if(pago->idEmpleado == -1) {
        return;
    }

    pagoLeerMonto(pago);
    fechaNow(&pago->fecha);
}
// ------------------ FIN Carga en memoria ------------------

// ------------------ Lectura de datos por consola ------------------
void pagoMostrar(Pago pago)
{
    char fecha[11];
    fechaToString(pago.fecha, fecha);

    printf(SEPARADOR);
    printf(PAGO_MOSTRAR, pago.id, pago.idEmpleado, pago.monto, fecha);
    printf(SEPARADOR);
}

void pagosMostrar(Pago* pagos, int size) {
    for (int i = 0; i < size; i++) {
        if(pagos[i].activo) pagoMostrar(pagos[i]);
    }
}
// ------------------ FIN Lectura de datos por consola ------------------

// ------------------ Guardado de datos en archivo ------------------
bool pagoGuardar() {
    Pago pago = pagoCrear();

    if(pago.idEmpleado == -1) {
        return false;
    }

    modificarMontoEmpresa(-pago.monto);

    return guardarRegistro(PATH_PAGOS, &pago, sizeof(Pago));
}

void pagoGuardarVarios() {
    char commander = 's';

    while (commander == 's')
    {
        pagoGuardar();
        printf(PAGO_PREGUNTAR_CARGAR);
        scanf("%c", &commander);
    }
}
// ------------------ FIN Guardado de datos en archivo ------------------

// ------------------ Lectura de datos en archivo ------------------
void pagosLeerArchivo() {
    int cantidad = cantidadRegistros(PATH_PAGOS, sizeof(Pago));
    Pago* pagos = malloc(sizeof(Pago) * cantidad);

    leerRegistros(PATH_PAGOS, pagos, sizeof(Pago));

    pagosMostrar(pagos, cantidad);

    free(pagos);
}

void pagosLeerArchivoPorEmpleadoId(long empleadoId) {
    int cantidad = cantidadRegistros(PATH_PAGOS, sizeof(Pago));
    Pago* pagos = malloc(sizeof(Pago) * cantidad);

    leerRegistros(PATH_PAGOS, pagos, sizeof(Pago));

    for (int i = 0; i < cantidad; i++) {
        if (pagos[i].idEmpleado == empleadoId && pagos[i].activo) {
            pagoMostrar(pagos[i]);
        }
    }

    free(pagos);
}

void pagoEliminarPorId(int id) {
    const cantidad = cantidadRegistros(PATH_PAGOS, sizeof(Pago));
    Pago* pagos = malloc(sizeof(Pago) * cantidad);

    leerRegistros(PATH_PAGOS, pagos, sizeof(Pago));

    for (int i = 0; i < cantidad; i++) {
        if (pagos[i].id == id && pagos[i].activo) {
            pagos[i].activo = false;
            modificarMontoEmpresa(+pagos[i].monto);
            modificarRegistro(PATH_PAGOS, &pagos[i], sizeof(Pago), i);
            break;
        }
    }

    free(pagos);
}

/**
 * Devuelve el monto del pago del mes actual del empleado. Si no se hizo el pago, devuelve 0.
*/
float pagosEsteMesEmpleadoId(unsigned long empleadoId) {
    float monto = 0;
        
    int cantidad = cantidadRegistros(PATH_PAGOS, sizeof(Pago));
    struct tm fechaActual;
    fechaNow(&fechaActual);

    Pago* pagos = malloc(sizeof(Pago) * cantidad);

    leerRegistros(PATH_PAGOS, pagos, sizeof(Pago));

    for (int i = 0; i < cantidad; i++) {
        // Verifico que el pago sea del empleado y que sea del mes actual
        if (pagos[i].idEmpleado == empleadoId && pagos[i].activo) {
            if (pagos[i].fecha->tm_mon == fechaActual.tm_mon && pagos[i].fecha->tm_year == fechaActual.tm_year) {
                monto += pagos[i].monto;
            }
        }
    }

    free(pagos);

    return monto;
} 
// ------------------ FIN Lectura de datos en archivo ------------------

// ------------------ Lectura individual propiedades -------------------
void pagoLeerId(Pago* pago) {
    int id = cantidadRegistros(PATH_PAGOS, sizeof(Pago)) + 1;
    pago->id = id;
}

void pagoLeerIdEmpleado(Pago* pago) {
    printf(PAGO_LEER_EMPLEADO_ID);
    int idEmpleado = desplegarSeleccionDeEmpleado();
    pago->idEmpleado = idEmpleado;
}

void pagoLeerMonto(Pago* pago) {
    printf(PAGO_LEER_MONTO);
    leerFloat(&pago->monto);
}
// ------------------ FIN Lectura individual propiedades -------------------