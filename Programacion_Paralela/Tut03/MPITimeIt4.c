/*******************************************************************************
*
*   MPITimeIt4.c - A program exemplifying the use of MPI_Wtime for measuring
*                   elapsed time
*                     MPI_Gather
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
          e_time;

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

  double e_times [p];
  for(int i =0; i<p;i++){
    printf("%f", e_times[i]);
  }
  printf("finalizo %d\n", my_rank );
  //comprobando que todos crean el vector e_times
  /* gather all the execution times to process 0 */
  MPI_Gather ( &e_time, 1, MPI_DOUBLE, e_times, 1, MPI_DOUBLE, PROCESS0, MPI_COMM_WORLD );

  /* print execution times */
  if ( my_rank == PROCESS0 )
  {
    for ( int rank = 0; rank < p; rank++ )
      printf ( "Execution time for proc%d is %lf\n", rank, e_times [rank] );
  }

  /* Shutdown MPI */
  MPI_Finalize();
}
