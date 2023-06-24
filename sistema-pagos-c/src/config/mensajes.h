#pragma once

// DIRECCIONES
#define DIRECCION_LEER_CALLE "Ingrese la calle: "
#define DIRECCION_LEER_NUMERO_CALLE "Ingrese el numero de la calle: "
#define DIRECCION_LEER_CIUDAD "Ingrese la ciudad: "
#define DIRECCION_LEER_PROVINCIA "Ingrese la provincia: "
#define DIRECCION_LEER_CODIGO_POSTAL "Ingrese el codigo postal: "
#define DIRECCION_MOSTRAR "Calle: %s\nNumero: %d\nCiudad: %s\nProvincia: %s\nCodigo postal: %d\n\n"

//EMPLEADOS
#define EMPLEADO_LEER_ID "Ingrese el id: "
#define EMPLEADO_LEER_NOMBRE_APELLIDO "Ingrese el nombre y apellido: "
#define EMPLEADO_LEER_DIRECCION "Ingrese la direccion: \n"
#define EMPLEADO_LEER_TELEFONO "Ingrese el telefono: "
#define EMPLEADO_LEER_TIPO_SUELDO "Ingrese el tipo de sueldo: "
#define EMPLEADO_LEER_JORNADA "Ingrese la jornada: "
#define EMPLEADO_LEER_SUELDO "Ingrese el sueldo: "
#define EMPLEADO_LEER_FECHA_INGRESO "Ingrese la fecha de ingreso (dd/mm/yyyy): "
#define EMPLEADO_LEER_ANIO_INGRESO "Ingrese el anio de ingreso: "
#define EMPLEADO_PREGUNTAR_CARGAR "Desea cargar mas empleados? (s/n): "
#define EMPLEADO_MOSTRAR_PARTE_1 "Id: \x1b[1m%lu\x1b[0m\nNombre y apellido: \x1b[1m"
#define EMPLEADO_MOSTRAR_PARTE_2 "\x1b[0m\nDireccion: \n"
#define EMPLEADO_MOSTRAR_PARTE_3 "\nTelefono: %lu\nFecha de ingreso: %s\n\n"
#define EMPLEADO_MOSTRAR_PAGOS_PENDIENTES "Id: %lu | Nombre y apellido: %s | Sueldo: %.2f | Pagado: %.2f | Pendiente: %.2f\n\n"
#define EMPLEADO_ELEGIR_TITULO "Elija un empleado: "

//PAGOS
#define PAGO_MOSTRAR "Id: %i\nId empleado: %i\nMonto %.2f\nFecha: %s\n"
#define PAGO_PREGUNTAR_CARGAR "Desea cargar mas pagos? (s/n): "
#define PAGO_LEER_ID "Ingrese el id: "
#define PAGO_LEER_EMPLEADO_ID "Ingrese el id de empleado: "
#define PAGO_LEER_MONTO "Ingrese el monto: "
#define PAGO_GUARDADO "\nPago guardado correctamente\n"
#define PAGO_ERROR_GUARDADO "\nError al guardar el pago\n"
#define PAGO_ELIMINADO "\nPago eliminado correctamente\n"

// EMPRESA
#define EMPRESA_LEER_NOMBRE "Ingrese el nombre de la empresa: "
#define EMPRESA_LEER_BALANCE "Ingrese el balance inicial de la empresa: "
#define EMPRESA_MOSTRAR_NOMBRE "Nombre de la empresa: %s\n"
#define EMPRESA_MOSTRAR_BALANCE "Balance inicial: %s\n"
#define EMPRESA_AVISO_BALANCE_NEGATIVO "CUIDADO!!! El balance de la empresa es negativo!"

//Estilos
#define SEPARADOR "----------------------------------------\n"

//ERRORES VALIDACIONES
#define ERROR_LEER_INT "Error al leer el entero, ingrese nuevamente: "
#define ERROR_LEER_FLOAT "Error al leer el float, ingrese nuevamente: "
#define ERROR_LEER_STRING "Error al leer el string, ingrese nuevamente: "
#define ERROR_LEER_CHAR "Error al leer el char, ingrese nuevamente: "
#define ERROR_LEER_FECHA "Error al leer la fecha, ingrese nuevamente: "

//ERRORES ARCHIVOS
#define ERROR_ABRIR_ARCHIVO "Error al abrir el archivo"

//MENUS
#define MENU_PRINCIPAL_TITULO "\n-----MENU PRINCIPAL-----\n"
#define MENU_EMPLEADOS_TITULO "\n-----MENU EMPLEADOS-----\n"
#define MENU_PAGOS_TITULO "\n-----MENU PAGOS-----\n"
#define MENU_ELEGIR_OPCION_TITULO "\n-----ELIJE UNA OPCION-----\n"
#define SALIENDO "Saliendo...\n"
#define VOLVIENDO "Volviendo...\n"
#define CUALQUIER_TECLA_VOLVER "\nPresione cualquier tecla para continuar...\n"

// CONFIGURACIONES
#define CONFIGURACIONES_TITULO "\n-----CONFIGURACIONES-----\n"

//TITULOS OPCIONES MENU EMPLEADOS
#define INGRESAR_DATOS_EMPLEADO "INGRESE LOS DATOS DEL EMPLEADO: \n\n"
#define EMPLEADOS_CARGADOS "EMPLEADOS CARGADOS: \n\n"
#define ELIMINAR_EMPLEADO "ELIMINAR EMPLEADO: \n\n"
#define MODIFICAR_EMPLEADO "MODIFICAR EMPLEADO: \n\n"
#define MODIFICAR_SALARIO_PORCENTAJE "MODIFICAR SALARIO POR PORCENTAJE: \n\n"

//TITULOS OPCIONES MENU EMPLEADOS
#define INGRESAR_DATOS_PAGO "INGRESE LOS DATOS DEL PAGO: \n\n"
#define PAGOS_CARGADOS "PAGOS CARGADOS: \n\n"
#define PAGOS_EMPLEADO "\nPAGOS EMPLEADO: %i \n\n"
#define PAGOS_PENDIENTES "PAGOS PENDIENTES: \n\n"

// SALARIOS
#define SALARIO_MOSTRAR "Sueldo inicial: \x1b[1m%s\x1b[0m\nSueldo final bruto: \x1b[1m%s\x1b[0m\nBonus: \x1b[1m%s\x1b[0m\nImpuestos: \x1b[1m%s\x1b[0m\nSueldo neto: \x1b[1m%s\x1b[0m\n"