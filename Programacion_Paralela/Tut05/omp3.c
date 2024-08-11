/*******************************************************************************
*                                                                              *
*  omp3.c - A program that illustrates the use of                              *
*             omp_get_num_procs                                                *
*             the private clause                                               *
*                                                                              *
*   Departamento de Electronica y Ciencias de la Computacion                   *
*   Pontificia Universidad Javeriana - CALI                                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <omp.h>

int main ( int argc, char *argv[] )
{
  int t_id,
      t,
      p;

  #pragma omp parallel private(t_id, t, p)
  {
    p = omp_get_num_procs ();
    t = omp_get_num_threads ();
    t_id = omp_get_thread_num ();
    printf ( "Hello from thread %d out of %d in %d processors\n", t_id, t, p );
  }

  return ( 0 );
}
