#include "fecha.h"
#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "time.h"

#include "../../services/configuracion/configuracion.h"
#include "../../config/mensajes.h"

char *meses[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio",
                    "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

void leerFecha(struct tm *fecha)
{
    char fecha_str[11];
    int dia, mes, anio;

    leerString(fecha_str, false);

    while (sscanf(fecha_str, "%d/%d/%d", &dia, &mes, &anio) != 3)
    {
        printf(ERROR_LEER_FECHA);
        leerString(fecha_str, false);
    }

    fecha->tm_mday = dia;
    fecha->tm_mon = mes;
    fecha->tm_year = anio;
    fecha->tm_hour = 0;
    fecha->tm_min = 0;
    fecha->tm_sec = 0;
    fecha->tm_isdst = -1;
}

void fechaNow(struct tm *fecha)
{
    time_t t = time(NULL);
    *fecha = *localtime(&t);
    fecha->tm_year += 1900;
}

void fechaToString(struct tm *fecha, char *fecha_str)
{
    Configuracion configuracion;
    bool configuracionLeida = obtenerConfiguracion(&configuracion);

    if (configuracion.formatoFechas == MM_DD_AAAA)
    {
        sprintf(fecha_str, "%02d/%02d/%04d", fecha->tm_mon, fecha->tm_mday, fecha->tm_year);
        return;
    }

    if (configuracion.formatoFechas == AAAA_MM_DD)
    {
        sprintf(fecha_str, "%04d/%02d/%02d", fecha->tm_year, fecha->tm_mon, fecha->tm_mday);
        return;
    }

    if (configuracion.formatoFechas == LETRAS_FECHA)
    {
        if (fecha->tm_mon >= 1 && fecha->tm_mon <= 12)
        {
            sprintf(fecha_str, "%02d de %s de %04d", fecha->tm_mday, meses[fecha->tm_mon - 1], fecha->tm_year);
        }
        else
        {
            sprintf(fecha_str, "Fecha inválida");
        }

        return;
    }

    // DD_MM_AAAA
    sprintf(fecha_str, "%02d/%02d/%04d", fecha->tm_mday, fecha->tm_mon, fecha->tm_year);
}
