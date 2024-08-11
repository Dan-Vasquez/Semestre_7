/*******************************************************************************
*
*   MPITimeIt1.c - A program exemplifying the use of MPI_Wtime for measuring
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
      workload;

  /* Initialize MPI and get process rank */
  MPI_Init ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );

  double  tstart,
          tstop;

  /* choose a random number to simulate workload */
  srand ( time ( NULL ) + my_rank );
  workload = ( rand () / (float) RAND_MAX ) * 5 * ( my_rank + 1 );

  /* Start timer, call sleep, then stop timer */
  tstart = MPI_Wtime ();
  sleep ( workload );
  tstop = MPI_Wtime ();

  printf( "Elapsed time for proc%d is %f secs\n", my_rank, tstop - tstart );

  /* Shutdown MPI */
  MPI_Finalize();
}
