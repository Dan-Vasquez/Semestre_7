/*******************************************************************************
*                                                                              *
*  omp1.c - A program that illustrates the use of                              *
*             omp_get_thread_num                                               *
*             omp_get_num_threads                                              *
*                                                                              *
*   Departamento de Electronica y Ciencias de la Computacion                   *
*   Pontificia Universidad Javeriana - CALI                                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <omp.h>

int main ( int argc, char *argv[] )
{
  printf ( "Hello world from initial thread\n" );
  /* create a team of threads */
  #pragma omp parallel
  {
    printf ( "I am thread %d out of %d threads\n",
              omp_get_thread_num (), omp_get_num_threads () );
  }
  printf ( "Bye from initial thread\n" );

  return ( 0 );
}
