#include "empleados.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../pagos/pagos.h"
#include "../pilas/pila.h"
#include "../../utils/fecha/fecha.h"
#include "../../utils/number/number.h"
#include "../../config/pathFiles.h"
#include "../direcciones/direcciones.h"
#include "../../config/mensajes.h"
#include "../archivos/archivos.h"
#include "../salarios/salarios.h"

// ------------------ Carga en memoria ------------------
Empleado empleadoCrear()
{
    Empleado empleado;
    Pila sueldo;
    inicpila(&sueldo);
    empleado.sueldo = sueldo;

    empleadoCargar(&empleado);

    empleado.activo = true;

    return empleado;
}

void empleadoCargar(Empleado *empleado)
{
    empleadoLeerId(empleado);
    empleadoLeerNombreApellido(empleado);
    empleadoLeerDireccion(empleado);
    empleadoLeerTelefono(empleado);
    empleadoLeerTipoDeSueldo(empleado);
    empleadoLeerSueldo(empleado);
    empleadoLeerFechaIngreso(empleado);
}
// ------------------ FIN Carga en memoria ------------------


// ------------------ Lectura de datos por consola ------------------
void empleadosMostrar(Empleado* empleados, int size) {
    for (int i = 0; i < size; i++) {
        if(empleados[i].activo) empleadoMostrar(empleados[i]);
    }
}

void empleadoMostrar(Empleado empleado)
{
    char fechaIngreso[40];
    fechaToString(empleado.fechaIngreso, fechaIngreso);

    float sueldo = tope(&empleado.sueldo);

    printf(SEPARADOR);
    printf(EMPLEADO_MOSTRAR_PARTE_1, empleado.id);
    puts(empleado.nombreYApellido);
    printf(EMPLEADO_MOSTRAR_PARTE_2);
    direccionMostrar(&empleado.direccion);
    mostrarSalario(sueldo, empleado);
    printf(EMPLEADO_MOSTRAR_PARTE_3, empleado.telefono, fechaIngreso);
    printf("Historial salario: ");
    mostrar(&empleado.sueldo);
    printf(SEPARADOR);
}
// ------------------ FIN Lectura de datos por consola ------------------


// ------------------ Guardado de datos en archivo ------------------
void empleadoGuardarVarios()
{
    char commander = 's';

    while (commander == 's')
    {
        empleadoGuardar();
        printf(EMPLEADO_PREGUNTAR_CARGAR);
        scanf("%c", &commander);
    }
}

bool empleadoGuardar()
{
    Empleado empleado = empleadoCrear();

    return guardarRegistro(PATH_EMPLEADOS, &empleado, sizeof(Empleado));
}
// ------------------ FIN Guardado de datos en archivo ------------------


// ------------------ Lectura de datos en archivo ------------------
Empleado empleadoLeerArchivo(int id) {
    int cantidad = cantidadRegistros(PATH_EMPLEADOS, sizeof(Empleado));
    Empleado* empleados = malloc(sizeof(Empleado) * cantidad);
    Empleado empleado;

    leerRegistros(PATH_EMPLEADOS, empleados, sizeof(Empleado));

    for (int i = 0; i < cantidad; i++) {
        if(empleados[i].activo && empleados[i].id == id) {
            empleado = empleados[i];
            break;
        }
    }

    free(empleados);

    return empleado;
}

/**
 * Lee los ids y nombres de los empleados para pasarlos a un array de strings
 * @param strings array de strings para rellenar
 * @return cantidad de empleados cargados
*/
int empleadosArchivoCargarOpcionesEnArregloStrings(char*** strings) {
    int cantidad = cantidadRegistros(PATH_EMPLEADOS, sizeof(Empleado));
    int cargados = 0;
    // Reservo memoria para el array de empleados
    Empleado* empleados = malloc(sizeof(Empleado) * cantidad);

    leerRegistros(PATH_EMPLEADOS, empleados, sizeof(Empleado));

    // Reservo memoria para el array de strings con la cantidad de empleados activos + 1 para otro
    *strings = malloc(sizeof(char) * cantidad + 1);

    for(int i = 0; i < cantidad; i++) {
        // Declaro memoria para el string
        (*strings)[i] = malloc(sizeof(char) * 100);

        if(empleados[i].activo) {
            char empleado[100];
            // Concateno el id y el nombre y apellido del empleado en un string para luego pasarlo al array de strings
            sprintf(empleado, "%d - %s", empleados[i].id, empleados[i].nombreYApellido);
            strcpy((*strings)[cargados], empleado);
            cargados++;
        }
    }

    // Limpio la memoria del array de empleados 
    free(empleados);

    return cargados;
}

/**
 * Libero la memoria del array de strings usados para opciones de empleados
*/
void liberarArregloDeStringsEmpleados(char** strings) {
    int cantidad = cantidadRegistros(PATH_EMPLEADOS, sizeof(Empleado));

    for(int i = 0; i < cantidad; i++) {
        free(strings[i]);
    }

    free(strings);
}

