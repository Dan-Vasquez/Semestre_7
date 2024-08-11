/* Parcial #2 Prog. Paralela
 - Miguel Angel Nivia (8958691)
 - Daniel Andres Vasquez (8963154)
 - Willian Chapid Tobar (8965113)
 
 Codigo #2 Paralelo MPI
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Función para calcular el producto matriz-matriz local
void producto_matriz_matriz_local(int matrizA[], int matrizB[], int matrizC[], int filas, int columnas, int my_rank){
  for (int i = 0; i < filas; i++){
    for (int j = 0; j < columnas; j++){
    	matrizC[columnas * i + j] = 0;
    	for (int k = 0; k < columnas; k++){
      	matrizC[columnas * i + j] += matrizA[i * columnas + k] * matrizB[k * columnas + j];
      	// printf("Operacion %d x %d = %d proceso %d\n", matrizA[i * columnas + k], matrizB[k * columnas + j], matrizC[columnas * i + j], my_rank);
    	}
    }
  }
}

int main(int argc, char *argv[]){
  int my_rank, p, filas, columnas, *matrizA, *matrizB, *matrizC;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  if (my_rank == 0){
    // Obtención de datos
    scanf("%d", &filas);
    columnas = filas;
    // Asignación de memoria para las matrices
    matrizA = (int *)malloc(filas * columnas * sizeof(int));
    matrizB = (int *)malloc(filas * columnas * sizeof(int));
    matrizC = (int *)malloc(filas * columnas * sizeof(int));

    // Obtención de matrizA
    for (int i = 0; i < filas * columnas; i++){
      scanf("%d,", &matrizA[i]);
    }

    // Obtención de matrizB
    for (int i = 0; i < filas * columnas; i++){
      scanf("%d,", &matrizB[i]);
    }
  }
  
  // Broadcast de los tamaños de las matrices
  MPI_Bcast(&filas, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&columnas, 1, MPI_INT, 0, MPI_COMM_WORLD);
  
  // Envio de informacion de la matrizB
  if (my_rank != 0){
  	matrizB = (int *)malloc(filas * columnas * sizeof(int));
  }
  MPI_Bcast(matrizB, filas * columnas, MPI_INT, 0, MPI_COMM_WORLD);

  // Scatter de matrizA y matrizB
  int local_columnas = columnas / p;
  int local_elements = filas * local_columnas;
  int *local_matrizA = (int *)malloc(local_elements * sizeof(int));
  int *local_matrizC = (int *)malloc(local_elements * sizeof(int));
  
  // Se envia particiones
  MPI_Scatter(matrizA, local_elements, MPI_INT, local_matrizA, local_elements, MPI_INT, 0, MPI_COMM_WORLD);

  // Cálculo del producto matriz-matriz local
  producto_matriz_matriz_local(local_matrizA, matrizB, local_matrizC, local_columnas, columnas, my_rank);

  // recoleccion de los resultados parciales
  MPI_Gather(local_matrizC, local_elements, MPI_INT, matrizC, local_elements, MPI_INT, 0, MPI_COMM_WORLD);

  if (my_rank == 0){
    printf("Solucion Matriz x Matriz: \n");
    for (int i = 0; i < filas; i++) {
      for (int j = 0; j < columnas; j++) {
        printf("%d ", matrizC[columnas * i + j]);
      }
      printf("\n");
    }

    // Liberar memoria
    free(matrizA);
    free(matrizC);
  }

  // Liberar memoria
  free(local_matrizA);
  free(matrizB);
  free(local_matrizC);

  MPI_Finalize();
  return 0;
}
