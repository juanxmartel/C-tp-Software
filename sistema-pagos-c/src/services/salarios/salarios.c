#include "salarios.h"
#include "../../utils/number/number.h"
#include "../empleados/empleados.h"
#include "../../utils/fecha/fecha.h"
#include "../configuracion/configuracion.h"
#include "../../config/mensajes.h"
#include <stdbool.h>
#include <time.h>

#define PORCENTAJE_IMPUESTOS 23
#define PORCENTAJE_BONUS_ANTIGUEDAD 8

float calcularImpuestos(float salario) {
    Configuracion configuracion;
    bool configuracionLeida = obtenerConfiguracion(&configuracion);
    int porcentajeImpuestos = configuracionLeida ? configuracion.porcentajeImpuestos : PORCENTAJE_IMPUESTOS;
    return salario * porcentajeImpuestos / 100;
}

float calcularBonus(float salario, struct tm* fechaIngreso) {
    Configuracion configuracion;
    bool configuracionLeida = obtenerConfiguracion(&configuracion);
    int porcentajeAntiguedad = configuracionLeida ? configuracion.porcentajeAntiguedad : PORCENTAJE_BONUS_ANTIGUEDAD;

    struct tm fechaActual;
    fechaNow(&fechaActual);

    int antiguedad = fechaActual.tm_year - fechaIngreso->tm_year;

    return salario * ((float) antiguedad * (float) porcentajeAntiguedad / 100);
}

float calcularSalarioConBonus(float salario, struct tm* fechaIngreso) {
    return salario + calcularBonus(salario, fechaIngreso);
}

float calcularSalarioNeto(float salario, struct tm* fechaIngreso) {
    
    return calcularSalarioConBonus(salario, fechaIngreso) - calcularImpuestos(salario);
}

void mostrarSalario(float salario, Empleado empleado) { 
    float sueldoBrutoInicial = salario;   
    float sueldoConBonus = calcularSalarioConBonus(salario, empleado.fechaIngreso);
    float salarioNeto = calcularSalarioNeto(salario, empleado.fechaIngreso);
    float bonus = calcularBonus(salario, empleado.fechaIngreso);
    float impuestos = calcularImpuestos(salario);

    char salarioInicialText[120];
    numeroToString(sueldoBrutoInicial, salarioInicialText);

    char salarioText[120];
    numeroToString(sueldoConBonus, salarioText);

    char bonusText[120];
    numeroToString(bonus, bonusText);

    char impuestosText[120];
    numeroToString(impuestos, impuestosText);

    char salarioNetoText[120];
    numeroToString(salarioNeto, salarioNetoText);

    printf(SALARIO_MOSTRAR, salarioInicialText, salarioText, bonusText, impuestosText, salarioNetoText);
}