#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilidades.h"

int validaFecha = 0;
int invalidaF = 0;
int añoBisiesto = 0;
void regReciclaje(Usuario **lista, int *numUsuario, int posicion)
{
    if (posicion < 0 || posicion >= *numUsuario)
    {
        printf("Error. No hay usuarios");
        return;
    }

    registrarActividades(lista, posicion, "reciclaje", "kilos", 1.5f);
}

void regDuchaCorta(Usuario **lista, int *numUsuario, int posicion)
{
    if (posicion < 0 || posicion >= *numUsuario)
    {
        printf("Error. No hay usuarios");
        return;
    }

    registrarActividades(lista, posicion, "ducha corta", "minutos", 3.0f);
}

void regTransporte(Usuario **lista, int *numUsuario, int posicion)
{
    if (posicion < 0 || posicion >= *numUsuario)
    {
        printf("Error. No hay usuarios");
        return;
    }

    registrarActividades(lista, posicion, "trasnporte sustentable", "kilometros", 4.5f);
}

void registrarActividades(Usuario **lista, int posicion, const char *tipoActividad, const char *tipoValor, float valorPuntos)
{
    // Registro de actividad

    Usuario *usuario = &(*lista)[posicion];
    // verifica que no pase de las 50 que se pueden registar
    if (usuario->numActividadesRealizadas >= MAX_ACTIVIDADES)
    {
        printf("Límite de actividades alcanzado (Puntos totales: %.2f)\n", usuario->puntosTotalesEcologicos);
        return;
    }

    // Estructura de actividad. Puntero temporal para manipular la actividad
    Actividad *registro = &usuario->actividades[usuario->numActividadesRealizadas];
    // Reporte *reporte;

    // Regitro de tipo de actividad
    strncpy(registro->tipoActividad, tipoActividad, 19);
    registro->tipoActividad[19] = '\0';

    // Nombre de la actividad
    printf("Nombre de la actividad de %s: ", tipoActividad);
    gets(registro->nombre);
    registro->nombre[strcspn(registro->nombre, "\n")] = '\0';

    // Valores
    float auxPuntos;
    printf("Introduce los %s: ", tipoValor);
    while (scanf("%f", &auxPuntos) != 1 || auxPuntos < 0)
    {
        limpiarBuffer();
        printf("Valor inválido. Ingrese un número positivo: ");
    }
    limpiarBuffer();
    // fecha
    // vamos a evitar que quiera poner otros datos no correctos

    printf("\t\t\tEn formato AAAA-MM-DD\n");
    printf("Fecha de la actividad: ");
    do
    {
        // almacena la fecha
        gets(registro->fecha);
        registro->fecha[strcspn(registro->fecha, "\n")] = '\0';
        printf("\nvalidaFecha: %d\n", validaFecha);
        validarFecha(registro->fecha);
        // valida la fecha
        if (validaFecha == 0)
        {
            printf("Formato inválido. Ingrese nuevamente (AAAA-MM-DD): ");
        }

    } while (validaFecha != 1); // vamos a usar el valor como una ayuda para un booleano

    // Vamos a sacar los puntos ecologicos de acuerdo con ciertos criterios
    // 1.5 puntos ecologicos por cada kg
    // 3 puntos ecologicos por cada min
    // 4.5 puntos ecologicos por cada km

    registro->puntos = auxPuntos * valorPuntos;
    printf("\tPuntos registrados: %.2f\n", registro->puntos);

    // Actualizar contador y puntos totales
    usuario->puntosTotalesEcologicos += registro->puntos;
    usuario->numActividadesRealizadas++;
    printf("\tPuntos totales: %.2f\n", usuario->puntosTotalesEcologicos);
    // reporte->totalPuntosGenerados = usuario->puntosTotalesEcologicos;
    validaFecha = 0;
}

void registrarBuscar(Usuario **lista, int *numUsuario, int *indices, int *encontrados, const char *tipo)
{
    if (*encontrados == 0)
    {
        printf("Usuario no encontrado\n");
        return;
    }

    else if (*encontrados == 1)
    {
        if (strcmp(tipo, "reciclaje") == 0)
        {
            regReciclaje(lista, numUsuario, indices[0]);
        }
        else if (strcmp(tipo, "ducha") == 0)
        {
            regDuchaCorta(lista, numUsuario, indices[0]);
        }
        else if (strcmp(tipo, "transporte") == 0)
        {
            regTransporte(lista, numUsuario, indices[0]);
        }
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

        printf("\nSeleccione el número de usuario para registrar actividad (1-%d): ", *encontrados);
        int seleccion;
        scanf("%d", &seleccion);
        limpiarBuffer();

        if (seleccion > 0 && seleccion <= *encontrados)
        {
            if (strcmp(tipo, "reciclaje") == 0)
            {
                regReciclaje(lista, numUsuario, indices[seleccion - 1]);
            }
            else if (strcmp(tipo, "ducha") == 0)
            {
                regDuchaCorta(lista, numUsuario, indices[seleccion - 1]);
            }
            else if (strcmp(tipo, "transporte") == 0)
            {
                regTransporte(lista, numUsuario, indices[seleccion - 1]);
            }
        }
        else
        {
            printf("Selección inválida\n");
        }
    }
}

