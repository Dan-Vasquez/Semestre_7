/*******************************************************************************
*
*   MPITimeIt2.c - A program exemplifying the use of MPI_Wtime for measuring
*                   elapsed time
*
*   Departamento de Electronica y Ciencias de la Computacion
*   Pontificia Universidad Javeriana - CALI
*
*******************************************************************************/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

#define PROCESS0    0

int main ( int argc, char *argv[] )
{
  int my_rank,
      p,
      workload;

  /* Initialize MPI and get process rank */
  MPI_Init ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );
  MPI_Comm_size ( MPI_COMM_WORLD, &p );

  double  tstart,
          e_time,
          min_time,
          max_time,
          sum_time;

  /* choose a random number to simulate execution time */
  srand ( time ( NULL ) + my_rank );
  workload = ( rand () / (float) RAND_MAX ) * 5 + 1;
  workload *= my_rank;

  /* Synchronise all the processes so they start at about the same time */
  MPI_Barrier ( MPI_COMM_WORLD );

  /* Start timer, call sleep, then stop timer */
  tstart = MPI_Wtime ();
  sleep ( workload );
  e_time = MPI_Wtime () - tstart;

  printf( "Elapsed time for proc%d is %f secs\n", my_rank, e_time );

  /* Use reduction calls to compute the max, min, and total time */
  MPI_Reduce ( &e_time, &min_time, 1, MPI_DOUBLE, MPI_MIN, PROCESS0, MPI_COMM_WORLD );
  MPI_Reduce ( &e_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, PROCESS0, MPI_COMM_WORLD );
  MPI_Reduce ( &e_time, &sum_time, 1, MPI_DOUBLE, MPI_SUM, PROCESS0, MPI_COMM_WORLD );

  if ( my_rank == PROCESS0 )
     printf ( "Time job is Min: %lf  Max: %lf  Avg: %lf seconds\n",
                min_time, max_time, sum_time / p );

  /* Shutdown MPI */
  MPI_Finalize();
}
