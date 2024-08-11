/*******************************************************************************
*                                                                              *
*  cpit1.c - MPI + OpenMP                                                      *
*                                                                              *
*   Estimate the value of pi by means of the integral of 4 / ( 1 + x^2 ) using *
*   tangent-trapezoidal rule using n trapezoids. The method is simple: the     *
*   integral is approximated by a sum of n intervals                           *
*                                                                              *
*   Departamento de Electronica y Ciencias de la Computacion
*   Pontificia Universidad Javeriana - CALI
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>
#include "timer.h"

#define f(x) ( 4.0 / ( 1.0 + ( x ) * ( x ) ) )

#define ROOT_PROCESS 0

int main ( int argc, char *argv[] )
{
  int     p,
          my_rank;
  int     n,
          i;
  double  PI25DT = 3.141592653589793238462643;
  double  h,
          mypi,
          t1,
          x,
          pi;

  struct timespec comm_timer,
                  comp_timer;
  double          comm_time,
                  comp_time;

  MPI_Init ( &argc, &argv );
  cpu_timer_start ( &comm_timer );
  MPI_Comm_size ( MPI_COMM_WORLD, &p );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );
  comm_time = cpu_timer_stop ( comm_timer );

  if ( my_rank == 0 )
  {
    printf ( "\nThe time will be measured in multiples of 1.0e-9 seconds\n" );
    printf ( "\nThe initialisation phase of MPI took %.3f seconds\n", comm_time );
  }

  for ( ; ; )
  {
    if ( my_rank == ROOT_PROCESS )
    {
      printf ( "Enter the number of intervals: (0 quits) ");
      fflush ( stdout );
      scanf ( "%d", &n );
    }

    cpu_timer_start ( &comm_timer );
    MPI_Bcast ( &n, 1, MPI_INT, ROOT_PROCESS, MPI_COMM_WORLD );
    comm_time = cpu_timer_stop ( comm_timer );

    if ( n == 0 )
      break;

    cpu_timer_start ( &comp_timer );
    h = 1.0 / ( double ) n;
    mypi = 0.0;
    t1 = h / 2;

    #pragma omp parallel for private(x) reduction(+:mypi)
    for ( i = my_rank; i < n; i += p )
    {
      x = h * ( double ) i;
      mypi += h * f ( x + t1 );
    }
    comp_time = cpu_timer_stop ( comp_timer );

    cpu_timer_start ( &comm_timer );
    MPI_Reduce ( &mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, ROOT_PROCESS, MPI_COMM_WORLD );
    comp_time += cpu_timer_stop ( comp_timer );

    if ( my_rank == ROOT_PROCESS )
    {
      printf ( "pi is approximately %.16f, Error is %.16f\n", pi, fabs ( pi - PI25DT ) );
      printf ( "Duration of the computation: %.6lf seconds\n", comp_time );
      printf ( "Duration of communication in P0: %.6lf seconds\n", comm_time );
    }
  } /* for ( ; ; ) */

  MPI_Finalize ();
  return ( 0 );
}
