#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <mpi.h>

#define PROCCESS0 0
#define f(x) ( 4.0 / ( 1.0 + ( x ) * ( x ) ) )

int main ( int argc, char *argv[] )
{
  /* Reference */
  double PI25DT = 3.141592653589793238462643;

  int     n, my_rank, p;      /* number of intervals */

  double  w,
          x,
          m,
          pi;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  for ( ; ; )
  {
    if (my_rank == PROCCESS0){
      printf ( "Enter the number of intervals: (0 quits) ");
      scanf ( "%d", &n );
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if ( n == 0 )
      break;

    pi = 0.0;
    w = 1.0 / ( double ) n;        /* width of trapezoid */
    m = w / 2;              /* middle point of trapezoid */
    #pragma omp parallel for reduction(+:pi) private(x)
    for ( int i = 0; i < n; i++ )
    {
      printf("Hilo %d ejecutando iteración %d\n", omp_get_thread_num(), i);
      x = w * ( double ) i + m;
      pi += w * f ( x );            /* area of trapezoid */
    }
    double pi_local;
    MPI_Reduce(&pi, &pi_local, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
    if(my_rank == PROCCESS0)
    {
      printf ( "pi is approximately %.16f, Error is %.16f\n",
              pi, fabs ( pi - PI25DT ) );
    }
  }

  return ( 0 );
}
