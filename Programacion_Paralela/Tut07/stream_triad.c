/*******************************************************************************
*
*  stream_triad.c - An implementation of the STREAM benchmark to measure
*                   MPI_Get_processor_name
*
*   Adapted from:   Robert Robey and Yuliana Zamora
*                   Parallel and High Performance Computing
*                   Manning, 2021
*
*   Departamento de Electronica y Ciencias de la Computacion
*   Pontificia Universidad Javeriana - CALI
*
*******************************************************************************/

#include <stdio.h>
#include "timer.h"

/* times to loop */
#define NTIMES              16

/* large enough to force into main memory */
#define MEGAS               16
#define STREAM_ARRAY_SIZE   (MEGAS) * 1024 * 1024

/* ANSI escape codes */
#define BGRN "\e[1;32m"
#define reset "\e[0m"

static double a[STREAM_ARRAY_SIZE],
              b[STREAM_ARRAY_SIZE],
              c[STREAM_ARRAY_SIZE];

int main ( int argc, char *argv[] )
{
   struct timespec tstart;

   /* initializing data and arrays */
   double scalar = 3.0,
          time_sum = 0.0;
   for (int i = 0; i < STREAM_ARRAY_SIZE; i++ )
   {
      a[i] = 1.0;
      b[i] = 2.0;
   }

   /* execute the inner loop NTIMES timing each iteration */
   for ( int iter = 0; iter < NTIMES; iter++ )
   {
      cpu_timer_start ( &tstart );
      /* stream triad loop */
      for ( int i = 0; i < STREAM_ARRAY_SIZE; i++ )
      {
         c[i] = a[i] + scalar * b[i];
      }
      /* accumulate execution times */
      time_sum += cpu_timer_stop ( tstart );
      /* just to keep the compiler from optimizing out the loop */
      c[1] = c[2];
   }
   /* average execution time */
   printf ( BGRN "Average runtime is %lf msecs\n" reset, time_sum / NTIMES );

   return ( 0 );
}