void empleadosLeerArchivo() {
    int cantidad = cantidadRegistros(PATH_EMPLEADOS, sizeof(Empleado));
    Empleado* empleados = malloc(sizeof(Empleado) * cantidad);

    leerRegistros(PATH_EMPLEADOS, empleados, sizeof(Empleado));

    empleadosMostrar(empleados, cantidad);

    free(empleados);
}

void empleadoLeerPorPropiedadEntera(char* name, int value, bool onlyOne) {
    int cantidad = cantidadRegistros(PATH_EMPLEADOS, sizeof(Empleado));
    Empleado* empleados = malloc(sizeof(Empleado) * cantidad);

    leerRegistros(PATH_EMPLEADOS, empleados, sizeof(Empleado));

    bool byId = strcmp(name, "id") == 0;
    bool byTelefono = strcmp(name, "telefono") == 0;
    bool bySueldo = strcmp(name, "sueldo") == 0;
    bool byAnioIngreso = strcmp(name, "anio ingreso") == 0;

    for (int i = 0; i < cantidad; i++) {
        if (!empleados[i].activo) continue;

        if (byId && empleados[i].id == value) {
            empleadoMostrar(empleados[i]);
            if(onlyOne) break;
            else continue;
        }

        if (byTelefono && empleados[i].telefono == value) {
            empleadoMostrar(empleados[i]);
            if(onlyOne) break;
            else continue;
        }

        if (bySueldo && (int) tope(&empleados[i].sueldo) == value) {
            empleadoMostrar(empleados[i]);
            if(onlyOne) break;
            else continue;
        }

        if (byAnioIngreso && empleados[i].fechaIngreso->tm_year == value) {
            empleadoMostrar(empleados[i]);
            if(onlyOne) break;
            else continue;
        }
    }

    free(empleados);
}

void empleadoLeerPorPropiedadString(char* name, char* value, bool onlyOne) {
    int cantidad = cantidadRegistros(PATH_EMPLEADOS, sizeof(Empleado));
    Empleado* empleados = malloc(sizeof(Empleado) * cantidad);

    leerRegistros(PATH_EMPLEADOS, empleados, sizeof(Empleado));

    bool byTipoSueldo = strcmp(name, "tipo sueldo") == 0;
    bool byJornada = strcmp(name, "jornada") == 0;

    for (int i = 0; i < cantidad; i++) {
        if (!empleados[i].activo) continue;

        if (byTipoSueldo && strcmp(empleados[i].tipoSueldo, value) == 0) {
            empleadoMostrar(empleados[i]);
            if(onlyOne) break;
            else continue;
        }

        if (byJornada && empleados[i].jornada == value) {
            empleadoMostrar(empleados[i]);
            if(onlyOne) break;
            else continue;
        }
    }

    free(empleados);
}

void empleadoLeerPorTelefonoConsola() {
    int value;
    printf(EMPLEADO_LEER_TELEFONO);
    leerInt(&value);
    empleadoLeerPorPropiedadEntera("telefono", value, false);
}

void empleadoLeerPorSueldoConsola() {
    int value;
    printf(EMPLEADO_LEER_SUELDO);
    leerInt(&value);
    empleadoLeerPorPropiedadEntera("sueldo", value, false);
}

void empleadoLeerPorAnioIngresoConsola() {
    int value;
    printf(EMPLEADO_LEER_ANIO_INGRESO);
    leerInt(&value);

    empleadoLeerPorPropiedadEntera("anio ingreso", value, false);
}

void empleadoLeerPorIdConsola() {
    int value;
    printf(EMPLEADO_LEER_ID);
    leerInt(&value);

    empleadoLeerPorPropiedadEntera("id", value, true);
}

void empleadoLeerPorTipoSueldoConsola() {
    char tipoSueldo[20];
    printf(EMPLEADO_LEER_TIPO_SUELDO);
    leerString(tipoSueldo, true);
    empleadoLeerPorPropiedadString("tipo sueldo", tipoSueldo, false);
}

void empleadoLeerPorJornadaConsola() {
    char jornada[20];
    printf(EMPLEADO_LEER_JORNADA);
    leerString(jornada, true);
    empleadoLeerPorPropiedadString("jornada", jornada, false);
}

// ------------------ FIN Lectura de datos en archivo ------------------

// ------------------ Eliminacion de datos en archivo ------------------
void empleadoEliminarPorId(int id) {
    const cantidad = cantidadRegistros(PATH_EMPLEADOS, sizeof(Empleado));
    Empleado* empleados = malloc(sizeof(Empleado) * cantidad);

    leerRegistros(PATH_EMPLEADOS, empleados, sizeof(Empleado));

    for (int i = 0; i < cantidad; i++) {
        if (empleados[i].id == id && empleados[i].activo) {
            empleados[i].activo = false;
            modificarRegistro(PATH_EMPLEADOS, &empleados[i], sizeof(Empleado), i);
            break;
        }
    }

    free(empleados);
}
// ------------------ FIN Eliminacion de datos en archivo ------------------

