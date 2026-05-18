/************************************************************************************************
 * Parcial 1 - Problema 1: Hora Solar Pico (HSP) - 2026                                        *
 *                                                                                              *
 * HSP = integral(I(t) dt, 0, 24) / 1000 [W/m²]                                               *
 *                                                                                              *
 * El sensor almacena 24 mediciones horarias en char irrad[24][6].                              *
 * Valores invalidos: negativos y "NA" -> se reemplazan por el valor previo (o 0).              *
 *                                                                                              *
 * Inciso (a): Funcion para calcular el HSP                                                     *
 * Inciso (b): Estructura que representa al dia solar medido                                    *
 * Inciso (c): Punteros a funcion para elegir metodo numerico                                   *
 *                                                                                              *
 * Como compilar: gcc parcial1.c -o parcial1.exe -Wall                                         *
 ************************************************************************************************/

// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Macros
#define _Horas          ((uint8_t) 24)  // 24 mediciones, una por hora
#define _Max_Char_Irrad ((uint8_t) 6)   // "1100\0" son 5 chars + '\0'
#define _Irrad_Ref      1000.0f         // Irradiancia de referencia [W/m²]
#define _Max_Nombre     ((uint8_t) 50)
#define _Max_Fecha      ((uint8_t) 11)  // "DD/MM/AAAA" + '\0'

// Tipos de Datos - Inciso (b): Estructura del dia solar medido
// La idea es simular un "objeto" en C: datos + punteros a funcion como metodos
typedef struct {
    // Variables de instancia (los datos del dia medido)
    char  nombre_estacion[_Max_Nombre];
    float latitud;
    float longitud;
    char  fecha[_Max_Fecha];                // DD/MM/AAAA
    char  irrad[_Horas][_Max_Char_Irrad];   // Buffer del sensor: 24 strings
    // Metodos (punteros a funcion)
    // calcular_hsp recibe un puntero a funcion para elegir el metodo numerico
    float (*calcular_hsp)(char (*irrad)[_Max_Char_Irrad], float (*metodo)(float *, int));
    float (*max_irradiancia)(char (*irrad)[_Max_Char_Irrad]);
    void  (*estacion_climatica)(char *fecha, float latitud, char *resultado);
} dia_solar_t;

// Prototipos de funciones
float calcular_hsp(char (*irrad)[_Max_Char_Irrad], float (*metodo)(float *, int));
float parsear_irradiancia(char *str, float valor_previo);
float max_irradiancia(char (*irrad)[_Max_Char_Irrad]);
void  estacion_climatica(char *fecha, float latitud, char *resultado);
float metodo_rectangular(float *valores, int n);
float metodo_trapezoidal(float *valores, int n);
void  init_dia_solar(dia_solar_t *dia, char *nombre, float lat, float lon,
                     char *fecha, char (*irrad)[_Max_Char_Irrad]);
void  imprimir_dia_solar(dia_solar_t *dia);

