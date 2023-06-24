#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "configuracion.h"
#include "../archivos/archivos.h"
#include "../../config/mensajes.h"
#include "../../config/pathFiles.h"

/**
 * Guarda la configuracion en el archivo de configuraciones
*/
void guardarConfiguracion(Configuracion *configuracion) {
    // Elimino el archivo para que no queden datos viejos
    FILE *archivo = fopen(PATH_CONFIGURACIONES, "wb");
    if(archivo) fclose(archivo);

    return guardarRegistro(PATH_CONFIGURACIONES, configuracion, sizeof(Configuracion));
}

/**
 * Obtiene la configuracion del archivo de configuraciones
*/
bool obtenerConfiguracion(Configuracion *configuracion) {
    return leerRegistro(PATH_CONFIGURACIONES, configuracion, sizeof(Configuracion), 0);
}