#include <stdio.h>
#include <stdlib.h>
#include "src/controllers/base/base.h"
#include "src/services/empresa/empresa.h"
#include "src/services/auth/auth.h"
#include "src/utils/avisos/avisos.h"
#include <string.h>

int main()
{
    char codigo[10];
    obtenerCodigo(codigo);

    while(!validarClaveProducto(codigo)) {
        printf("\n");
        printf("CLAVE DE PRODUCTO INVALIDA\n");
        obtenerCodigo(codigo);
    }

    mostrarAviso("CLAVE DE PRODUCTO VALIDA");

    Empresa empresa;
    if(!obtenerInfoEmpresa(&empresa) || !esValidaEmpresa(&empresa)) {
        printf("INTRODUZCA LA INFORMACION DE SU EMPRESA\n");
        cargarEmpresa(&empresa);
        strcpy(empresa.claveProducto, codigo);
        guardarInfoEmpresa(empresa);
    }

    if(tieneBalanceNegativoEmpresa(&empresa)) mostrarAvisoBalanceNegativo();

    baseMenu();

    return 0;
}
