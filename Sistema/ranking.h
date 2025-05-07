#ifndef RANKING_H
#define RANKING_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        char nombre[50];
        float puntos;
        char tipoActividad[20];
        char fecha[11];

    } ActividadR;

    typedef struct
    {
        int id;
        char nombre[50];
        int edad;
        char comunidad[50];
        float puntosTotalesEcologicos;
        ActividadR actividades[50];
        int numActividadesRealizadas; // Contador de actividades registradas
    } UsuarioR;

    void mostrarRanking(UsuarioR *lista, int numUsuarios, const char *nombreComunidad);

#ifdef __cplusplus
}
#endif

#endif