// Funcion principal
int main(void){
    float hsp;
    char estacion[20];
    dia_solar_t dia;

    // Datos de ejemplo: 24 mediciones horarias de irradiancia [W/m²]
    char irrad_ejemplo[_Horas][_Max_Char_Irrad] = {
        "0.00", "0.00", "0.00", "0.00", "0.00",         // 00-04 hs
        "10.0",                                         // 05 hs
        "120",  "350",  "600",  "800",  "950",          // 06-10 hs
        "1050", "1100", "1080",                         // 11-13 hs (pico)
        "NA",                                           // 14 hs - error de medicion
        "850",  "650",                                  // 15-16 hs
        "-1.00",                                        // 17 hs - valor negativo (invalido)
        "300",  "80.0", "5.00",                         // 18-20 hs
        "0.00", "0.00", "0.00"                          // 21-23 hs
    };

    // Inciso (a): Calculo directo del HSP
    printf("---- Inciso (a): Calculo del HSP ----\n");
    hsp = calcular_hsp(irrad_ejemplo, metodo_rectangular);
    printf("HSP (rectangular) = %.2f [hs]\n", hsp);

    hsp = calcular_hsp(irrad_ejemplo, metodo_trapezoidal);
    printf("HSP (trapezoidal) = %.2f [hs]\n", hsp);

    // Inciso (b): Estructura del dia solar
    printf("\n---- Inciso (b): Estructura dia_solar_t ----\n");

    // Inicializo la estructura con los datos del dia medido y los punteros a funcion
    init_dia_solar(&dia, "Buenos Aires - UTN", -34.6f, -58.4f,
                   "06/04/2026", irrad_ejemplo);
    imprimir_dia_solar(&dia);

    // Uso de metodos a traves de la estructura
    // Es como hacer dia.metodo() en un lenguaje orientado a objetos
    hsp = dia.calcular_hsp(dia.irrad, metodo_rectangular);
    printf("HSP del dia (rectangular) = %.2f [hs]\n", hsp);

    printf("Maxima irradiancia = %.1f [W/m2]\n", dia.max_irradiancia(dia.irrad));

    dia.estacion_climatica(dia.fecha, dia.latitud, estacion);
    printf("Estacion climatica: %s\n", estacion);

    // Inciso (c): Seleccion del metodo numerico por el usuario
    printf("\n---- Inciso (c): Seleccion de metodo numerico ----\n");

    // Array de punteros a funcion: cada elemento es un metodo numerico distinto
    // El usuario elige cual usar en tiempo de ejecucion
    float (*metodos[2])(float *, int) = {metodo_rectangular, metodo_trapezoidal};
    char *nombres_metodo[2] = {"Rectangular", "Trapezoidal"};
    int opcion = -1;

    printf("Seleccione metodo de integracion:\n");
    printf("  0 - Rectangular (suma de Riemann)\n");
    printf("  1 - Trapezoidal\n");
    printf("Opcion: ");
    scanf("%d", &opcion);

    if(opcion < 0 || opcion > 1){
        printf("Opcion invalida, se usa Rectangular por defecto.\n");
        opcion = 0;
    }

    // Calculo del HSP con el metodo elegido
    hsp = dia.calcular_hsp(dia.irrad, metodos[opcion]);
    printf("HSP (%s) = %.2f [hs]\n", nombres_metodo[opcion], hsp);

    return 0;
}

// Funciones

// Convierte un string del buffer irrad a float
// Si el valor es "NA" o negativo, devuelve valor_previo (o 0 si es la primera medicion)
// atof() devuelve 0.0 si el string no es un numero valido, pero eso no es 
// un problema aca porque "NA" ya lo filtro antes con strcmp
float parsear_irradiancia(char *str, float valor_previo){
    // Verifico si es "NA" (error de medicion del sensor)
    if(strcmp(str, "NA") == 0) return valor_previo;

    float valor = (float)atof(str); // atof: ASCII to float

    // La irradiancia no puede ser negativa, si lo es descarto la medicion
    if(valor < 0.0f) return valor_previo;

    return valor;
}

// Calcula la Hora Solar Pico: HSP = integral(I(t)dt, 0, 24) / 1000
// Recibe el buffer de strings del sensor y un puntero a funcion con el metodo numerico
// char (*irrad)[6] es un puntero a arrays de 6 chars (equivale a irrad[][6])
float calcular_hsp(char (*irrad)[_Max_Char_Irrad], float (*metodo)(float *, int)){
    float valores[_Horas], valor_previo = 0.0f;
    uint8_t i;

    // Primero paso todos los strings a float, corrigiendo los invalidos
    for(i=0; i<_Horas; i++){
        valores[i] = parsear_irradiancia(irrad[i], valor_previo);
        valor_previo = valores[i]; // Guardo por si el proximo es "NA"
    }

    // Llamo al metodo numerico a traves del puntero a funcion
    float integral = metodo(valores, _Horas);

    return integral / _Irrad_Ref;
}

// Metodo rectangular: Integral ~= Suma f(i)*dt, como dt=1h es solo la suma
float metodo_rectangular(float *v, int n){
    float s = 0;
    for(int i=0; i<n; i++) s += v[i];
    return s;
}

