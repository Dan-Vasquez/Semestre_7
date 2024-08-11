/*******************************************************************************
*
*  cpi_p2p.c - Basic send/receive version
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

#define ERROR_CODE    -1

#define ROOT_PROCESS  0

#define N_TAG         0
#define PI_TAG        1

int main ( int argc, char *argv[] )
{
  int     p,
          my_rank;
  int     n,
          i;
  double  PI25DT = 3.141592653589793238462643;
  double  w,
          my_pi,
          m,
          x,
          rank_pi,
          pi;

  MPI_Init ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );
  MPI_Comm_size ( MPI_COMM_WORLD, &p );

  if ( p < 2 )
    /* Terminate (in a non-gracefully manner) the runtime environment */
    MPI_Abort ( MPI_COMM_WORLD, ERROR_CODE );

  for ( ; ; )
  {
    if ( my_rank == ROOT_PROCESS )
    {
      printf ( "Enter the number of intervals: (0 quits) ");
      fflush ( stdout );
      scanf ( "%d", &n );
      /* send the number of intervals to every other process */
      for ( int rank = 1; rank < p; rank++ )
        MPI_Send ( &n, 1, MPI_INT, rank, N_TAG, MPI_COMM_WORLD );
    }
    else
    {
      /* get the number of intervals from root process */
      MPI_Recv ( &n, 1, MPI_INT, ROOT_PROCESS, N_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
    }

    /* no intervals; so, exit */
    if ( n == 0 )
      break;

    /* calculate this process contribution */
    my_pi = 0.0;
    w = 1.0 / ( double ) n;
    m = w / 2;

    for ( i = my_rank; i < n; i += p )
    {
      x = w * ( double ) i + m;
      my_pi += w * f ( x );
    }

    if ( my_rank == ROOT_PROCESS )
    {
      /* consolidate the contributions */
      pi = 0;
      pi += my_pi;
      for ( int rank = 1; rank < p; rank++ )
      {
        MPI_Recv ( &rank_pi, 1, MPI_DOUBLE, rank, PI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
        pi += rank_pi;
      }

      printf ( "pi is approximately %.16f, Error is %.16f\n", pi, fabs ( pi - PI25DT ) );

    }
    else
    {
      /* send contribution */
      MPI_Send ( &my_pi, 1, MPI_DOUBLE, ROOT_PROCESS, PI_TAG, MPI_COMM_WORLD );
    }
  } /* for ( ; ; ) */

  MPI_Finalize ();
  return ( 0 );
}
