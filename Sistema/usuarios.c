#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilidades.h"

static int ultimoID = 100;

void limpiarBuffer()
{
    while (getchar() != '\n')
        ; // Limpiar el buffer de entrada
}

void agregarUsuario(Usuario **lista, int *numUsuario, int *ultimoID)
{

    *lista = (Usuario *)realloc(*lista, (*numUsuario + 1) * sizeof(Usuario));
    if (*lista == NULL)
    {
        printf("Error al asignar memoria.\n");
        return;
    }

    Usuario *nuevo = &(*lista)[*numUsuario];
    if (*numUsuario == 0 && *ultimoID < 100)
    {
        *ultimoID = 100;
    }
    nuevo->id = ++(*ultimoID);

    printf("Nombre: ");
    // fgets(nuevo->nombre, sizeof(nuevo->nombre), stdin);
    gets(nuevo->nombre);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = '\0'; // Eliminar salto de línea

    printf("Edad: ");
    while (scanf("%d", &nuevo->edad) != 1)
    {
        printf("Entrada inválida. Ingrese la edad (número): ");
        limpiarBuffer();
    }
    //
    limpiarBuffer();

    printf("Comunidad: ");
    gets(nuevo->comunidad);
    // opcional, es de limpieza del salto de linea
    nuevo->comunidad[strcspn(nuevo->comunidad, "\n")] == '\0';

    // Suponiendo que vamos a ingresar puntos ecologicos tambien
    // printf("Puntos Ecologicos: ");
    // scanf("%f", &nuevo->puntosTotalesEcologicos);
    // limpiarBuffer();

    (*numUsuario)++; // Incrementar contador
                     // guardarYMostrarNombres(*lista, *numUsuario);
}

void mostrarListaUsuarios(Usuario *lista, int numUsuario)
{
    if (numUsuario == 0)
    {
        printf("\nNo hay usuarios registrados.\n");
        return;
    }

    printf("\n=========== LISTA DE USUARIOS ===========\n");
    for (int i = 0; i < numUsuario; i++)
    {
        printf("\nID: %d", lista[i].id);
        printf("\nNombre: %s", lista[i].nombre);
        printf("\nEdad: %d", lista[i].edad);
        printf("\nComunidad: %s", lista[i].comunidad);
        printf("\nPuntos Ecologicos: %.2f\n", lista[i].puntosTotalesEcologicos);
    }
}

Usuario *buscarUsuario(Usuario *lista, int numUsuarios, const char *nombre, int *indices, int *encontrados)
{
    *encontrados = 0;
    // vamos a convertirlas en minusculas para que busque coincidencias sin disticion

    for (int i = 0; i < numUsuarios; i++)
    {
        // Convertir ambos strings a minúsculas para comparar
        char nombreMinu[50];
        char busquedaMinu[50];

        // Convertir a minúsculas los nombres
        for (int j = 0; lista[i].nombre[j]; j++)
        {
            nombreMinu[j] = tolower(lista[i].nombre[j]);
        }
        // limpia el buffer
        nombreMinu[strlen(lista[i].nombre)] = '\0';

        for (int j = 0; nombre[j]; j++)
        {
            busquedaMinu[j] = tolower(nombre[j]);
        }
        busquedaMinu[strlen(nombre)] = '\0';

        // Buscar coincidencia parcial
        if (strstr(nombreMinu, busquedaMinu) != NULL)
        {
            indices[(*encontrados)++] = i;
        }
    }

    // opcion funcionable para que sea exclusivo el nombre completo sin mostrar coinidencias. Hace distincion
    /*for (int i = 0; i < numUsuarios; i++)
    {
        if (strcmp(lista[i].nombre, nombre) == 0)
        {
            indices[(*encontrados)++] = i;
        }
    }*/
    return NULL;
}

void buscarModificar(Usuario **lista, int *numUsuario, int *indices, int *encontrados)
{
    int auxiliarEncontrados = *encontrados;
    printf("%d\n", auxiliarEncontrados);
    if (auxiliarEncontrados == 0)
    {
        printf("Usuario no encontrado");
        // return;
    }
    else if (auxiliarEncontrados == 1)
    {
        modificarUsuario(lista, numUsuario, indices[0]);
    }
    else
    {
        printf("\nSe encontraron %d usuarios con ese nombre:\n", auxiliarEncontrados);
        for (int i = 0; i < auxiliarEncontrados; i++)
        {
            Usuario indiceUsuario = (*lista)[indices[i]];
            printf("%d. \tID: %d | Nombre: %s| Edad: %d | Comunidad: %s\n",
                   i + 1, indiceUsuario.id, indiceUsuario.nombre, indiceUsuario.edad, indiceUsuario.comunidad);
        }

        printf("\nSeleccione el número de usuario a modificar (1-%d): ", auxiliarEncontrados);
        int seleccion;
        scanf("%d", &seleccion);
        limpiarBuffer();

        if (seleccion > 0 && seleccion <= auxiliarEncontrados)
        {
            modificarUsuario(lista, numUsuario, indices[seleccion - 1]);
        }
        else
        {
            printf("Selección inválida\n");
        }
    }
}

