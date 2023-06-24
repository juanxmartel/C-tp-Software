#include "empleados.h"
#include "../../config/mensajes.h"
#include "../../services/empleados/empleados.h"
#include "../../services/menu/menu.h"
#include "../../utils/number/number.h"
#include "../../config/commands.h"

/**
 * Carga un empleado en el archivo
*/
void empleadoCargarUno()
{
    system(CLEAR);

    printf(INGRESAR_DATOS_EMPLEADO);

    bool resultado = empleadoGuardar();

    if(resultado) {
        printf("\nEmpleado guardado correctamente\n");
    } else {
        printf("\nError al guardar el empleado\n");
    }
}

/**
 * Muestra todos los empleados en el archivo
*/
void mostrarEmpleados()
{
    system(CLEAR);

    printf(EMPLEADOS_CARGADOS);

    empleadosLeerArchivo();
}

/**
 * Despliega menu de eleccion de empleado y elimina el empleado seleccionado
*/
void eliminarEmpleado()
{
    system(CLEAR);

    printf(ELIMINAR_EMPLEADO);
 
    int id = desplegarSeleccionDeEmpleado();

    if(id == -1) {
        return;
    }

    empleadoEliminarPorId(id);

    printf("\nEmpleado eliminado correctamente\n");
}

/**
 * Despliega menu de eleccion de empleado y modifica el empleado seleccionado
*/
void modificarEmpleado() {
    system(CLEAR);

    printf(MODIFICAR_EMPLEADO);

    int id = desplegarSeleccionDeEmpleado();

    if(id == -1) {
        return;
    }

    empleadoModificarPorId(id);

    printf("\nEmpleado modificado correctamente\n");
}

/**
 * Agrega un porcentaje a todos los salarios de los empleados
*/
void modificarSalarioPorcentaje() {
    system(CLEAR);

    printf(MODIFICAR_SALARIO_PORCENTAJE);

    int porcentaje;
    printf("Ingrese el porcentaje que desea agregar a todos los salarios: ");
    leerInt(&porcentaje);

    empleadoModificarPorcentajeSalarioTodos(porcentaje);

    printf("\nSalarios modificados correctamente\n");
}

/**
 * Muestra un menu de propiedades por las que filtrar empleados que luego seran mostrados
*/
void empleadosFiltradosPorPropiedad() {
    Menu menu;
    int cantidadOpciones = 4;

    char* nombres[] = {
        "Telefono", 
        "Sueldo", 
        "Anio ingreso",
        "Tipo de sueldo",
    };

    menuDesplegar(&menu, MENU_ELEGIR_OPCION_TITULO, nombres, NULL, cantidadOpciones);

    switch (menu.opcionActual - 1) {
        case 0:
            empleadoLeerPorTelefonoConsola();
            break;
        case 1:
            empleadoLeerPorSueldoConsola();
            break;
        case 2:
            empleadoLeerPorAnioIngresoConsola();
            break;
        case 3:
            empleadoLeerPorTipoSueldoConsola();
            break;
    }
}

/**
 * Obtiene las opciones de empleados con formato (id - nombre) y las despliega en un menu para que el usuario elija uno
*/
int desplegarSeleccionDeEmpleado() {
    Menu menuEmpleadosOpciones;
    char **nombresOpciones;
    int cantidadOpcionesEmpleados = empleadosArchivoCargarOpcionesEnArregloStrings(&nombresOpciones);
    nombresOpciones[cantidadOpcionesEmpleados] = "Volver"; // Se agrega la opcion volver al final del arreglo de strings

    menuDesplegar(&menuEmpleadosOpciones, EMPLEADO_ELEGIR_TITULO, nombresOpciones, NULL, cantidadOpcionesEmpleados + 1);

    // Si se elige la opcion volver, se libera el arreglo de strings y se retorna -1
    if(menuEmpleadosOpciones.opcionActual == cantidadOpcionesEmpleados + 1) {
        liberarArregloDeStringsEmpleados(nombresOpciones);
        return -1;
    }


    // Se obtiene el id del empleado elegido
    int idElegido;
    sscanf(nombresOpciones[menuEmpleadosOpciones.opcionActual - 1], "%d", &idElegido);

    liberarArregloDeStringsEmpleados(nombresOpciones);

    return idElegido;
}

/**
 * Se muestran los empleados en un menu para que el usuario elija uno y luego se muestran 
 * las propiedades del empleado elegido para modificar una
*/
void empleadosModificarPorPropiedad() {
    int id = desplegarSeleccionDeEmpleado();

    if(id == -1) {
        return;
    }

    Menu menu;
    int cantidadOpciones = 3;

    char* nombres[] = {
        "Telefono", 
        "Sueldo", 
        "Tipo de sueldo"
    };

    menuDesplegar(&menu, MENU_ELEGIR_OPCION_TITULO, nombres, NULL, cantidadOpciones);

    Empleado empleado = empleadoLeerArchivo(id);

    switch (menu.opcionActual - 1) {
        case 0:
            empleadoLeerTelefono(&empleado);
            break;
        case 1:
            empleadoLeerSueldo(&empleado);
            break;
        case 2:
            empleadoLeerTipoDeSueldo(&empleado);
            break;
    }

    empleadoModificarPorIdManual(id, &empleado);
}

/**
 * Imprime un mensaje de que se esta volviendo al menu principal
*/
void volverEmpleadoMenu()
{
    printf(VOLVIENDO);
}

/**
 * Imprime un mensaje de que se esta saliendo del programa
*/	
void salirEmpleadoMenu()
{
    printf(SALIENDO);
}

/**
 * Despliega el menu de funcionalidades de empleados
*/
void empleadosMenu() {
    Menu menu;
    int cantidadOpciones = 9;

    char* nombres[] = {
        "Cargar un empleado", 
        "Mostrar Empleados", 
        "Eliminar empleado", 
        "Modificar empleado", 
        "Modificar propiedad de empleado",
        "Aumentar porcentaje de salario a empleados",
        "Empleados filtrados por propiedad",
        "Volver", 
        "Salir"
    };

    void (*funciones[])() = {
        empleadoCargarUno, 
        mostrarEmpleados, 
        eliminarEmpleado, 
        modificarEmpleado, 
        empleadosModificarPorPropiedad,
        modificarSalarioPorcentaje,
        empleadosFiltradosPorPropiedad,
        volverEmpleadoMenu, 
        salirEmpleadoMenu
    };

    do {
        menuDesplegar(&menu, MENU_EMPLEADOS_TITULO, nombres, funciones, cantidadOpciones);
        printf(CUALQUIER_TECLA_VOLVER);
    } while (menu.opcionActual != cantidadOpciones - 1 && menu.opcionActual != cantidadOpciones && getch()); //

    if (menu.opcionActual == cantidadOpciones)
        exit(0);
}