// Metodo trapezoidal: Integral ~= Suma (f(i)+f(i+1))/2 * dt
// Mas preciso que el rectangular porque promedia entre muestras consecutivas
float metodo_trapezoidal(float *v, int n){
    float s = 0;
    for(int i=0; i<n-1; i++) s += (v[i] + v[i+1]) / 2.0f;
    return s;
}

// Devuelve el mayor valor valido de irradiancia del dia
float max_irradiancia(char (*irrad)[_Max_Char_Irrad]){
    float maximo = 0.0f, valor_previo = 0.0f, val;
    uint8_t i;

    for(i=0; i<_Horas; i++){
        val = parsear_irradiancia(irrad[i], valor_previo);
        if(val > maximo) maximo = val;
        valor_previo = val;
    }

    return maximo;
}

// Determina la estacion del anio segun fecha y latitud
// En hemisferio sur las estaciones estan invertidas respecto al norte
void estacion_climatica(char *fecha, float latitud, char *resultado){
    int mes = 0, trimestre, indice;
    char *estaciones[] = {"Invierno", "Primavera", "Verano", "Otono"};

    // Extraigo el mes de la fecha (formato DD/MM/AAAA)
    char *ptr = strchr(fecha, '/');
    if(ptr != NULL) mes = atoi(ptr + 1);

    if(mes < 1 || mes > 12){
        strcpy(resultado, "Error fecha");
        return;
    }

    trimestre = (mes - 1) / 3;  // 0=Ene-Mar, 1=Abr-Jun, 2=Jul-Sep, 3=Oct-Dic

    // Para hemisferio sur, desplazo 2 trimestres
    if(latitud >= 0.0f) indice = trimestre;
    else indice = (trimestre + 2) % 4;

    strcpy(resultado, estaciones[indice]);
}

// Constructor: inicializa la estructura y le asigna los punteros a funcion
// Es como el __init__ de Python o el constructor de una clase en C++
void init_dia_solar(dia_solar_t *dia, char *nombre, float lat, float lon,
                    char *fecha, char (*irrad)[_Max_Char_Irrad]){
    // strncpy para no desbordar el buffer (a diferencia de strcpy)
    strncpy(dia->nombre_estacion, nombre, _Max_Nombre - 1);
    dia->nombre_estacion[_Max_Nombre - 1] = '\0'; // Me aseguro de terminar el string
    dia->latitud  = lat;
    dia->longitud = lon;
    strncpy(dia->fecha, fecha, _Max_Fecha - 1);
    dia->fecha[_Max_Fecha - 1] = '\0';

    // Copio las 24 mediciones (24 * 6 = 144 bytes)
    memcpy(dia->irrad, irrad, _Horas * _Max_Char_Irrad);

    // Asigno los metodos: cada puntero apunta a la funcion correspondiente
    dia->calcular_hsp       = calcular_hsp;
    dia->max_irradiancia    = max_irradiancia;
    dia->estacion_climatica = estacion_climatica;
}

// Imprime los datos del dia solar
void imprimir_dia_solar(dia_solar_t *dia){
    float valor_previo = 0.0f, val;
    uint8_t i;

    printf("Estacion: %s\n", dia->nombre_estacion);
    printf("Ubicacion: lat=%.1f, lon=%.1f\n", dia->latitud, dia->longitud);
    printf("Fecha: %s\n", dia->fecha);
    printf("Mediciones de irradiancia [W/m2]:\n");

    for(i=0; i<_Horas; i++){
        val = parsear_irradiancia(dia->irrad[i], valor_previo);
        printf("  %02u hs: %-6s -> %.1f", i, dia->irrad[i], val);
        if(strcmp(dia->irrad[i], "NA") == 0) printf(" (corregido: NA)");
        else if(atof(dia->irrad[i]) < 0.0f) printf(" (corregido: negativo)");
        printf("\n");
        valor_previo = val;
    }
}
