/* Parcial #1 Prog. Paralela
 - Miguel Angel Nivia (8958691)
 - Daniel Andres Vasquez (8963154)
 - Willian Chapid Tobar (8965113)
 
 Codigo #1 Secuencial
*/

#include <stdio.h>
#include <stdlib.h>

int dot_product(int size, int *vect1, int *vect2){
  int sum = 0;
  for (int i = 0; i < size; i++) 
  {
    sum += vect1[i] * vect2[i];
  }
  return sum;
}

int main(){
  // input size
  int size;
  scanf("%d", &size);
  int *vect1 = (int *)malloc(sizeof(int)* size), *vect2 = (int *)malloc(sizeof(int)* size); 
  // input Vect1
  for (int i = 0; i < size; i++) 
  {
    scanf("%d,", &vect1[i]);
  }
  // input Vect2
  for (int i = 0; i < size; i++) 
  {
    scanf("%d,", &vect2[i]);
  }	 
	
  // dot product calculation
  int sum = 0;
  sum = dot_product(size, vect1, vect2);
	
  printf("Dot product of vectors: %d\n", sum);
  return 0;
}
