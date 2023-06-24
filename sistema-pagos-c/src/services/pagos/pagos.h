#pragma once

#include "stdbool.h"
#include "time.h"

#define Pago struct _Pago

struct _Pago
{
    unsigned long id;
    unsigned long idEmpleado;
    float monto;
    struct tm fecha[20];
    bool activo;
};

float pagosEsteMesEmpleadoId(unsigned long empleadoId);
Pago pagoCrear();
void pagoCargar(Pago *pago);
void pagoMostrar(Pago pago);
void pagosMostrar(Pago* pagos, int size);
bool pagoGuardar();
void pagoGuardarVarios();
void pagosLeerArchivo();
void pagosLeerArchivoPorEmpleadoId(long empleadoId);
void pagoLeerId(Pago* pago);
void pagoLeerIdEmpleado(Pago* pago);
void pagoLeerMonto(Pago* pago);
void pagoEliminarPorId(int id);