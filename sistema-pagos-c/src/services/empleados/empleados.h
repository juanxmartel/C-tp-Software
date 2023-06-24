#pragma once

#include "../direcciones/direcciones.h"
#include "../pilas/pila.h"
#include <stdbool.h>
#include "time.h"

#define Empleado struct _Empleado

struct _Empleado
{
    unsigned long id;//numero que identifica al empleado
    char nombreYApellido[70];//nombre del sujeto
    Direccion direccion;//direccion del empleado
    unsigned long telefono;//telefono del empleado
    char tipoSueldo[40];//los distintos tipos de sueldo que hay mensual, horas
    char jornada[40];//las distintas jornadas de trabajo que hay parcial, completa
    Pila sueldo; //cantidad de dinero que cobra
    struct tm fechaIngreso[20]; //fecha de ingreso a la empresa
    bool activo;
};

Empleado empleadoCrear();
void empleadoCargar(Empleado *empleado);
void empleadoLeerId(Empleado *empleado);
void empleadoLeerNombreApellido(Empleado *empleado);
void empleadoLeerDireccion(Empleado *empleado);
void empleadoLeerTelefono(Empleado *empleado);
void empleadoLeerTipoDeSueldo(Empleado *empleado);
void empleadoLeerSueldo(Empleado *empleado);
void empleadoLeerFechaIngreso(Empleado *empleado);
void empleadoMostrar(Empleado empleado);
void empleadosMostrar(Empleado* empleados, int size);
void empleadoGuardarVarios();
bool empleadoGuardar();
void empleadoLeerPorPropiedadEntera(char* name, int value, bool onlyOne);
void empleadoLeerPorPropiedadString(char* name, char* value, bool onlyOne);
void empleadoLeerPorTelefonoConsola();
void empleadoLeerPorSueldoConsola();
void empleadoLeerPorTipoSueldoConsola();
void empleadoLeerPorAnioIngresoConsola();
void empleadoLeerPorJornadaConsola();
void empleadosLeerArchivo();
void empleadoEliminarPorId(int id);
void empleadoModificarPorId(int id);
void empleadoModificarPorIdManual(int id, Empleado* empleado);
void empleadoModificarPorcentajeSalarioTodos(int porcentaje);
int empleadosArchivoCargarOpcionesEnArregloStrings(char*** strings);
void liberarArregloDeStringsEmpleados(char** strings);
Empleado empleadoLeerArchivo(int id);