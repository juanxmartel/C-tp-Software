#pragma once

#include <stdio.h>
#include <malloc.h>
#define Pila struct _Pila
#define P_Pila struct _Pila *

struct _Pila
{
    float valores[50]; // 50 valores float fijos
    int postope;
};

void inicpila(P_Pila p);
void apilar(P_Pila p, float dato);
float desapilar(P_Pila p);
float tope(P_Pila p);
float pilavacia(P_Pila p);
void leer (P_Pila p);
void mostrar(P_Pila p);


