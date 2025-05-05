// #include <iostream>
// #include <vector>
// #include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //para el tiempo
#include <windows.h>

#include <locale.h> // Para configuración regional
#include <wchar.h>  // Para caracteres anchos
#include "utilidades.h"

void generarRanking(Usuario *lista, int numUsuarios)
{
    // Estructura que verifica que usuario no esta en null
    Usuario *copiaLista = lista;
    // Reporte *usuarioDestacado;
    if (copiaLista == NULL || numUsuarios == 0)
    {
        printf("\nNo hay usuarios registrados.\n");
        return;
    }
    // Ya verificado vamos a acomodar los valores
    for (int i = 0; i < numUsuarios - 1; i++)
    {
        for (int j = 0; j < numUsuarios - i; i++)
        {
            if (copiaLista[j].puntosTotalesEcologicos < copiaLista[j + 1].puntosTotalesEcologicos)
            {
                // Intercambio de valores
                Usuario temporal = copiaLista[j];
                copiaLista[j] = copiaLista[j + 1];
                copiaLista[j + 1] = temporal;
            }
        }
    }
    // strcpy(copiaLista[0], usuarioDestacado->usuarioDestactado);
}

void buscarGenerar(Usuario **lista, int *numUsuario, int *indices, int *encontrados)
{
    if (*encontrados == 0)
    {
        printf("Usuario no encontrado");
        // return;
    }
    else if (*encontrados == 1)
    {
        generarResumenUsuario(lista, numUsuario, indices[0]);
    }
    else
    {
        printf("\nSe encontraron %d usuarios con ese nombre:\n", *encontrados);
        for (int i = 0; i < *encontrados; i++)
        {
            Usuario indiceUsuario = (*lista)[indices[i]];
            printf("%d. \tID: %d | Nombre: %s| Edad: %d | Comunidad: %s\n",
                   i + 1, indiceUsuario.id, indiceUsuario.nombre, indiceUsuario.edad, indiceUsuario.comunidad);
        }

        printf("\nSeleccione el número de usuario (1-%d): ", *encontrados);
        int seleccion;
        scanf("%d", &seleccion);
        limpiarBuffer();

        if (seleccion > 0 && seleccion <= *encontrados)
        {
            generarResumenUsuario(lista, numUsuario, indices[seleccion - 1]);
        }
        else
        {
            printf("Selección inválida\n");
        }
    }
}

void generarResumenUsuario(Usuario **lista, int *numUsuario, int posicion)
{

    // Generar resumen
    // Verificar si hay usuarios
    if (lista == NULL || *numUsuario == 0)
    {
        printf("No hay usuarios registrados");
        return;
    }
    Usuario *usuario = &(*lista)[posicion];

    // Ahora vamos a imprimir los datos
    // Imprimir encabezado
    printf("\n\n+----------------------------------------------------+\n");
    printf(" \t\tResumen de Actividades\t\t      \n");
    printf("+----------------------------------------------------+\n");

    // Usuario
    printf(" Usuario: %s\n", usuario->nombre);
    printf(" Comunidad: %s\n\n", usuario->comunidad);

    // Actividades
    printf(" Actividades Registradas:\n");
    printf("------------------------------------------------------\n");
    printf("| %-10s | %-30s | %-10s |\n", "Fecha", "Actividad", "Puntos");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < usuario->numActividadesRealizadas; i++)
    {
        printf("| %-10s | %-30s | %-10.2f |\n",
               usuario->actividades[i].fecha, usuario->actividades[i].nombre, usuario->actividades[i].puntos);
    }

    printf("------------------------------------------------------\n");
    printf("Total de puntos: %.2f\n", usuario->puntosTotalesEcologicos);
    if (usuario->puntosTotalesEcologicos > 0)
    {
        mensajeMotivacion(usuario->puntosTotalesEcologicos);
    }
    printf("\n------------------------------------------------------\n\n\n");
}

