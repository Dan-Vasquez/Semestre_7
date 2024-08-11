/* Parcial #2 Prog. Paralela
 - Miguel Angel Nivia (8958691)
 - Daniel Andres Vasquez (8963154)
 - Willian Chapid Tobar (8965113)
 
 Codigo #3 Paralelo MPI
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define PROCESS0 0

// Función para calcular el producto matriz-vector
void producto_matriz_vector(int matriz[], int vector[], int resultado[], int filas, int columnas){
    for (int i = 0; i < filas; i++) 
    {
        resultado[i] = 0;
        for (int j = 0; j < columnas; j++) 
        {
            resultado[i] += matriz[i * columnas + j] * vector[j];
        }
    }
}

int main(int argc, char *argv[]){
    int filas, columnas;
    int *matriz = NULL;
    int *resultado = NULL, *vector = NULL;

    int my_rank, p;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (my_rank == PROCESS0) 
    {
        // Proceso maestro
        scanf("%d, %d", &filas, &columnas);
    }
    MPI_Bcast(&filas, 1, MPI_INT, PROCESS0, MPI_COMM_WORLD);
    MPI_Bcast(&columnas, 1, MPI_INT, PROCESS0, MPI_COMM_WORLD);
    vector = (int *)malloc(columnas * sizeof(int));
    if (my_rank == PROCESS0)
    {
        // Asignación de memoria para la matriz
        matriz = (int *)malloc(filas * columnas * sizeof(int));

        // Obtención matriz
        for (int i = 0; i < filas * columnas; i++) {
            scanf("%d,", &matriz[i]);
        }
        // Asignación de memoria para el vector
        
        // Asignación de memoria para la respuesta
        resultado = (int *)malloc(filas * sizeof(int));

        // Obtención Vector
        for (int i = 0; i < columnas; i++) {
            scanf("%d,", &vector[i]);
        }
    }

    // Enviamos las dimensiones de la matriz
    
    // Calculamos cuántas filas le tocan a cada proceso
    int filas_por_proceso = filas / p;
    int *matriz_por_proceso = (int *)malloc(filas_por_proceso * columnas * sizeof(int));
    int *resultado_por_proceso = (int *) malloc(filas_por_proceso*sizeof(int));
    // Enviamos partes de la matriz a cada proceso
    MPI_Scatter(matriz, filas_por_proceso * columnas, MPI_INT, matriz_por_proceso, filas_por_proceso * columnas, MPI_INT, PROCESS0, MPI_COMM_WORLD);

    // Enviamos el vector completo a todos los procesos
    MPI_Bcast(vector, columnas, MPI_INT, PROCESS0, MPI_COMM_WORLD);
    
    // Calculamos el producto de matriz x vector para cada proceso
    producto_matriz_vector(matriz_por_proceso, vector, resultado_por_proceso, filas_por_proceso, columnas);
    // Recopilamos los resultados de cada proceso usando un gather
    MPI_Gather(resultado_por_proceso, filas_por_proceso, MPI_INT, resultado, filas_por_proceso, MPI_INT, PROCESS0, MPI_COMM_WORLD);
    // Imprimir la parte de la matriz recibida por cada proceso
    if (my_rank == PROCESS0) {
        printf("Solucion Matriz x Vector: \n");
        for (int i = 0; i < filas; i++) {
            printf("%d ", resultado[i]);
        }
        printf("\n");

        free(matriz);
        free(vector);
        free(resultado);
    }
    
    free(matriz_por_proceso);
    free(resultado_por_proceso);

    

    MPI_Finalize();
    return 0;
}