#pragma once

#define Direccion struct _Direccion

struct _Direccion{
    char calle[70];
    int numero;
    char ciudad[70];
    char provincia[70];
    int codigo_postal;
};

Direccion direccionCrear();
void direccionCargar(Direccion *d);
void direccionMostrar(Direccion* direccion);
void direccionLeerCalle(Direccion* direccion);
void direccionLeerNumero(Direccion* direccion);
void direccionLeerCiudad(Direccion* direccion);
void direccionLeerProvincia(Direccion* direccion);
void direccionLeerCodigoPostal(Direccion* direccion);