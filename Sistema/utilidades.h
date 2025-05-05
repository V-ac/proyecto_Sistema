#ifndef UTILIDADES_H
#define UTILIDADES_H

#define ID 50
#define NOMBRE 50
#define COMUNIDAD 50
#define PUNTOSECOLOGICOS 3
#define MAX_USUARIOS 100
#define MAX_ACTIVIDADES 50
#define TIPO 20
#define FECHA 11
#define MENSAJE 50

typedef struct
{
    char nombre[NOMBRE];
    float puntos;
    char tipoActividad[TIPO];
    char fecha[FECHA];

} Actividad;

typedef struct
{
    int id;
    char nombre[NOMBRE];
    int edad;
    char comunidad[COMUNIDAD];
    float puntosTotalesEcologicos;
    Actividad actividades[MAX_ACTIVIDADES];
    int numActividadesRealizadas; // Contador de actividades registradas
} Usuario;

typedef struct
{
    char nombre[50];
    int cantidad;
} ComunidadContador;
// Usuario
void limpiarBuffer();
void agregarUsuario(Usuario **lista, int *numUsuario, int *ultimoID);
void mostrarListaUsuarios(Usuario *lista, int numUsuario);
Usuario *buscarUsuario(Usuario *lista, int numUsuarios, const char *nombre, int *indices, int *encontrados);
void buscarModificar(Usuario **lista, int *numUsuario, int *indices, int *encontrados);
void modificarUsuario(Usuario **lista, int *numUsuario, int posicion);
void eliminarUsuario(Usuario **lista, int *numUsuario, int posicion);
void buscarEliminar(Usuario **lista, int *numUsuario, int *indices, int *encontrados);

// Accciones
void guardarDatos(Usuario *lista, int numUsuario, int ultimoID);
void cargarDatos(Usuario **lista, int *numUsuarios, int *ultimoID);

// Actividades
void regReciclaje(Usuario **lista, int *numUsuario, int posicion);
void regDuchaCorta(Usuario **lista, int *numUsuario, int posicion);
void regTransporte(Usuario **lista, int *numUsuario, int posicion);
void registrarActividades(Usuario **lista, int posicion, const char *tipoActividad, const char *tipoValor, float valorPuntos);
void registrarBuscar(Usuario **lista, int *numUsuario, int *indices, int *encontrados, const char *tipo);
void esBisiesto(int año);
void validarFecha(const char *fecha);
char *actividadComun(Usuario *lista, int numUsuario);
char *comunidadComun(Usuario *lista, int numUsuario);

// Reportes
void generarRanking(Usuario *lista, int numUsuarios);
void generarResumenUsuario(Usuario **lista, int *numUsuario, int posicion);
void generarReporte(Usuario *lista, int *numUsuario);
void generarReporteTxT(Usuario *lista, int *numUsuario);
void mensajeMotivacion(float puntos);
void buscarGenerar(Usuario **lista, int *numUsuario, int *indices, int *encontrados);
void obtenerFechaActual(char *fechaActual);
// void barraHorizontal();

#endif
