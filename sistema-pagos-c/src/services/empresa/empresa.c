#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "empresa.h"
#include "../archivos/archivos.h"
#include "../../utils/string/string.h"
#include "../../utils/number/number.h"
#include "../../utils/avisos/avisos.h"
#include "../../config/mensajes.h"
#include "../../config/pathFiles.h"

void cargarEmpresa(Empresa* empresa) {
    printf(EMPRESA_LEER_NOMBRE);
    leerString(empresa->nombre, true);
    printf(EMPRESA_LEER_BALANCE);
    leerInt(&empresa->balance);
}

void guardarInfoEmpresa(Empresa empresa) {
    // Elimino el archivo para que no queden datos viejos
    FILE *archivo = fopen(PATH_EMPRESA, "wb");
    if(archivo) fclose(archivo);

    return guardarRegistro(PATH_EMPRESA, &empresa, sizeof(Empresa));
}

bool obtenerInfoEmpresa(Empresa *empresa) {
    return leerRegistro(PATH_EMPRESA, empresa, sizeof(Empresa), 0);
}

bool esValidaEmpresa(Empresa* empresa) {
    return 
        strlen(empresa->nombre) > 0;
}

bool tieneBalanceNegativoEmpresa(Empresa* empresa) {
    return empresa->balance < 0;
}

void mostrarAvisoBalanceNegativo() {
    mostrarAviso(EMPRESA_AVISO_BALANCE_NEGATIVO);
    printf(CUALQUIER_TECLA_VOLVER);
    getch();
}

void mostrarEmpresa(Empresa empresa) {
    char balance_str[100];
    numeroToString(empresa.balance, balance_str);

    printf(SEPARADOR);
    printf(EMPRESA_MOSTRAR_NOMBRE, empresa.nombre);
    printf(EMPRESA_MOSTRAR_BALANCE, balance_str);
    printf(SEPARADOR);
}

void modificarEmpresa(Empresa* empresa) {
    cargarEmpresa(empresa);

    guardarInfoEmpresa(*empresa);
}

void modificarMontoEmpresa(int monto) {
    Empresa empresa;
    obtenerInfoEmpresa(&empresa);
    empresa.balance += monto;
    guardarInfoEmpresa(empresa);
}