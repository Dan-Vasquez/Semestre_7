/*******************************************************************************
*                                                                              *
*  for3.c - A program to illustrate using nested loops and
*           the parallel sections directive
*                                                                              *
*   Departamento de Electronica y Ciencias de la Computacion                   *
*   Pontificia Universidad Javeriana - CALI                                    *
*                                                                              *
*******************************************************************************/


#include <stdio.h>
#include <omp.h>

#define SIZE  1024

void vectInit ( double *a, double *b, int n );
void vectAdd ( double *a, double *b, double *y, int n );

int main ( int argc, char *argv[] )
{
  double  a[SIZE],
          b[SIZE],
          y[SIZE];

  vectInit ( a, b, SIZE );
  #pragma omp barrier
  vectAdd ( a, b, y, SIZE );

  return ( 0 );
}

void vectInit ( double *a, double *b, int n )
{
  #pragma omp parallel
  {
    #pragma omp sections
    {
      #pragma omp section
      {
        int i;

        #pragma omp parallel for
        for ( i = 0; i < n; i++ )
          a[i] = i;
      }
      #pragma omp section
      {
        int i;

        #pragma omp parallel for
        for ( i = 0; i < n; i++ )
          b[i] = n - i;
      }
    }
  }
}

void vectAdd ( double *a, double *b, double *y, int n )
{
  int i;

  #pragma omp parallel for
  for ( i = 0; i < n; i++ )
    y[i] = a[i] + b[i];
}
