#pragma once

bool guardarRegistro(char* nombreArchivo, void* registro, int sizeRegistro);
bool guardarRegistros(char* nombreArchivo, void* registros, int sizeRegistro, int cantidad);
bool leerRegistro(char* nombreArchivo, void* registro, int sizeRegistro, int posicion);
int cantidadRegistros(char* nombreArchivo, int sizeRegistro);
bool leerRegistros(char* nombreArchivo, void* registros, int sizeRegistro);
bool modificarRegistro(char* nombreArchivo, void* registro, int sizeRegistro, int posicion);
bool modificarRegistros(char* nombreArchivo, void* registros, int sizeRegistro, int posicion, int cantidad);
bool eliminarRegistro(char* nombreArchivo, int sizeRegistro, int posicion);