/*******************************************************************************
*
*  allreduce.c - A program that illustrates using
*                 MPI_Allreduce
*
*   Departamento de Electronica y Ciencias de la Computacion
*   Pontificia Universidad Javeriana - CALI
*
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
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

  /* Allocate memory for a buffer that will hold num_elements_per_proc */
  double *vector = NULL;
  vector = (double *) malloc ( sizeof ( double ) * num_elements_per_proc );
  /* Fill in the array randomly */
  srand ( time ( NULL ) * my_rank );
  for ( int i = 0; i < num_elements_per_proc; i++ )
    vector [i] = rand () / (double) RAND_MAX;

  /* Compute the sum of all local elements */
  double my_sum = 0;
  for ( int i = 0; i < num_elements_per_proc; i++ )
    my_sum += vector [i];

  /* Reduce all of the local sums into the global sum in order to calculate the mean */
  double global_sum;
  MPI_Allreduce ( &my_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
  double mean = global_sum / (double) num_elements;

  /* Compute the local sum of the squared differences from the mean */
  double my_sq_diff = 0;
  for ( int i = 0; i < num_elements_per_proc; i++ )
    my_sq_diff += ( vector[i] - mean ) * ( vector[i] - mean );

  /* Reduce the global sum of the squared differences to the root process */
  double global_sq_diff;
  MPI_Reduce ( &my_sq_diff, &global_sq_diff, 1, MPI_DOUBLE, MPI_SUM,
               ROOT_PROC, MPI_COMM_WORLD );

  /* Now that we have the global sum of the squared differences on the root,
      compute the standard deviation (the square root of the mean of the squared differences) and print it */
  if ( my_rank == ROOT_PROC )
  {
    double stddev = sqrt ( global_sq_diff / (double) num_elements );
    printf ( "Mean = %lf, Standard deviation = %lf\n", mean, stddev );
  }

  /* Free allocated memory */
  free ( vector );

  MPI_Finalize ();
}
