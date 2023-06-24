#pragma once

#include "time.h"

void leerFecha(struct tm *fecha);
void fechaNow(struct tm *fecha);
void fechaToString(struct tm *fecha, char *fecha_str);