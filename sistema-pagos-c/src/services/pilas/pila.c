#include "pila.h"


void inicpila(P_Pila p)
{
    p->postope=0;
}

void apilar(P_Pila p, float dato)
{
    int index = (*p).postope;
    (*p).valores[index]=dato;
    (*p).postope = (*p).postope + 1;
}

float desapilar(P_Pila p)
{
    float z = p->valores[p->postope -1];
    p->postope--;
    return z;
}

float tope(P_Pila p)
{
    return p->valores[p->postope - 1];
}

float pilavacia(P_Pila p)
{
    return (p->postope == 0);
}

void leer (P_Pila p)
{
    float aux = 0;
    if (p->postope < 50)
    {
        printf("Ingrese un valor entero: ");
        fflush(stdin);
        scanf("%d", &aux);
        apilar(p, aux);
    }
    else
        printf("Error: la pila esta llena");
}

void mostrar(P_Pila p)
{
    for(int i=0; i < p->postope; i++)
        printf("| %.2f ", p->valores[i]);
    printf("\n");
}
