#include <stdio.h>
#include <math.h>
#include <omp.h>

#define f(x) ( 4.0 / ( 1.0 + ( x ) * ( x ) ) )

int main ( int argc, char *argv[] )
{
  /* Reference */
  double PI25DT = 3.141592653589793238462643;

  int     n;      /* number of intervals */

  double  w,
          x,
          m,
          pi;

  for ( ; ; )
  {
    printf ( "Enter the number of intervals: (0 quits) ");
    scanf ( "%d", &n );
    if ( n == 0 )
      break;

    pi = 0.0;
    w = 1.0 / ( double ) n;        /* width of trapezoid */
    m = w / 2;              /* middle point of trapezoid */
    #pragma omp parallel for reduction(+:pi)
    for ( int i = 0; i < n; i++ )
    {
      printf("Hilo %d ejecutando iteración %d\n", omp_get_thread_num(), i);
      x = w * ( double ) i + m;
      pi += w * f ( x );            /* area of trapezoid */
    }

    printf ( "pi is approximately %.16f, Error is %.16f\n",
              pi, fabs ( pi - PI25DT ) );
  }

  return ( 0 );
}
