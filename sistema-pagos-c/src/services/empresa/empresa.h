#pragma once 

#include "stdbool.h";

#define Empresa struct _Empresa

struct _Empresa
{
    char nombre[50];
    int balance;
    char claveProducto[10];
};

void guardarInfoEmpresa(Empresa empresa);
bool obtenerInfoEmpresa(Empresa *empresa);
void cargarEmpresa(Empresa* empresa);
void mostrarEmpresa(Empresa empresa);
void modificarEmpresa(Empresa* empresa);
void modificarMontoEmpresa(int monto);
bool esValidaEmpresa(Empresa* empresa);
bool tieneBalanceNegativoEmpresa(Empresa* empresa);
void mostrarAviso();
void mostrarAvisoBalanceNegativo();
void mostrarAviso(char* aviso);