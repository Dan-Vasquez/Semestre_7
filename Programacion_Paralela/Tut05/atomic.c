/*******************************************************************************
*                                                                              *
*  atomic.c - A program to demonstrate using
*             the atomic directive
*                                                                              *
*   Departamento de Electronica y Ciencias de la Computacion                   *
*   Pontificia Universidad Javeriana - CALI                                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>

int main ( int argc , char *argv [])
{
  int max;

  sscanf (argv [1], "%d", &max);

  int i,
      sum = 0;

  #pragma omp parallel for
  for ( i = 1; i <= max; i++ )
    #pragma omp atomic
    sum = sum + i;

  printf ("%d\n", sum);

  return ( 0 );
}
