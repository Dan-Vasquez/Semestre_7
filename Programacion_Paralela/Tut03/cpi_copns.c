/*******************************************************************************
*
*  cpi_copns.c - Collective Operations version
*
*   Estimate the value of pi by means of the integral of 4 / ( 1 + x^2 ) using
*   tangent-trapezoidal rule using n trapezoids. The method is simple: the
*   integral is approximated by a sum of n intervals
*
*   Departamento de Electronica y Ciencias de la Computacion
*   Pontificia Universidad Javeriana - CALI
*
*******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define f(x) ( 4.0 / ( 1.0 + ( x ) * ( x ) ) )

#define ROOT_PROCESS  0

int main ( int argc, char *argv[] )
{
  int     p,
          my_rank;
  int     n,
          i;
  double  PI25DT = 3.141592653589793238462643;
  double  h,
          my_pi,
          t1,
          x,
          pi;

  MPI_Init ( &argc, &argv );
  MPI_Comm_size ( MPI_COMM_WORLD, &p );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );

  for ( ; ; )
  {
    if ( my_rank == ROOT_PROCESS )
    {
      printf ( "Enter the number of intervals: (0 quits) ");
      fflush ( stdout );
      scanf ( "%d", &n );
    }

    /* root process broadcasts number of intervals to every other process */
    MPI_Bcast ( &n, 1, MPI_INT, ROOT_PROCESS, MPI_COMM_WORLD );
    /* no intervals; so, exit */
    if ( n == 0 )
      break;

    /* calculate this process contribution */
    my_pi = 0.0;
    h = 1.0 / ( double ) n;
    t1 = h / 2;

    for ( i = my_rank; i < n; i += p )
    {
      x = h * ( double ) i;
      my_pi += h * f ( x + t1 );
    }

    /* consolidate the contributions */
    MPI_Reduce ( &my_pi, &pi, 1, MPI_DOUBLE, MPI_SUM, ROOT_PROCESS, MPI_COMM_WORLD );

    if ( my_rank == ROOT_PROCESS )
      printf ( "pi is approximately %.16f, Error is %.16f\n", pi, fabs ( pi - PI25DT ) );
  } /* for ( ; ; ) */

  MPI_Finalize ();
  return ( 0 );
}
