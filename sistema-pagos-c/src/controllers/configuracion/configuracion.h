#pragma once

#include "../../services/menu_horizontal/menu_horizontal.h"

void configuracionMenu();
void mover(int opcionActual, int tecla);

Menu_Horizontal construirOpcionFormatoNumeros(int opcionActual);
Menu_Horizontal construirOpcionFormatoFecha(int opcionActual);
Menu_Horizontal construirOpcionPorcentajeAntiguedad(int opcionActual);
Menu_Horizontal construirOpcionPorcentajeImpuestos(int opcionActual);
void guardarConfiguracionMenu();