void mensajeMotivacion(float puntos)
{
    // Generamos el arreglo con las frases:
    const char *frases[] = {
        "¡Sigue acumulando puntos!",
        "¡Lo lograste! Con %.2f puntos, demuestras que cada pequeña acción cuenta",
        "¡Wow! Tus %.2f puntos son semillas de cambio. ¡Cultiva más acciones verdes!",
        "¡Eres un campeón/a de la sostenibilidad! %.2f puntos demuestran tu compromiso",
        "Con %.2f puntos, eres ejemplo de que cuidar el ambiente ¡sí vale la pena! Comparte tu éxito",
        "¡Vas como cohete! %.2f puntos te acercan al podio ecológico. ¡No pares!",
        "Cada punto suma. ¡Y tú ya llevas %.2f! Imagina el cambio si todos siguen tu ejemplo",
        "¡El planeta festeja tus %.2f puntos! Sembraste acciones, cosecharás un futuro mejor"};

    if (puntos >= 1000)
    {
        printf("\n¡Leyenda verde en construcción! (Puntos: %d)\n", puntos);
    }
    else if (puntos >= 500 && puntos <= 550)
    {
        printf("\n¡Felicidades! Has superado los %.2f puntos y tu impacto positivo en el planeta es inspirador. ¡Sigue así!\n", 500.0f);
    }
    else if (puntos >= 100 && puntos <= 150)
    {
        printf("\n¡Boom! Rompiste la barrera de %.2f puntos. El planeta te lo agradece. ¡A por más!\n", 100.0f);
    }
    else if (puntos >= 50 && puntos <= 70)
    {
        printf("\n¡Vas por buen camino! (Puntos: %d)\n", puntos);
    }
    else
    {
        const int num_frases = sizeof(frases) / sizeof(frases[0]); // Tamaño automático
        // Generar índice seguro (0 <= indice < num_frases)
        int indice = rand() % num_frases; // Esto NUNCA excederá el rango

        if (strstr(frases[indice], "%.2f") != NULL)
        {
            printf(frases[indice], puntos); // Para frases con un %.2f
        }
        else
        {
            printf("\n%s\n", frases[indice]); // Para frases sin formato
        }
    }
}

void generarReporteTxT(Usuario *lista, int *numUsuario)
{
    // SetConsoleOutputCP(CP_UTF8); // ¡Solución clave! Para los caracteres especiales
    //  Verificar si hay usuarios
    float totalPuntos = 0;
    if (lista == NULL || *numUsuario == 0)
    {
        printf("No hay usuarios registrados");
        return;
    }

    FILE *archivo = fopen("Reporte_Usuarios.txt", "w");

    if (archivo == NULL)
    {
        printf("Error al generar el reporte\n");
        return;
    }
    // Reporte *reporte;
    //  Obtener la fecha actual
    char fechaHoy[11];
    obtenerFechaActual(fechaHoy);
    fprintf(archivo, "\n===================== Reporte General =====================\n");
    fprintf(archivo, "Fecha: %s\n", fechaHoy);
    fprintf(archivo, "| %-3s | %-35s | %-35s | %-10s | %-5s\n", "ID", "Nombre", "Comunidad", "Puntos", "Actividades");
    fprintf(archivo, "------------------------------------------------------\n");

    for (int i = 0; i < *numUsuario; i++)
    {
        fprintf(archivo, "| %-3d | %-35s | %-35s | %-10.2f | %-5d\n",
                lista[i].id, lista[i].nombre, lista[i].comunidad,
                lista[i].puntosTotalesEcologicos, lista[i].numActividadesRealizadas);
        totalPuntos += lista[i].puntosTotalesEcologicos;
    }

    // Buscar usuario con más puntos (destacado)
    int indiceDestacado = 0;
    for (int i = 1; i < *numUsuario; i++)
    {
        if (lista[i].puntosTotalesEcologicos > lista[indiceDestacado].puntosTotalesEcologicos)
        {
            indiceDestacado = i;
        }
    }

    float puntos = totalPuntos / (float)(*numUsuario);
    char *actividad = actividadComun(lista, *numUsuario);
    char *comunidad = comunidadComun(lista, *numUsuario);
    char *usuarioDestacado = lista[indiceDestacado].nombre;
    int puntosUsuarioDestacadoInt = (int)lista[indiceDestacado].puntosTotalesEcologicos;

    fprintf(archivo, "------------------------------------------------------\n");
    fprintf(archivo, "Total usuarios registrados: %d\n", *numUsuario);
    fprintf(archivo, "Total puntos generados: %.2f\n", totalPuntos);
    fprintf(archivo, "Actividad más común: %s\n", actividad);
    fprintf(archivo, "Comunidad con más usuarios activos: %s\n", comunidad);
    fprintf(archivo, "Usuario destacado del mes: %s (%d puntos)\n", usuarioDestacado, puntosUsuarioDestacadoInt);
    fprintf(archivo, "Promedio de puntos por usuario: %.2f\n", puntos);
    fclose(archivo);
}

