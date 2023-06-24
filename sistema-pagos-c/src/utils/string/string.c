#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include "stdbool.h"

#include "../../config/mensajes.h"

void leerString(char *string, bool soloLetras)
{
    bool valido = false;

    while (!valido)
    {
        fflush(stdin);
        gets(string);
        trimSpaces(string);

        if (!validarTamanioString(0, string))
        {
            printf(ERROR_LEER_STRING);
            continue;
        }

        if (soloLetras && !validarCaracteresAlfaString(string))
        {
            printf(ERROR_LEER_STRING);
            continue;
        }

        valido = true;
    };
}

bool validarTamanioString(int mayorA, char *string)
{
    return strlen(string) > mayorA;
}

bool validarCaracteresAlfaString(char *string)
{
    int end = strlen(string);

    for (int i = 0; i < end; i++)
    {
        if (!isalpha(string[i]) && string[i] != ' ')
        {
            ;
            return false;
        }
    }

    return true;
}

void trimSpaces(char *string)
{
    _trimSpacesAtEnd(string);
    _trimSpacesAtStart(string);
}

void _trimSpacesAtStart(char *string)
{
    int end = strlen(string);

    for (int i = 0; i < end; i++)
    {
        if (string[i] == ' ')
        {
            string[i] = '\0';
        }
        else
        {
            break;
        }
    }
}

void _trimSpacesAtEnd(char *string)
{
    int end = strlen(string);

    for (int i = end - 1; i >= 0; i--)
    {
        if (string[i] == ' ')
        {
            string[i] = '\0';
        }
        else
        {
            break;
        }
    }
}
