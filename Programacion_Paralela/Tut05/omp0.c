/*******************************************************************************
*                                                                              *
*  omp0.c - A program that illustrates the creation of a team of threads via   *
*             #pragma omp parallel                                             *
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
    printf ( "Hello world from a member of a team of threads\n" );
  }
  printf ( "Bye from initial thread\n" );

  return ( 0 );
}
