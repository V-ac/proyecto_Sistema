#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilidades.h"

void guardarDatos(Usuario *lista, int numUsuario, int ultimoID)
{
    FILE *archivo = fopen("registro.bin", "wb");
    if (archivo == NULL)
    {
        printf("Error al guardar datos\n");
        return;
    }
    // Primero guarda el último ID
    fwrite(&ultimoID, sizeof(int), 1, archivo); // separado para que no haya problema, ya que solo recibe 4 datos
    // Luego guarda los usuarios
    fwrite(lista, sizeof(Usuario), numUsuario, archivo);
    fclose(archivo);
}

void cargarDatos(Usuario **lista, int *numUsuarios, int *ultimoID)
{
    FILE *archivo = fopen("registro.bin", "rb");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo 'registro.bin' (puede que no exista)\n");
        return;
    }

    // Primero lee el último ID guardado
    if (fread(ultimoID, sizeof(int), 1, archivo) != 1)
    {
        printf("Error al leer el último ID\n");
        fclose(archivo);
        return;
    }

    // Calcula el tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    long file_size = ftell(archivo) - sizeof(int); // Restamos el tamaño del ID que ya leímos

    // Si el archivo está vacío, salir
    if (file_size <= 0)
    {
        printf("El archivo está vacío\n");
        fclose(archivo);
        return;
    }

    // Vuelve al inicio del archivo para leer
    // fseek(archivo, 0, SEEK_SET);
    fseek(archivo, sizeof(int), SEEK_SET); // Nos posicionamos después del ID

    // Calcula el número de estudiantes
    *numUsuarios = file_size / sizeof(Usuario);

    // Asigna memoria
    *lista = (Usuario *)malloc(*numUsuarios * sizeof(Usuario));
    if (*lista == NULL)
    {
        printf("Error al asignar memoria\n");
        fclose(archivo);
        return;
    }

    // Lee los datos
    // size_t elementos_leidos = fread(*lista, sizeof(Usuario), archivo);
    size_t elementos_leidos = fread(*lista, sizeof(Usuario), *numUsuarios, archivo);
    fclose(archivo);

    if (elementos_leidos != *numUsuarios)
    {
        printf("Error: No se leyeron todos los datos correctamente\n");
        free(*lista); // Libera memoria si hubo error
        *lista = NULL;
        *numUsuarios = 0;
        *ultimoID = 100;
    }
}