void obtenerFechaActual(char *fechaActual)
{
    time_t tiempo_actual;
    struct tm *info_tiempo;
    char fecha[11]; // Suficiente para AAAA-MM-DD + carácter nulo

    time(&tiempo_actual);
    info_tiempo = localtime(&tiempo_actual);

    strftime(fecha, sizeof(fecha), "%Y-%m-%d", info_tiempo);
    strcpy(fechaActual, fecha);
}

void generarReporte(Usuario *lista, int *numUsuario)
{
    // SetConsoleOutputCP(CP_UTF8); // ¡Solución clave! Para los caracteres especiales
    //  Verificar si hay usuarios
    float totalPuntos = 0;
    if (lista == NULL || *numUsuario == 0)
    {
        printf("No hay usuarios registrados");
        return;
    };
    //  Obtener la fecha actual
    char fechaHoy[11];
    obtenerFechaActual(fechaHoy);
    printf("\n===================== Reporte General =====================\n");
    printf("Fecha: %s\n\n\n", fechaHoy);
    printf("| %-3s | %-35s | %-35s | %-10s | %-5s\n", "ID", "Nombre", "Comunidad", "Puntos", "Actividades");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < *numUsuario; i++)
    {
        printf("| %-3d | %-35s | %-35s | %-10.2f | %-5d\n",
               lista[i].id, lista[i].nombre, lista[i].comunidad,
               lista[i].puntosTotalesEcologicos, lista[i].numActividadesRealizadas);
        totalPuntos += lista[i].puntosTotalesEcologicos;
    }

    // Buscar usuario con más puntos (destacado)
    int indiceDestacado = 0;
    for (int i = 1; i < *numUsuario; i++)
    {
        if (lista[i].puntosTotalesEcologicos > lista[indiceDestacado].puntosTotalesEcologicos)
        {
            indiceDestacado = i;
        }
    }

    float puntos = totalPuntos / (float)(*numUsuario);
    char *actividad = actividadComun(lista, *numUsuario);
    char *comunidad = comunidadComun(lista, *numUsuario);
    char *usuarioDestacado = lista[indiceDestacado].nombre;
    int puntosUsuarioDestacadoInt = (int)lista[indiceDestacado].puntosTotalesEcologicos;
    printf("------------------------------------------------------\n");
    printf("Total usuarios registrados: %d\n", *numUsuario);
    printf("Total puntos generados: %.2f\n", totalPuntos);
    printf("Actividad más común: %s\n", actividad);
    printf("Comunidad con más usuarios activos: %s\n", comunidad);
    printf("Usuario destacado del mes: %s (%d puntos)\n", usuarioDestacado, puntosUsuarioDestacadoInt);
    printf("Promedio de puntos por usuario: %.2f\n", puntos);
}
