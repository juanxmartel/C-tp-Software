#pragma once

#include "../empleados/empleados.h"

float calcularSalarioConBonus(float salario, struct tm* fechaIngreso);
float calcularSalarioNeto(float salario, struct tm* fechaIngreso);
void mostrarSalario(float salario, Empleado empleado);