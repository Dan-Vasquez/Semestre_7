/*******************************************************************************
*
*  rowVcol_major.c -  A program to demonstrate row vs col-major access times
*
*   Notes:            C uses row-major order to store arrays in memory
*
*******************************************************************************/

#include <stdio.h>
#include <time.h>

#include "timer.h"

#define   N   1024

int Matrix[N][N];

int main ( void )
{
  int             i,
                  j;
  struct timespec t_row,
                  t_col;
  double  dr,
          dc;

  dr = 0.0;
  dc = 0.0;

  /* Timing row-major order */

  cpu_timer_start ( &t_row );

  for ( i = 0; i < N; i++ )
    for ( j = 0; j < N; j++ )
      Matrix[i][j] = Matrix[i][j] + ( Matrix[i][j] * Matrix[i][j] );

  dr += cpu_timer_stop ( t_row );
  printf ( "The run-time of row major order is %lf\n", dr );

  /* Timing col-major order */

  cpu_timer_start ( &t_col );

  for ( j = 0; j < N; j++ )
    for ( i = 0; i < N; i++ )
      Matrix[i][j] = Matrix[i][j] + (Matrix[i][j] * Matrix[i][j]);

  dc += cpu_timer_stop ( t_col );
  printf ( "The run-time of column major order is %lf\n", dc );

  /* Print col-major vs col-major order ratio */

  printf ( "col-major/row-major ratio is %lf\n", dc/dr );
}
