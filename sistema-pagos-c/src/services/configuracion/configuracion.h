#pragma once

#include "stdbool.h"

#define Configuracion struct _Configuracion

typedef enum FormatoFecha
{
    DD_MM_AAAA = 0,
    MM_DD_AAAA = 1,
    AAAA_MM_DD = 2,
    LETRAS_FECHA = 3
};

typedef enum FormatoNumeros
{
    NUMEROS = 0,
    LETRAS = 1
};

struct _Configuracion
{
    int formatoFechas;
    int formatoNumeros;
    int porcentajeAntiguedad;
    int porcentajeImpuestos;
};

void guardarConfiguracion(Configuracion *configuracion);
bool obtenerConfiguracion(Configuracion *configuracion);