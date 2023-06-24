#pragma once

#include <stdbool.h>

void obtenerCodigo(char* codigo);
int** codigoAMatriz(char* codigo);
char* desencriptarMatrizATexto(int** inversa, float** matrizEncriptada, int filas[2], int columnas[2]);
int** textoAMatriz(char* texto, int filas, int columnas);
char* matrizATexto(int** matriz, int filas, int columnas);
int** crearMatrizDinamica(int dimensionX, int dimensionY);
void multiplicarMatrices(int **resultado, int** matrizA, float matrizB[3][3], int filas[2], int columnas[2]);
bool validarClaveProducto(char* codigo);