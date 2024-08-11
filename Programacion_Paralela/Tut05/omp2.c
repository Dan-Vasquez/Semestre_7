/*******************************************************************************
*                                                                              *
*  omp2.c - A program that illustrates using                                   *
*             omp_get_num_threads
*             omp_get_thread_num
*                                                                              *
*   Departamento de Electronica y Ciencias de la Computacion                   *
*   Pontificia Universidad Javeriana - CALI                                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <omp.h>

int main ( int argc, char *argv[] )
{
  int my_tid,
      t;

  /* create a team of threads */
  #pragma omp parallel
  {
    t = omp_get_num_threads ();
    my_tid = omp_get_thread_num ();
    printf ( "Hello world\n" );
    printf ( "I am thread %d out of %d threads\n", my_tid, t );
  }

  return ( 0 );
}
