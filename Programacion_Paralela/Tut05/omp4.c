/*******************************************************************************
*                                                                              *
*  omp4.c - A program that illustrates declaring private variables
*                                                                              *
*   Departamento de Electronica y Ciencias de la Computacion                   *
*   Pontificia Universidad Javeriana - CALI                                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <omp.h>

int main ( int argc, char *argv[] )
{
  #pragma omp parallel
  {
    int t = omp_get_num_threads ();
    int my_tid = omp_get_thread_num ();

    printf ( "Hello from thread %d out of %d threads in total\n", my_tid, t );
  }

  return ( 0 );
}
