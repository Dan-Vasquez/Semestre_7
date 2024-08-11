/*******************************************************************************
*
*   MPITimeIt3.c - A program exemplifying the use of MPI_Wtime for measuring
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

#define ET_TAG      0

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

  /* send execution time to process 0 */
  MPI_Send ( &e_time, 1, MPI_DOUBLE, PROCESS0, ET_TAG, MPI_COMM_WORLD );

  /* print execution times */
  if ( my_rank == PROCESS0 )
  {
    printf ( "Execution time for proc%d is %lf\n", my_rank, e_time );
    for ( int rank = 1; rank < p; rank++ )
    {
      /* receive execution times */
      MPI_Recv ( &e_time, 1, MPI_DOUBLE, rank, ET_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
      printf ( "Execution time for proc%d is %lf\n", rank, e_time );
    }
  }

  /* Shutdown MPI */
  MPI_Finalize();
}
