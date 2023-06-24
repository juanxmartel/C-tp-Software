#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "direcciones.h"
#include "../../utils/number/number.h"
#include "../../utils/string/string.h"
#include "../../config/mensajes.h"

Direccion direccionCrear() {
    Direccion nueva;

    direccionCargar(&nueva);

    return nueva;
}

void direccionCargar(Direccion *d) {
    direccionLeerCalle(d);
    direccionLeerNumero(d);
    direccionLeerCiudad(d);
    direccionLeerProvincia(d);
    direccionLeerCodigoPostal(d);
}

void direccionMostrar(Direccion* direccion) {
    printf(DIRECCION_MOSTRAR, direccion->calle, direccion->numero, direccion->ciudad, direccion->provincia, direccion->codigo_postal);
}

void direccionLeerCalle(Direccion* direccion) {
    printf(DIRECCION_LEER_CALLE);
    leerString(direccion->calle, true);
}

void direccionLeerNumero(Direccion* direccion) {
    printf(DIRECCION_LEER_NUMERO_CALLE);
    leerInt(&direccion->numero);
}

void direccionLeerCiudad(Direccion* direccion) {
    printf(DIRECCION_LEER_CIUDAD);
    leerString(direccion->ciudad, true);
}

void direccionLeerProvincia(Direccion* direccion) {
    printf(DIRECCION_LEER_PROVINCIA);
    leerString(direccion->provincia, true);
}

void direccionLeerCodigoPostal(Direccion* direccion) {
    printf(DIRECCION_LEER_CODIGO_POSTAL);
    leerInt(&direccion->codigo_postal);
}
