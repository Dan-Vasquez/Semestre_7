/*******************************************************************************
*                                                                              *
*  races.c - A program to demonstrate data races
*                                                                              *
*   Departamento de Electronica y Ciencias de la Computacion                   *
*   Pontificia Universidad Javeriana - CALI                                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>

int main ( int argc , char *argv [])
{
  int max;

  if ( argc != 2 )
  {
    printf ( "Usage: %s max_iters\n", argv[0] );
    return ( - 1 );
  }

  sscanf (argv [1], "%d", &max);

  int i,
      sum = 0;

  #pragma omp parallel for
  for ( i = 1; i <= max; i++ )
    sum = sum + i;

  printf ( "%d (golden = %d)\n", sum, max * (max + 1) / 2 );

  return ( 0 );
}
