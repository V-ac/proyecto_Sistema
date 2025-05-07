#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <functional>
#include <wchar.h>
#include <string.h>
#include "ranking.h"
#include <windows.h>

extern "C" void mostrarRanking(UsuarioR *lista, int numUsuarios, const char *nombreComunidad)
{

    SetConsoleOutputCP(CP_UTF8);

    // Verificar parámetros
    if (lista == nullptr || numUsuarios == 0 || nombreComunidad == nullptr)
    {
        std::cout << "\nError. Datos inválidos para mostrar el ranking.\n";
        return;
    }

    // Filtrar usuarios de la comunidad específica
    std::vector<UsuarioR> usuariosFiltrados;
    for (int i = 0; i < numUsuarios; i++)
    {
        // if (strcasestr_custom(lista[i].comunidad, nombreComunidad) != nullptr)
        if (strcasecmp(lista[i].comunidad, nombreComunidad) == 0)
        {
            usuariosFiltrados.push_back(lista[i]);
        }
    }

    // Verificar si hay usuarios en la comunidad
    if (usuariosFiltrados.empty())
    {
        std::cout << "\nNo hay usuarios registrados en la comunidad \""
                  << nombreComunidad << "\"\n";
        return;
    }

    // Ordenar descendente por puntos
    std::sort(usuariosFiltrados.begin(), usuariosFiltrados.end(),
              [](const UsuarioR &a, const UsuarioR &b)
              {
                  // std::cout << "a: " << a.nombre << " b: " << a.puntosTotalesEcologicos << "\n";
                  return a.puntosTotalesEcologicos > b.puntosTotalesEcologicos;
              });
    // Obtener máximo para escalar las barras
    float max_puntos = usuariosFiltrados[0].puntosTotalesEcologicos;

    if (max_puntos <= 0)
    {
        max_puntos = 1;
    }
    // Encabezado del ranking
    std::cout << "\nRanking de usuarios de la comunidad \"" << nombreComunidad << "\":\n\n";

    for (int i = 0; i < usuariosFiltrados.size(); i++)
    {
        int bar_length = static_cast<int>((usuariosFiltrados[i].puntosTotalesEcologicos * 40) / max_puntos);
        std::cout << std::left << std::setw(20) << usuariosFiltrados[i].nombre << " | "
                  << std::string(bar_length, '#') << "   " << std::fixed << std::setprecision(1)
                  << usuariosFiltrados[i].puntosTotalesEcologicos
                  << " pts\n";
    }

    // Espacio final como en el ejemplo
    std::cout << "\n";
}
