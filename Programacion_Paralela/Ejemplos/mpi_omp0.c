/*******************************************************************************
*
*  mpi_omp0.c -   A program that illustrates using MPI + OpenMP
*
*   Departamento de Electronica y Ciencias de la Computacion
*   Pontificia Universidad Javeriana - CALI
*
*******************************************************************************/

#include <stdio.h>
#include <mpi.h>
#include <omp.h>

int main ( int argc, char *argv[] )
{
  int   my_rank,
        p;
  int   t_id;
  int   t;

  /* Initialise MPI runtime */
  MPI_Init ( &argc, &argv );

  /* Determine process rank */
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );

  /* Determine total number of processes */
  MPI_Comm_size ( MPI_COMM_WORLD, &p );

  /* Get node name */
  char node_name [MPI_MAX_PROCESSOR_NAME];
  int  name_len;
  MPI_Get_processor_name ( node_name, &name_len );

  #pragma omp parallel private(t_id, t)
  {
    t = omp_get_num_threads ();
    t_id = omp_get_thread_num ();
    printf ( "Hello from thread %d out of %d running inside process %d out of %d on %s\n",
              t_id, t, my_rank, p, node_name );
  }

  /* Shutdown MPI runtime */
  MPI_Finalize ();

  return ( 0 );
}
