#include "number.h"
#include <stdlib.h>
#include <stdio.h>

#include "../../config/mensajes.h";
#include "../../services/configuracion/configuracion.h";

void leerInt(int *numero)
{
    while (scanf("%i", numero) == 0)
    {
        printf(ERROR_LEER_INT);
        fflush(stdin);
    };
}

void leerFloat(float *numero)
{
    while (scanf("%f", numero) == 0)
    {
        printf(ERROR_LEER_FLOAT);
        fflush(stdin);
    };
}

void numeroToString(int numero, char *numeroStr)
{
    Configuracion configuracion;
    bool configuracionLeida = obtenerConfiguracion(&configuracion);

    if (configuracion.formatoNumeros == LETRAS)
    {
        numeroALetra(numero, numeroStr);
        return;
    }

    sprintf(numeroStr, "%d", numero);
}

void numeroALetra(int numero, char *numeroStr)
{
    char strAux[120];

    if(numero < 0) {
        sprintf(numeroStr, "menos ");
        numero *= -1;
    } else {
        sprintf(numeroStr, ""); // Lo dejamos vacio
    }

    // Si el numero es 0, se manda directamente la palabra "cero"
    if(numero == 0) {
        sprintf(numeroStr, "cero");
        return;
    }

    if(numero >= 1000000) {
        resolverMillones(numero, strAux);
        strcat(numeroStr, strAux);
        return;
    }

    if(numero >= 1000) {
        resolverMiles(numero, strAux);
        strcat(numeroStr, strAux);
        return;
    }

    if(numero >= 100) {
        resolverCentenas(numero, strAux);
        strcat(numeroStr, strAux);
        return;
    }

    if(numero >= 10) {
        resolverDecenas(numero, strAux);
        strcat(numeroStr, strAux);
        return;
    }

    resolverUnidades(numero, strAux);
    strcat(numeroStr, strAux);
}

void resolverMillones(int num, char* string) {
    char millonesInLetter[120];
    char milesInLetter[80];

    // Paso el numero a texto
    char* numText = (char*) malloc(15 * sizeof(char));
    sprintf(numText, "%d", num);

    // Separo la parte de millones de los miles
    char* milesText = numText + strlen(numText) - 6;
    char* millonesText = (char*) malloc(15 * sizeof(char));
    strncpy(millonesText, numText, strlen(numText) - 6);

    // Resuelvo la parte de millones y miles, los 2 usando la misma funcion, debido a que la parte de millones puede ser 1 o mas
    resolverMiles(atoi(milesText), milesInLetter);
    resolverMiles(atoi(millonesText), millonesInLetter);

    // Si la parte de millones es mayor a 1, se agrega la palabra "millones" al final
    if(atoi(millonesText) > 1) sprintf(string, "%s millones %s", millonesInLetter, milesInLetter);
    else sprintf(string, "un millon %s", milesText);

    free(numText);
    free(milesText);
    free(millonesText);
}

void resolverMiles(int num, char* string) {
    // Si el numero es 1000, se manda directamente la palabra "mil"
    if(num == 1000) {
        sprintf(string, "mil");
        return;
    } 

    char milesInLetter[80];
    char centenasInLetter[60];

    // Paso el numero a texto
    char* numText = (char*) malloc(10 * sizeof(char));
    sprintf(numText, "%d", num);

    // Si el numero es menor a 1000, se manda a resolver las centenas
    if(strlen(numText) < 4) {
        resolverCentenas(num, string);
        return;
    }

    // Separo la parte de centenas de los miles
    char* centenasText = numText + strlen(numText) - 3;
    char* milesText = (char*) malloc(10 * sizeof(char));
    strncpy(milesText, numText, strlen(numText) - 3);;

    // Resuelvo la parte de miles y centenas
    resolverCentenas(atoi(centenasText), centenasInLetter);
    resolverCentenas(atoi(milesText), milesInLetter);

    // Si la parte de miles es mayor a 1, se agrega la palabra "mil" al final
    if(atoi(milesText) > 1) sprintf(string, "%s mil %s", milesInLetter, centenasInLetter);
    else if(atoi(milesText) == 1) sprintf(string, "mil %s", centenasInLetter);
    else sprintf(string, "%s", centenasInLetter);

    free(numText);
    free(milesText);
    free(centenasText);
}

void resolverCentenas(int num, char* string) {
    char *centenas[] = {"", "ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos",
        "seiscientos", "setecientos", "ochocientos", "novecientos"};

    // Si el numero es 100, se manda directamente la palabra "cien"
    if(num == 100) {
        sprintf(string, "cien");
        return;
    }

    // Se manda a resolver las decenas
    char decenas[40];
    resolverDecenas(num % 100, decenas);

    // Si el numero es mayor a 100, se agrega la palabra "cientos" al final, sino se manda directamente las decenas
    if(num / 100 > 0) sprintf(string, "%s %s", centenas[num / 100], decenas);
    else sprintf(string, "%s", decenas);
}

void resolverDecenas(int num, char* string) {
    char *excepciones[] = {"diez", "once", "doce", "trece", "catorce", "quince"};
    char *decenas[] = {"", "dieci", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta",
        "ochenta", "noventa"};

    // Si el numero es menor a 10, se manda a resolver las unidades
    if(num < 10) {
        resolverUnidades(num, string);
        return;
    }

    // Si el numero es menor a 15, se manda a resolver las excepciones
    if (num < 15)
    {
        sprintf(string, "%s", excepciones[num - 10]);
        return;
    }

    // Si el numero es menor a 20, se manda a resolver las unidades y se agrega la palabra "dieci" al principio
    if(num < 20) {
        char unidades[10];
        resolverUnidades(num % 10, unidades);
        sprintf(string, "dieci%s", unidades);
        return;
    }

    // Si el numero es 20, se manda directamente la palabra "veinte"
    if(num == 20) {
        sprintf(string, "%s", decenas[num / 10]);
        return;
    }

    // Si el numero es menor a 30, se manda a resolver las unidades y se agrega la palabra "veinti" al principio
    if(num < 30) {
        char unidades[10];
        resolverUnidades(num % 10, unidades);
        sprintf(string, "veinti%s", unidades);
        return;
    }

    // Se manda a resolver las unidades
    char unidades[10];
    resolverUnidades(num % 10, unidades);

    // Si el numero es mayor a 30, se agrega la palabra "y" al medio con decentas[num / 10] y unidades
    if(strlen(unidades) > 0) sprintf(string, "%s y %s", decenas[num / 10], unidades);
    else sprintf(string, "%s", decenas[num / 10]);
}

void resolverUnidades(int num, char* string) {
    char *unidades[] = {"", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho",
        "nueve"};

    // El numero se manda directamente a texto
    sprintf(string, "%s", unidades[num]);
}