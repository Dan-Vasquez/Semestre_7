/* Parcial #2 Prog. Paralela
 - Miguel Angel Nivia (8958691)
 - Daniel Andres Vasquez (8963154)
 - Willian Chapid Tobar (8965113)
 
 Codigo #1 Secuencial
*/

#include <stdio.h>
#include <stdlib.h>

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
	printf("Solucion Matriz x Vector: \n");
	for (int i = 0; i < filas; i++) 
	{
		printf("%d ", resultado[i]);
	}
	printf("\n");
	free(vector);
	free(matriz);
	free(resultado);
	return 0;
}
