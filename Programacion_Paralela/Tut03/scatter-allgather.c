/*******************************************************************************
*
*  scatter-gather.c - A program that illustrates using
*                       MPI_Scatter
*                       MPI_Allgather
*                     and passing arguments via the command line
*
*   Departamento de Electronica y Ciencias de la Computacion
*   Pontificia Universidad Javeriana - CALI
*
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define   ROOT_PROC   0

int main ( int argc, char *argv[] )
{
  int         my_rank,
              p;

  if ( argc != 2 )
  {
    printf ( "Usage: %s <elements_per_proc>\n", argv[0] );
    exit ( -1 );
  }

  /* Get the number of elements per process from the command line */
  int num_elements_per_proc = atoi ( argv [1] );

  MPI_Init ( &argc, &argv );

  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );
  MPI_Comm_size ( MPI_COMM_WORLD, &p );

  /* Total number of elements is equal to the number of elements per process
      times the number of processes */
  int num_elements = num_elements_per_proc * p;

  /* On the root process allocate memory for a buffer that will hold the
      entire array. Fill in the array */
  int *vector = NULL;
  if ( my_rank == ROOT_PROC )
  {
    vector = ( int * ) malloc ( sizeof ( int ) * num_elements );
    for ( int i = 0; i < num_elements; i++ )
      vector [i] = i + 1;
  }

  /* For each process, allocate memory for a local buffer that will hold a
      subset of the entire array; its size is equal to the number of
      elements per process */
  int *subvector = NULL;
  subvector = ( int * ) malloc ( sizeof ( int ) * num_elements_per_proc );

  /* The root process scatters the entire array amongst all processes.
      Each process receives its subset into the local buffer */
  MPI_Scatter ( vector, num_elements_per_proc, MPI_INT,
                subvector, num_elements_per_proc, MPI_INT,
                ROOT_PROC, MPI_COMM_WORLD );

  /* Compute the average of all elements in the subset */
  int my_sum = 0;
  for ( int i = 0; i < num_elements_per_proc; i++ )
    my_sum += subvector [i];
  double my_avg = (double) my_sum / num_elements_per_proc;

  /* Allocate memory for a buffer that will hold the local averages */
  double *avgs = ( double * ) malloc ( sizeof ( double ) * p );
  /* Gather all partial averages down to all the processes */
  MPI_Allgather ( &my_avg, 1, MPI_DOUBLE,
                  avgs, 1, MPI_DOUBLE,
                  MPI_COMM_WORLD );

  /* Now that we have all of the partial averages, compute the global average of all numbers.
      Since we are assuming each process computed an average across an equal amount of elements,
      this computation will produce the correct answer. */
  double sum_of_avgs = 0;
  for ( int rank = 0; rank < p; rank++ )
    sum_of_avgs += avgs [rank];
  double global_avg;
  global_avg = sum_of_avgs / p;
  printf ( "In proc%d, sum of local averages is %lf; global average is %lf\n",
             my_rank, sum_of_avgs, global_avg );

  /* Compute the global average across the entire array for comparison */
  if ( my_rank == ROOT_PROC )
  {
    double global_sum = (double) ( num_elements + 1 ) * num_elements  / 2;
    printf ( "Golden reference is %lf\n", global_sum / num_elements );
  }

  /* Free allocated memory */
  free ( avgs );
  free ( subvector );
  if ( my_rank == ROOT_PROC )
    free ( vector );

  MPI_Finalize ();
}
