/*******************************************************************************
*                                                                              *
*  for3.c                                                                      *
*                                                                              *
*   Departamento de Electronica y Ciencias de la Computacion                   *
*   Pontificia Universidad Javeriana - CALI                                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <omp.h>

int main ( int argc, char *argv[] )
{
  int max;

  if ( argc != 2 )
  {
    printf ( "Usage: %s max_iters\n", argv[0] );
    return ( - 1 );
  }

  sscanf ( argv [1], "%d", &max );

  #pragma omp parallel for
  for ( int i = 1; i <= max; i++ )
    for ( int j = 1; j <= max; j++ )
      printf ( "%d: (%d, %d)\n", omp_get_thread_num (), i, j );

  return ( 0 );
}
