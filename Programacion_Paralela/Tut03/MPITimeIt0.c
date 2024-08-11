/*******************************************************************************
*
*   MPITimeIt0.c - A program exemplifying the use of MPI_Wtime for measuring
*                   elapsed time
*
*   Departamento de Electronica y Ciencias de la Computacion
*   Pontificia Universidad Javeriana - CALI
*
*******************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <mpi.h>

#define PROCESS0    0

int main ( int argc, char *argv[] )
{
  int my_rank;

  /* Initialize MPI and get process rank */
  MPI_Init ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );

  double  tstart,
          tstop,
          tick_resolution;

  /* Start timer, call sleep, then stop timer */
  tstart = MPI_Wtime ();
  sleep ( 10 );
  tstop = MPI_Wtime ();

  /* Process 0 prints timing output */
  if ( my_rank == PROCESS0 )
  {
    tick_resolution = MPI_Wtick ();
    printf( "Elapsed time is %f secs (resolution is %f seconds)\n", tstop - tstart, tick_resolution );
  }

  /* Shutdown MPI */
  MPI_Finalize();
}
