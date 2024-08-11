/*******************************************************************************
*                                                                              *
*  for0.c - A program to illustrate how OpenMP distributes workload between
*           threads
*                                                                              *
*   Departamento de Electronica y Ciencias de la Computacion                   *
*   Pontificia Universidad Javeriana - CALI                                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <omp.h>

int main ( int argc, char *argv[] )
{
  int max,
      i;

  if ( argc != 2 )
  {
    printf ( "Usage: %s max_iters\n", argv[0] );
    return ( - 1 );
  }

  sscanf ( argv [1], "%d", &max );

  #pragma omp parallel for
  for ( i = 0; i < max; i++ )
    printf ( "%d: %d\n", omp_get_thread_num (), i );

  return ( 0 );
}
