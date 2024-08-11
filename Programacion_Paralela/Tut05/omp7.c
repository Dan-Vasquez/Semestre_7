/*******************************************************************************
*                                                                              *
*  omp7.c - A program that illustrates declaring private variables
*                                                                              *
*   Departamento de Electronica y Ciencias de la Computacion                   *
*   Pontificia Universidad Javeriana - CALI                                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <omp.h>

int main ( int argc, char *argv[] )
{
  int t;

  #pragma omp parallel
  {
    int my_tid = omp_get_thread_num ();

    my_tid = omp_get_thread_num ();
    printf ( "Hello from thread %d \n", my_tid );

    if ( my_tid == 0 )
    {
      t = omp_get_num_threads ();
      printf ( "%d threads in total\n", t );
    }
  }

  return ( 0 );
}
