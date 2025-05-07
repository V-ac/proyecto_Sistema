#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>
#include "utilidades.h"

void menuUsuarios(Usuario **listaUsuarios, int *numUsuarios, int *ultimoID);
void menuActividad(Usuario **listaUsuarios, int *numUsuarios, int *ultimoID);
void menuReportes(Usuario **listaUsuarios, int *numUsuarios, int *ultimoID);

// static int ultimoID = 100;

int main()
{
    SetConsoleOutputCP(CP_UTF8); // ¡Solución clave! Para los caracteres especiales
    Usuario *listaUsuarios = NULL;
    int numUsuarios = 0;
    int ultimoID = 0; // Se inicializará a 100 al agregar el primer usuario
    int opcion;
    cargarDatos(&listaUsuarios, &numUsuarios, &ultimoID);

    do
    {
        printf("\n============ MENú PRINCIAL ============\n");
        printf("1. Gestionar usuarios\n");
        printf("2. Registrar actividad ecológica\n");
        printf("3. Generar reportes\n");
        printf("4. Guardar y salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion)
        {
        case 1:
            menuUsuarios(&listaUsuarios, &numUsuarios, &ultimoID);
            break;
        case 2:
            menuActividad(&listaUsuarios, &numUsuarios, &ultimoID);
            break;
        case 3:
            menuReportes(&listaUsuarios, &numUsuarios, &ultimoID);
            break;
        case 4:
            printf("Guardando y saliendo...\n");
            guardarDatos(listaUsuarios, numUsuarios, ultimoID);
            break;
        default:
            printf("Opción no válida\n");
        }
    } while (opcion != 4);

    return 0;
}

void menuUsuarios(Usuario **listaUsuarios, int *numUsuarios, int *ultimoID)
{
    SetConsoleCP(CP_UTF8);

    int opcion;
    do
    {
        printf("\n ============== Menú de Gestion de Usuarios ==============\n");
        printf("1. Agregar nuevo usuario\n");
        printf("2. Modificar usuario\n");
        printf("3. Eliminar usuario\n");
        printf("4. Listar usuarios\n");
        printf("5. Volver al menú principal\n");
        printf("Opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion)
        {
        case 1:
            agregarUsuario(listaUsuarios, numUsuarios, ultimoID); // Sin &
            break;
        case 2:
            if (*numUsuarios == 0)
            {
                printf("No hay usuarios registrados\n");
                break;
            }
            char nombreBuscar[50];
            printf("Nombre de usuario a modificar: ");
            gets(nombreBuscar);
            nombreBuscar[strcspn(nombreBuscar, "\n")] = '\0'; // lo limpiamos de salto de linea

            int indicesModificar[MAX_USUARIOS], encontradosBuscar;
            buscarUsuario(*listaUsuarios, *numUsuarios, nombreBuscar, indicesModificar, &encontradosBuscar);

            buscarModificar(listaUsuarios, numUsuarios, indicesModificar, &encontradosBuscar);

            break;

        case 3:
            if (*numUsuarios == 0)
            {
                printf("No hay usuarios registrados\n");
                break;
            }
            char nombreEliminar[50];
            printf("Nombre de usuario a eliminar: ");
            gets(nombreEliminar);
            nombreEliminar[strcspn(nombreEliminar, "\n")] = '\0'; // lo limpiamos de salto de linea

            int indices[MAX_USUARIOS], encontrados;
            buscarUsuario(*listaUsuarios, *numUsuarios, nombreEliminar, indices, &encontrados);

            buscarEliminar(listaUsuarios, numUsuarios, indices, &encontrados);

            break;
        case 4:
            mostrarListaUsuarios(*listaUsuarios, *numUsuarios);
            break;
        case 5:
            printf("\n\t\t\t\tVolviendo al menú princial...\n\n\n");
            break;

        default:
            printf("Opción no válida\n");
        }

    } while (opcion != 5);
}

// Menu para Actividad
void menuActividad(Usuario **listaUsuarios, int *numUsuarios, int *ultimoID)
{
    SetConsoleCP(CP_UTF8);
    int opcion;
    do
    {
        printf("\n ============== Menú de Registro de Actividad Ecológica ==============\n");
        printf("1. Registrar reciclaje\n");
        printf("2. Registrar ducha corta\n");
        printf("3. Registrar transporte sustentable\n");
        printf("4. Volver al menú principal\n");
        printf("Opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion)
        {
        case 1:
            if (*numUsuarios == 0)
            {
                printf("No hay usuarios registrados\n");
                break;
            }
            char nombreReciclaje[50];
            printf("Nombre de usuario a para registar reciclaje: ");
            gets(nombreReciclaje);
            nombreReciclaje[strcspn(nombreReciclaje, "\n")] = '\0'; // lo limpiamos de salto de linea

            int indicesReciclaje[MAX_USUARIOS], encontradosReciclaje;
            buscarUsuario(*listaUsuarios, *numUsuarios, nombreReciclaje, indicesReciclaje, &encontradosReciclaje);
            registrarBuscar(listaUsuarios, numUsuarios, indicesReciclaje, &encontradosReciclaje, "reciclaje");

            break;
        case 2:
            if (*numUsuarios == 0)
            {
                printf("No hay usuarios registrados\n");
                break;
            }
            char nombreDucha[50];
            printf("Nombre de usuario a para registar ducha corta: ");
            gets(nombreDucha);
            nombreDucha[strcspn(nombreDucha, "\n")] = '\0'; // lo limpiamos de salto de linea

            int indicesDucha[MAX_USUARIOS], encontradosDucha;
            buscarUsuario(*listaUsuarios, *numUsuarios, nombreDucha, indicesDucha, &encontradosDucha);
            registrarBuscar(listaUsuarios, numUsuarios, indicesDucha, &encontradosDucha, "ducha");

            break;
        case 3:
            if (*numUsuarios == 0)
            {
                printf("No hay usuarios registrados\n");
                break;
            }
            char nombreTransporte[50];
            printf("Nombre de usuario a para registar transporte sustentable: ");
            gets(nombreTransporte);
            nombreTransporte[strcspn(nombreTransporte, "\n")] = '\0'; // lo limpiamos de salto de linea

            int indicesTransporte[MAX_USUARIOS], encontradosTransporte;
            buscarUsuario(*listaUsuarios, *numUsuarios, nombreTransporte, indicesTransporte, &encontradosTransporte);
            registrarBuscar(listaUsuarios, numUsuarios, indicesTransporte, &encontradosTransporte, "transporte");

            break;
        case 4:
            printf("\n\t\t\t\tVolviendo al menú princial...\n\n\n");
            break;

        default:
            printf("Opción no válida\n");
        }

    } while (opcion != 4);
}

// Menu de Reportes
void menuReportes(Usuario **listaUsuarios, int *numUsuarios, int *ultimoID)
{
    int opcion;
    do
    {
        printf("\n ============== Menú de Reportes ==============\n");
        printf("1. Ver ranking de usuarios por comunidad\n");
        printf("2. Ver resumen de actividades por usuario\n");
        printf("3. Generar archivo de reporte\n");
        printf("4. Volver al menú principal\n");
        printf("Opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion)
        {
        case 1:

            if (*numUsuarios == 0)
            {
                printf("No hay usuarios registrados\n");
                break;
            }
            char **listaColonias = arregloComunidad(*listaUsuarios, *numUsuarios);
            int numColonias = obtenerTamano(listaColonias);

            char nombreBuscarComunidad[50];
            printf("\nIngrese el nombre de la comunidad: ");
            gets(nombreBuscarComunidad);
            nombreBuscarComunidad[strcspn(nombreBuscarComunidad, "\n")] = '\0'; // lo limpiamos de salto de linea
            char *comunidadesEncontradas[50];
            int encontradosComunidad;

            buscarComunidad(listaColonias, numColonias, nombreBuscarComunidad, comunidadesEncontradas, &encontradosComunidad);
            buscarRanking(listaUsuarios, numUsuarios, listaColonias, numColonias, comunidadesEncontradas, &encontradosComunidad);
            // limpiarBuffer();
            break;
        case 2:
            if (*numUsuarios == 0)
            {
                printf("No hay usuarios registrados\n");
                break;
            }
            char nombreResumen[50];
            printf("Nombre de usuario: ");
            gets(nombreResumen);
            nombreResumen[strcspn(nombreResumen, "\n")] = '\0'; // lo limpiamos de salto de linea

            int indicesResumen[MAX_USUARIOS], encontradosResumen;
            buscarUsuario(*listaUsuarios, *numUsuarios, nombreResumen, indicesResumen, &encontradosResumen);
            buscarGenerar(listaUsuarios, numUsuarios, indicesResumen, &encontradosResumen);
            break;
        case 3:
            // printf("Opcion Generar archivo de reporte\n");
            generarReporteTxT(*listaUsuarios, numUsuarios);
            generarReporte(*listaUsuarios, numUsuarios);
            break;
        case 4:
            printf("\n\t\t\t\tVolviendo al menu princial...\n\n\n");
            break;
        default:
            printf("Opción no válida\n");
        }

    } while (opcion != 4);
}