// ------------------ Modificacion de datos en archivo ------------------
void empleadoModificarPorId(int id) {
    int cantidad = cantidadRegistros(PATH_EMPLEADOS, sizeof(Empleado));
    Empleado* empleados = malloc(sizeof(Empleado) * cantidad);

    leerRegistros(PATH_EMPLEADOS, empleados, sizeof(Empleado));

    for (int i = 0; i < cantidad; i++) {
        if (empleados[i].id == id && empleados[i].activo) {
            empleadoCargar(&empleados[i]);
            empleados[i].id = id;
            modificarRegistro(PATH_EMPLEADOS, &empleados[i], sizeof(Empleado), i);
            break;
        }
    }

    free(empleados);
}

void empleadoModificarPorIdManual(int id, Empleado* empleado) {
    int cantidad = cantidadRegistros(PATH_EMPLEADOS, sizeof(Empleado));
    Empleado* empleados = malloc(sizeof(Empleado) * cantidad);

    leerRegistros(PATH_EMPLEADOS, empleados, sizeof(Empleado));

    for (int i = 0; i < cantidad; i++) {
        if (empleados[i].id == id && empleados[i].activo) {
            empleados[i].id = id;
            modificarRegistro(PATH_EMPLEADOS, empleado, sizeof(Empleado), i);
            break;
        }
    }

    free(empleados);
}
// ------------------ FIN Modificacion de datos en archivo ------------------

// ------------------ Funcionalidades extra ------------------
void empleadoModificarPorcentajeSalarioTodos(int porcentaje) {
    int cantidad = cantidadRegistros(PATH_EMPLEADOS, sizeof(Empleado));
    Empleado* empleados = malloc(sizeof(Empleado) * cantidad);

    leerRegistros(PATH_EMPLEADOS, empleados, sizeof(Empleado));

    for (int i = 0; i < cantidad; i++) {
        float sueldo = tope(&empleados[i].sueldo);
        apilar(&empleados[i].sueldo, sueldo + (sueldo * porcentaje / 100));
    }

    modificarRegistros(PATH_EMPLEADOS, empleados, sizeof(Empleado), 0, cantidad);

    free(empleados);
}

void empleadoMostrarPagosPendientesDelMes() {
    int cantidad = cantidadRegistros(PATH_EMPLEADOS, sizeof(Empleado));
    Empleado* empleados = malloc(sizeof(Empleado) * cantidad);

    leerRegistros(PATH_EMPLEADOS, empleados, sizeof(Empleado));

    for (int i = 0; i < cantidad; i++) {
        if (empleados[i].activo) {
            float montoPagado = pagosEsteMesEmpleadoId(empleados[i].id);
            float sueldo = tope(&empleados[i].sueldo);
            float sueldoConBonus = calcularSalarioConBonus(sueldo, empleados[i].fechaIngreso);

            float montoPagadoRedondeo = round(montoPagado * 100.0) / 100.0;
            float sueldoConBonusRedondeo = round(sueldoConBonus * 100.0) / 100.0;
            if (montoPagadoRedondeo < sueldoConBonusRedondeo) {
                printf(EMPLEADO_MOSTRAR_PAGOS_PENDIENTES, empleados[i].id, empleados[i].nombreYApellido, sueldoConBonus, montoPagado, sueldoConBonus - montoPagado);
            }
        }
    }

    free(empleados);
}
// ------------------ FIN Funcionalidades extra ------------------

// ------------------ Carga de datos individuales por consola ------------------
void empleadoLeerId(Empleado *empleado)
{
    int id = cantidadRegistros(PATH_EMPLEADOS, sizeof(Empleado)) + 1;
    empleado->id = id;
}

void empleadoLeerNombreApellido(Empleado *empleado)
{
    printf(EMPLEADO_LEER_NOMBRE_APELLIDO);
    leerString(empleado->nombreYApellido, true);
}

void empleadoLeerDireccion(Empleado *empleado)
{
    printf(EMPLEADO_LEER_DIRECCION);
    direccionCargar(&empleado->direccion);
}

void empleadoLeerTelefono(Empleado *empleado)
{
    printf(EMPLEADO_LEER_TELEFONO);
    leerInt(&empleado->telefono);
}

void empleadoLeerTipoDeSueldo(Empleado *empleado)
{
    printf(EMPLEADO_LEER_TIPO_SUELDO);
    leerString(empleado->tipoSueldo, true);
}

void empleadoLeerSueldo(Empleado *empleado)
{
    float sueldo;
    printf(EMPLEADO_LEER_SUELDO);
    leerFloat(&sueldo);
    apilar(&empleado->sueldo, sueldo);
}

void empleadoLeerFechaIngreso(Empleado *empleado)
{
    printf(EMPLEADO_LEER_FECHA_INGRESO);
    leerFecha(&empleado->fechaIngreso);
}
// ------------------ FIN Carga de datos individuales por consola ------------------
