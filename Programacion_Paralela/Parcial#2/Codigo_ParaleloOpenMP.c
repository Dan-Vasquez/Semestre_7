/* Parcial #2 Prog. Paralela
 - Miguel Angel Nivia (8958691)
 - Daniel Andres Vasquez (8963154)
 - Willian Chapid Tobar (8965113)
 
 Codigo #2 Paralelo OpenMP
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Función para calcular el producto matriz-vector (utilizamos omp)
void producto_matriz_vector(int matriz[], int vector[], int resultado[], int filas, int columnas) {
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
int main(){
	// Obtencion informacion
	int filas, columnas, 
			*resultado = NULL, *matriz = NULL, *vector = NULL;
	
	scanf("%d, %d", &filas, &columnas);
	
	// Asignación de memoria para la matriz
  matriz = (int *)malloc(filas * columnas * sizeof(int ));
    
	// Obtencion matriz
	for (int i = 0; i < (filas * columnas); i++) 
	{
		scanf("%d,", &matriz[i]);
	}
	
	// Asignación de memoria para el vector
	vector = (int *)malloc(columnas * sizeof(int ));
	
	// Asignación de memoria para la respuesta
	resultado = (int *)malloc(filas * sizeof(int ));
	
	// Obtencion Vector
	for (int i = 0; i < columnas; i++) 
	{
		scanf("%d,", &vector[i]);
	}	
	
	// Calcular matriz x vector
	producto_matriz_vector(matriz, vector, resultado, filas, columnas);
	printf("Solucion Matriz x Vector OpenMP: \n");
	for (int i = 0; i < filas; i++) 
	{
		printf("%d ", resultado[i]);
	}
	int *resultado_secuencial = (int*)malloc(sizeof(int) * filas);
  producto_matriz_vector_secuencial(matriz, vector, resultado_secuencial,filas,columnas);
	printf("Solucion Matriz x Vector secuencial MPI: \n");
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
	printf("\n");
	free(vector);
	free(matriz);
	free(resultado);
	return 0;
}