void modificarUsuario(Usuario **lista, int *numUsuario, int posicion)
{
    if (posicion < 0 || posicion >= *numUsuario)
        return;

    Usuario *modificacion = &(*lista)[posicion];

    printf("\t\t\tEditando al usuario: %s\n", modificacion->nombre);
    printf("Ingrese el nuevo nombre [Actual: %s]: ", modificacion->nombre);
    // gets(modificacion->nombre, NOMBRE, stdin);
    // modificacion->nombre[strcspn(modificacion->nombre, "\n")] = '\0';
    gets(modificacion->nombre);
    // Esta es opcional, solo es de limpieza
    modificacion->nombre[strcspn(modificacion->nombre, "\n")] = '\0';

    printf("Ingrese la nueva edad [Actual: %d]: ", modificacion->edad);
    scanf("%d", &modificacion->edad);
    limpiarBuffer();

    printf("Ingrese el nuevo comunidad [Actual: %s]: ", modificacion->comunidad);
    // gets(modificacion->comunidad, COMUNIDAD, stdin);
    // modificacion->comunidad[strcspn(modificacion->comunidad, "\n")] = '\0';
    gets(modificacion->comunidad);
    // Esta es opcional, solo es de limpieza
    modificacion->comunidad[strcspn(modificacion->comunidad, "\n")] = '\0';

    // Suponiendo que se puede modifcar los puntos
    // printf("Ingrese el nuevo total de puntos ecologicos [Actual: %f]: ", modificacion->puntosTotalesEcologicos);
    // scanf("%f", &modificacion->puntosTotalesEcologicos);
    // limpiarBuffer();
}

void eliminarUsuario(Usuario **lista, int *numUsuario, int posicion)
{
    if (posicion < 0 || posicion >= *numUsuario)
    {
        printf("Usuario no valido");
        return;
    }

    // 1. Mover elementos primero
    for (int i = posicion; i < *numUsuario - 1; i++)
    {
        (*lista)[i] = (*lista)[i + 1];
    }

    // 2. reducir Contador
    (*numUsuario)--;

    // 3. Reajusar memoria solo si quedan elementos
    if (*numUsuario > 0)
    {
        *lista = (Usuario *)realloc(*lista, (*numUsuario) * sizeof(Usuario));
        if (*lista == NULL)
        {
            printf("Advertencia: No se pudo reajustar memoria (pero los datos son validos)\n");
            return;
        }
    }
    else
    {
        // Para liberar bien la memoria si ya no tiene elementos
        if (*lista != NULL)
        {
            free(*lista);
            *lista = NULL; // Buenas prácticas: evitar punteros colgantes
        }
    }
}

void buscarEliminar(Usuario **lista, int *numUsuario, int *indices, int *encontrados)
{
    int opcion;
    int auxiliarEncontrados = *encontrados;
    printf("%d\n", auxiliarEncontrados);
    if (auxiliarEncontrados == 0)
    {
        printf("Usuario no encontrado");
        // return;
    }
    else if (auxiliarEncontrados == 1)
    {
        eliminarUsuario(lista, numUsuario, indices[0]);
    }
    else
    {
        printf("\nSe encontraron %d usuarios con ese nombre:\n", auxiliarEncontrados);
        for (int i = 0; i < auxiliarEncontrados; i++)
        {
            Usuario indiceUsuario = (*lista)[indices[i]];
            printf("%d. \tID: %d | Nombre: %s| Edad: %d | Comunidad: %s\n",
                   i + 1, indiceUsuario.id, indiceUsuario.nombre, indiceUsuario.edad, indiceUsuario.comunidad);
        }

        printf("\nSeleccione el número de usuario a eliminar (1-%d): ", auxiliarEncontrados);
        int seleccion;
        if (scanf("%d", &seleccion) != 1 || seleccion < 1 || seleccion > auxiliarEncontrados)
        {
            limpiarBuffer();
            printf("Selección inválida\n");
            return;
        }
        limpiarBuffer();
        // Confirmación

        printf("¿Eliminar al usuario %d? [1] Si [2] No: ", seleccion);
        int opcion;
        scanf("%d", &opcion);

        if (opcion == 1)
        {
            eliminarUsuario(lista, numUsuario, indices[seleccion - 1]);
            printf("Usuario eliminado\n");
        }
        else
        {
            printf("Operación cancelada\n");
        }
    }
}
