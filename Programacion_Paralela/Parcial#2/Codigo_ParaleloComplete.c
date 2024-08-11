/* Parcial #2 Prog. Paralela
 - Miguel Angel Nivia (8958691)
 - Daniel Andres Vasquez (8963154)
 - Willian Chapid Tobar (8965113)
 
 Codigo #4 Paralelo OpenMP + MPI(Complete)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>

#define PROCESS0 0


void producto_matriz_vector(int matriz[], int vector[], int resultado[], int filas, int columnas){
    #pragma omp parallel for collapse(2) shared(matriz, vector, resultado, filas, columnas)
    for (int i = 0; i < filas; i++) 
    {
      for (int j = 0; j < columnas; j++) 
      {
          //#pragma omp atomic
          resultado[i] += matriz[i * columnas + j] * vector[j];
      }
    }
}
void producto_matriz_vector_secuencial(int matriz[], int vector[], int resultado[], int filas, int columnas){
    for (int i = 0; i < filas; i++) 
    {
      resultado[i] = 0;
      for (int j = 0; j < columnas; j++) 
      {
          resultado[i] += matriz[i * columnas + j] * vector[j];
      }
    }
}
int main(int argc, char *argv[]) {
	int filas, columnas;
  int *matriz = NULL, *resultado = NULL, *vector = NULL;
  double scomm_time, ecomm_time;
	int  my_rank, p;
	MPI_Init ( &argc, &argv );
  scomm_time = MPI_Wtime();
  MPI_Comm_size ( MPI_COMM_WORLD, &p );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );
  ecomm_time = MPI_Wtime () - scomm_time;
  
  if ( my_rank == PROCESS0 )
  {
    scanf("%d, %d", &filas, &columnas);
    printf ( "\nThe time will be measured in multiples of %.1e seconds\n", MPI_Wtick () );
    printf ( "\nThe initialisation phase of MPI took %.3f seconds\n", ecomm_time );
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
  
  // CODIGO DE SOLUCION
  
  if ( my_rank == PROCESS0 )
  {
    printf("Solucion Matriz x Vector Paralela OpenMP y MPI: \n");
        for (int i = 0; i < filas; i++) {
            printf("%d ", resultado[i]);
        }
        printf("\n");
    int *resultado_secuencial = (int*)malloc(sizeof(int) * filas);
    producto_matriz_vector_secuencial(matriz, vector, resultado_secuencial,filas,columnas);
  	printf("Solucion Matriz x Vector secuencial OpenMP y MPI: \n");
        for (int i = 0; i < filas; i++) {
            printf("%d ", resultado_secuencial[i]);
        }
        printf("\n");
    printf("Diferencias?:\n");
    int ans = 1;
    for (int i = 0; i < filas && ans; i++)
    {
      if(resultado[i]-resultado_secuencial[i] != 0)
      {
        ans = 0;
      }
    }
    if (ans)
    {
      printf("No hay Diferencias\n");
    }
    else
    {
      printf("Hay Diferencias\n");
    }
    printf("\n");
  	// Calculo de tiempos
    printf ( "Duration of the computation: %.6lf seconds\n", ecomm_time );
    printf ( "Duration of communication in P0: %.6lf seconds\n", ecomm_time );
    free(matriz);
    free(vector);
    free(resultado);
  }
  free(matriz_por_proceso);
  free(resultado_por_proceso);
  MPI_Finalize();
  return 0;
}
