#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define NUM_HILOS 3

typedef struct
{
    char nombre[100];
} ArchivoParam;

void *contar_lineas(void *arg)
{
    ArchivoParam *p = (ArchivoParam *)arg;
    // w escritura, r lectura, a añadir al final, w+, r+, a+ aparte pueden crear el archivo
    FILE *archivo = fopen(p->nombre, "r");
    int *contador = malloc(sizeof(int));
    *contador = 0;

    if (archivo == NULL)
    {
        perror("Error al abrir el archivo, putamadre");
        pthread_exit(contador);
    }
    char linea[256];
    while (fgets(linea, sizeof(linea), archivo))
    {
        (*contador)++;
    }
    fclose(archivo);
    printf("Archivo %s tiene %d lineas: \n", p->nombre, *contador);
    pthread_exit(contador);
}

int main()
{
    printf("INICIO\n");
    pthread_t hilos[NUM_HILOS];
    char *nombres_archivos[NUM_HILOS] = {"file1.txt", "file2.txt", "file3.txt"};
    ArchivoParam parametros[NUM_HILOS];

    for (int i = 0; i < NUM_HILOS; i++)
    {
        strncpy(parametros[i].nombre, nombres_archivos[i], sizeof(parametros[i].nombre));
        pthread_create(&hilos[i], NULL, contar_lineas, &parametros[i]);
    }

    int total_lineas = 0;

    for (int i = 0; i < NUM_HILOS; i++)
    {
        int *resultado;
        pthread_join(hilos[i], (void **)&resultado);
        total_lineas += *resultado;
        free(resultado);
    }

    printf("Total Lineas: %d\n", total_lineas);
    
}