void esBisiesto(int año)
{

    if ((año % 4 == 0 && año % 100 != 0) || (año % 400 == 0))
    {
        añoBisiesto = 1;
    }
}

void validarFecha(const char *fecha)
{
    // Reiniciamos banderas
    validaFecha = 0;
    invalidaF = 1; // Asumimos que es inválido hasta que se demuestre lo contrario
    // verifica la longitud
    if (strlen(fecha) != 10)
    {
        return;
    }
    // verifica los guiones en las posiciones correctas
    if (fecha[4] != '-' || fecha[7] != '-')
    {
        return;
    }

    // verificar que los demás caracteres sean dígitos
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
        {
            continue; // Saltar guiones
        }

        if (!isdigit(fecha[i])) // verifica si son numeros
        {
            return;
        }
    }

    // Extraemos los componentes para verificar que efectivamente es una fecha logica
    // ejemplo de como funciona esto: 2025-04-29. atoi solo almacena los puros numeros
    int año = atoi(fecha);     // 2025
    int mes = atoi(fecha + 5); // 04 (porque especificamos que empiece pasado la posicion 5, asi que se salta 2025-)
    int dia = atoi(fecha + 8); // 29 (igual que el caso anterior pero aqui empieza pasando 2025-04-)

    // validamos rango de mes
    if (mes < 1 || mes > 12)
    {
        return;
    }

    // validamos dia segun el mes ingresado
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // verificamos si el año que ingreso el bisiesto para cambiar el valor del mes de febrero por 29 dias para que no de error y se cicle
    if (añoBisiesto == 1)
    {
        diasPorMes[1] = 29; // Febrero en año bisiesto
    }

    // validamos que el dia sea correcto en el mes indicado
    /* "dia < 1 || dia > diasPorMes[mes - 1]"
        vamos a desenglosar que hace cada cosa.
        1 . dia < 1  --- evita numeros negativos o 0
        2. dia > diasPorMes[mes - 1]  ---- evita que el numero sea mayor de los dias del mes por ejemplo 2025-04-32 esta fecha no existe
        3. diasPorMes[mes - 1] solo estamos ajustando los indices del arreglo para que empiece desde el indice 0
    */
    if (dia < 1 || dia > diasPorMes[mes - 1])
    {
        return;
    }

    // validar año y que sea razonable (ejemplo: entre 1980 - 2100)
    if (año < 1980 || año > 2100)
    {
        return;
    }

    // Si cumple con todo, entonces rompemos el ciclo del do haciendo la variable validaFecha = 1
    validaFecha = 1;
    invalidaF = 0;
}

char *actividadComun(Usuario *lista, int numUsuario)
{
    if (numUsuario == 0 || lista == NULL)
    {
        return "No usuarios registrados";
    }
    // Inicializar contadores para los 3 tipos
    int reciclaje = 0, ducha = 0, transporte = 0;
    for (int i = 0; i < numUsuario; i++)
    {
        for (int j = 0; j < lista[i].numActividadesRealizadas; j++)
        {
            char *tipo = lista[i].actividades[j].tipoActividad;

            if (strcasecmp(tipo, "reciclaje") == 0)
            {
                reciclaje++;
            }
            else if (strcasecmp(tipo, "ducha corta") == 0)
            {
                ducha++;
            }
            else if (strcasecmp(tipo, "transporte") == 0)
            {
                transporte++;
            }
        }
    }
    // Determinar la actividad más común
    if (reciclaje >= ducha && reciclaje >= transporte)
    {
        return "Reciclaje";
    }
    else if (ducha >= reciclaje && ducha >= transporte)
    {
        return "Ducha corta";
    }
    else
    {
        return "Transporte sustentable";
    }
}

char *comunidadComun(Usuario *lista, int numUsuario)
{
    if (numUsuario == 0 || lista == NULL)
    {
        return "No hay comunidades";
    }

    ComunidadContador comunidades[50] = {0};
    int numComunidades = 0;

    // Contar comunidades
    for (int i = 0; i < numUsuario; i++)
    {
        int encontrada = 0;

        // Buscar si la comunidad ya está registrada
        for (int j = 0; j < numComunidades; j++)
        {
            if (strcasecmp(lista[i].comunidad, comunidades[j].nombre) == 0)
            {
                comunidades[j].cantidad++;
                encontrada = 1;
                break;
            }
        }

        // Si no se encontró, agregar nueva comunidad
        if ((encontrada == 0) && (numComunidades < 50))
        {
            strncpy(comunidades[numComunidades].nombre, lista[i].comunidad, 49);
            comunidades[numComunidades].nombre[49] = '\0'; // Asegurar terminación nula
            comunidades[numComunidades].cantidad = 1;
            numComunidades++;
        }
    }

    // Encontrar la comunidad con mayor cantidad
    int maxIndex = 0;
    for (int i = 1; i < numComunidades; i++)
    {
        if (comunidades[i].cantidad > comunidades[maxIndex].cantidad)
        {
            maxIndex = i;
        }
    }

    char *comunidadMasComun = comunidades[maxIndex].nombre;

    return comunidadMasComun;
}
