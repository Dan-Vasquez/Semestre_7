/*******************************************************************************
*                                                                              *
*  for1.c - A program to illustrate using
*           the parallel for directive
*                                                                              *
*   Departamento de Electronica y Ciencias de la Computacion                   *
*   Pontificia Universidad Javeriana - CALI                                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <omp.h>

#define SIZE  1024

void vectAdd(double *a, double *b, double *y, int n);

int main(int argc, char *argv[]) {
    double  a[SIZE],
            b[SIZE],
            y[SIZE];

    // Inicializar los vectores a y b
    for (int i = 0; i < SIZE; i++) {
        a[i] = 1.0;
        b[i] = 2.0;
    }

    // Ejecutar la función vectAdd
    vectAdd(a, b, y, SIZE);

    // Imprimir los primeros valores del vector resultante y
    printf("Resultado:\n");
    for (int i = 0; i < 10; i++) {
        printf("%f ", y[i]);
    }
    printf("\n");
  
    return (0);
}

void vectAdd(double *a, double *b, double *y, int n) {
    int i;

    // Se imprime el número de hilos utilizados
    printf("Número de hilos: %d\n", omp_get_max_threads());

    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        // Se imprime qué hilo está ejecutando cada iteración
        printf("Hilo %d ejecutando iteración %d\n", omp_get_thread_num(), i);
        y[i] = a[i] + b[i];
    }
}
