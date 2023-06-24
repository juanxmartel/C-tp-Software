#pragma once 

#include "stdbool.h";

void leerString(char *string, bool soloLetras);
bool validarTamanioString(int mayorA, char *string);
bool validarCaracteresAlfaString(char *string);
void trimSpaces(char *string);
void _trimSpacesAtStart(char *string);
void _trimSpacesAtEnd(char *string);