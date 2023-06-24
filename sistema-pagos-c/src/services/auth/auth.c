#include "auth.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include "../../utils/string/string.h"
#include "../empresa/empresa.h"

float claveEncriptada[3][3] = {
    {
        -57.11,
        -10.55,
        -6.88,
    },
    {
        -65.88,
        -10.44,
        -13.11
    },
    {
        68.44,
        14.22,
        11.55
    }
};


void multiplicarMatrices(int **resultado, int** matrizA, float matrizB[3][3], int filas[2], int columnas[2])
{
    if(columnas[0] != filas[1]) return NULL;

    for (int j = 0; j < columnas[1]; j++)
    {
        for (int i = 0; i < filas[0]; i++)
        {
            float sumaFila = 0;
            for (int z = 0; z < filas[1]; z++)
            {
                sumaFila += (float) matrizA[i][z] * (float) matrizB[z][j];
            }

            resultado[i][j] = round(sumaFila);
        }
    }
}

int **crearMatrizDinamica(int dimensionX, int dimensionY)
{
    if (dimensionX <= 0 || dimensionY <= 0) {
        return NULL;
    }

    int **matriz = malloc(sizeof(int *) * dimensionX);

    for (int i = 0; i < dimensionX; i++)
    {
        *(matriz + i) = malloc(sizeof(int) * dimensionY);
    }

    return matriz;
}

void borrarMatrizDinamica(int **matriz, int dimensionX)
{
    for (int i = 0; i < dimensionX; i++)
    {
        free(matriz[i]);
    }

    free(matriz);
}

char* matrizATexto(int** matriz, int filas, int columnas) {
    char* texto = malloc(sizeof(char) * filas * columnas + 1);
    int cargados = 0;
    char a = 'a';
    int aCode = a;

    for(int i = 0; i < columnas; i++) {
        for(int j = 0; j < filas; j++) {
            if(matriz[j][i] == 0) {
                texto[cargados] = '\0';
                break;
            }

            texto[cargados] = (char) (matriz[j][i] + aCode - 1);
            cargados++;
        }
    }

    texto[cargados] = '\0';

    return texto;
}

int** textoAMatriz(char* texto, int filas, int columnas) {
    int** matriz = crearMatrizDinamica(filas, columnas);
    int cargados = 0;

    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < columnas; j++) {
            matriz[i][j] = texto[cargados] - '0';
            cargados++;
        }
    }

    return matriz;
}

void obtenerCodigo(char* codigo) {
    Empresa empresa;

    if(obtenerInfoEmpresa(&empresa)) {
        strcpy(codigo, empresa.claveProducto);
        return;
    }

    printf("Ingrese la clave de producto: ");
    leerString(codigo, false);
}

int** codigoAMatriz(char* codigo) {
   int** matriz = textoAMatriz(codigo, 3, 3);
}

char* desencriptarMatrizATexto(int** inversa, float** matrizEncriptada, int filas[2], int columnas[2])
{
    int** matrizDesencriptada = crearMatrizDinamica(filas[0], columnas[1]);

    multiplicarMatrices(matrizDesencriptada, inversa, matrizEncriptada, filas, columnas);

    char* textoDesencriptado = matrizATexto(matrizDesencriptada, filas[0], columnas[1]);

    borrarMatrizDinamica(matrizDesencriptada, filas[0]);

    return textoDesencriptado;
}

bool validarClaveProducto(char* codigo) {
    int** matriz = codigoAMatriz(codigo);

    int filas[] = {3, 3};
    int columnas[] = {3, 3};

    float** claveEncriptadaPointer = claveEncriptada;
    char* texto = desencriptarMatrizATexto(matriz, claveEncriptadaPointer, filas, columnas);

    if(strcmp(texto, "password") == 0) {
        borrarMatrizDinamica(matriz, 3);
        free(texto);
        return true;
    }

    return false;
}
