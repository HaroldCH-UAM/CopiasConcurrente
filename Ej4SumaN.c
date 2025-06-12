#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1001
#define NUM_HILOS 4

int parciales[NUM_HILOS];

void *suma_parcial(void *arg)
{
    int indice = *(int *)arg;
    int paso = N / NUM_HILOS;
    int inicio = (indice * paso) + 1;
    int fin = (indice == NUM_HILOS - 1) ? N : (indice + 1) * paso;

    int suma = 0;
    for (int i = inicio; i <= fin; i++)
    {
        suma += i;
    }
    parciales[indice] = suma;
    pthread_exit(NULL);
}

int main()
{
    pthread_t hilos[NUM_HILOS];
    int indices[NUM_HILOS];

    for (int i = 0; i < NUM_HILOS; i++)
    {
        indices[i] = i;
        pthread_create(&hilos[i], NULL, suma_parcial, &indices[i]);
    }

    for (int i = 0; i < NUM_HILOS; i++)
    {
        pthread_join(hilos[i], NULL);
    }
    
    int suma_total = 0;

    for (int i = 0; i < NUM_HILOS; i++)
    {
        suma_total += parciales[i];
    }
    
    printf("Suma total de 1 hasta %d = %d\n", N, suma_total);


}