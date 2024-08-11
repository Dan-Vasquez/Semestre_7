/* Parcial #3 Prog. Paralela
 - Miguel Angel Nivia (8958691)
 - Daniel Andres Vasquez (8963154)
 - Willian Chapid Tobar (8965113)
 
 Codigo #1 Secuencial
*/

#include <stdio.h>
#include <stdlib.h>

// Función para calcular el producto matriz-matriz
void producto_matriz_matriz(int matrizA[], int matrizB[], int matrizC[], int filas, int columnas){
  for (int i = 0; i < filas; i++) 
  {
    for (int j = 0; j < columnas; j++) 
    {
      matrizC[i * columnas + j] = 0; 
      for (int k = 0; k < columnas; k++)
      {
        matrizC[i * columnas + j] += matrizA[i * columnas + k] * matrizB[k * columnas + j];
      }
    }
  }
}

int main(){
	// Obtencion tamaño
	int filas, columnas, *matrizC = NULL, *matrizA = NULL, *matrizB = NULL;
	
	scanf("%d", &filas);
	columnas = filas;
	// Asignación de memoria para las matrices
  matrizA = (int *)malloc(filas * columnas * sizeof(int ));
  matrizB = (int *)malloc(filas * columnas * sizeof(int ));
  matrizC = (int *)malloc(filas * columnas * sizeof(int ));
    
	// Obtencion matrizA
	for (int i = 0; i < (filas * columnas); i++) 
	{
		scanf("%d,", &matrizA[i]);
	}
	
	// Obtencion matrizB
	for (int i = 0; i < (filas * columnas); i++) 
	{
		scanf("%d,", &matrizB[i]);
	}
	
	// Calcular matriz x vector
	producto_matriz_matriz(matrizA, matrizB, matrizC, filas, columnas);
	printf("Solucion Matriz x Matriz: \n");
	for (int i = 0; i < filas; i++) 
	{
		for (int j = 0; j < columnas; j++){
			printf("%8d ", matrizC[i *columnas + j]);
		}
		printf("\n");
	}
	printf("\n");
	free(matrizA);
	free(matrizB);
	free(matrizC);
	return 0;
}
