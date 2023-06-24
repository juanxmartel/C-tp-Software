#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"

/**
 *  Guarda un registro en un archivo. Si el archivo no existe, lo crea.
 * @param nombreArchivo Nombre del archivo a guardar.
 * @param registro Registro a guardar. Direccion de memoria void para que se pueda pasar cualquier tipo.
 * @param sizeRegistro Tamaño del registro a guardar.
 *  @return true si se pudo guardar, false si no.
*/
bool guardarRegistro(char* nombreArchivo, void* registro, int sizeRegistro)
{
    FILE* archivo = fopen(nombreArchivo, "ab");

    if(archivo)
    {
        fwrite(registro, sizeRegistro, 1, archivo);
        fclose(archivo);
        return true;
    }

    return false;
}

/**
 *  Guarda varios registros en un archivo. Si el archivo no existe, lo crea.
 * @param nombreArchivo Nombre del archivo a guardar.
 * @param registros Registros a guardar. Direccion de memoria void para que se pueda pasar cualquier tipo de arreglo.
 * @param sizeRegistro Tamaño del registro a guardar.
 * @param cantidad Cantidad de registros a guardar.
 * @return true si se pudo guardar, false si no.
*/
bool guardarRegistros(char* nombreArchivo, void* registros, int sizeRegistro, int cantidad)
{
    FILE* archivo = fopen(nombreArchivo, "ab");

    if(archivo)
    {
        fwrite(registros, sizeRegistro, cantidad, archivo);
        fclose(archivo);
        return true;
    }

    return false;
}

/**
 * Lee un registro de un archivo.
 * @param nombreArchivo Nombre del archivo a leer.
 * @param registro Registro a leer. Direccion de memoria void para que se pueda pasar cualquier tipo.
 * @param sizeRegistro Tamaño del registro a leer.
 * @param posicion Posicion del registro a leer.
 * @return true si se pudo leer, false si no.
*/
bool leerRegistro(char* nombreArchivo, void* registro, int sizeRegistro, int posicion) {
    FILE* archivo = fopen(nombreArchivo, "rb");

    if(archivo)
    {
        fseek(archivo, sizeRegistro * posicion, SEEK_SET);
        fread(registro, sizeRegistro, 1, archivo);

        fclose(archivo);
        return true;
    }

    return false;
}

/**
 * Lee todos los registros de un archivo.
 * @param nombreArchivo Nombre del archivo a leer.
 * @param sizeRegistro Tamaño del registro a leer.
 * @return cantidad de registros.
*/
int cantidadRegistros(char* nombreArchivo, int sizeRegistro) {
    FILE* archivo = fopen(nombreArchivo, "r+b");
    int cantidad = 0;

    if(archivo)
    {
        fseek(archivo, 0, SEEK_END);
        cantidad = ftell(archivo) / sizeRegistro;
        fclose(archivo);
    }

    return cantidad;
}

/**
 * Lee todos los registros de un archivo.
 * @param nombreArchivo Nombre del archivo a leer.
 * @param registros Registros a leer. Direccion de memoria void para que se pueda pasar cualquier tipo de arreglo a rellenar
 * @param sizeRegistro Tamaño del registro a leer.
 * @return true si se pudo leer, false si no.
*/
bool leerRegistros(char* nombreArchivo, void* registros, int sizeRegistro) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    int cantidad = cantidadRegistros(nombreArchivo, sizeRegistro);

    if(archivo)
    {
        fread(registros, sizeRegistro, cantidad, archivo);
        fclose(archivo);
        return true;
    }

    return false;
}

/**
 * Elimina un registro de un archivo. Convierte el registro en un registro vacio con el caracter '\0'.
 * @param nombreArchivo Nombre del archivo a eliminar.
 * @param sizeRegistro Tamaño del registro a eliminar.
 * @param posicion Posicion del registro a eliminar.
 * @return true si se pudo eliminar, false si no.
*/
bool eliminarRegistro(char* nombreArchivo, int sizeRegistro, int posicion) {
    FILE* archivo = fopen(nombreArchivo, "r+b");

    if(archivo)
    {
        fseek(archivo, sizeRegistro * posicion, SEEK_SET);
        fwrite("\0", sizeRegistro, 1, archivo);
        fclose(archivo);
        return true;
    }

    return false;
}

/**
 *  Modifica un registro de un archivo.
 * @param nombreArchivo Nombre del archivo a modificar.
 *  @param registro Registro a modificar. Direccion de memoria void para que se pueda pasar cualquier tipo.
 * @param sizeRegistro Tamaño del registro a modificar.
 * @param posicion Posicion del registro a modificar.
 * @return true si se pudo modificar, false si no.
*/
bool modificarRegistro(char* nombreArchivo, void* registro, int sizeRegistro, int posicion) {
    FILE* archivo = fopen(nombreArchivo, "r+b");

    if(archivo)
    {
        fseek(archivo, sizeRegistro * posicion, SEEK_SET);
        fwrite(registro, sizeRegistro, 1, archivo);
        fclose(archivo);
        return true;
    }

    return false;
}

/**
 * Modifica varios registros de un archivo.
 * @param nombreArchivo Nombre del archivo a modificar.
 * @param registros Registros a modificar. Direccion de memoria void para que se pueda pasar cualquier tipo de arreglo.
 * @param sizeRegistro Tamaño del registro a modificar.
 * @param posicion Posicion del registro a modificar.
 * @param cantidad Cantidad de registros a modificar.
 * @return true si se pudo modificar, false si no.
*/
bool modificarRegistros(char* nombreArchivo, void* registros, int sizeRegistro, int posicion, int cantidad) {
    FILE* archivo = fopen(nombreArchivo, "r+b");

    if(archivo)
    {
        fseek(archivo, sizeRegistro * posicion, SEEK_SET);
        fwrite(registros, sizeRegistro, cantidad, archivo);
        fclose(archivo);
        return true;
    }

    return false;
}