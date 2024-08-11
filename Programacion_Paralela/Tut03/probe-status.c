/*******************************************************************************
*
*  probe-status.c - A program that illustrates using
*                     MPI_Probe
*                     the MPI_Status struct
*                     MPI_Get_count
*
*   Departamento de Electronica y Ciencias de la Computacion
*   Pontificia Universidad Javeriana - CALI
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define PROCESS0  0

enum role_ranks
{
  SENDER,
  RECEIVER
};

enum msg_tags
{
  ERR_TAG,
  VECT_TAG
};

#define ERROR_CODE        -1
#define MAX_VECTOR_SIZE   1048576

int main ( int argc, char *argv[] )
{
  int         my_rank,
              p;

  MPI_Init ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );
  MPI_Comm_size ( MPI_COMM_WORLD, &p );

  if ( p != 2 )
  {
    int err_code = ERROR_CODE;

    if ( my_rank == PROCESS0 )
    {
      printf ( "\n%s is meant to be executed by 2 processes.\n\n", argv[0] );
      for ( int rank = 1; rank < p; rank++ )
        MPI_Send ( &err_code, 1, MPI_INT, rank, ERR_TAG, MPI_COMM_WORLD );
    }
    else
      MPI_Recv ( &err_code, 1, MPI_INT, PROCESS0, ERR_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE );

    /* Terminate (gracefully) the runtime environment */
    MPI_Finalize ();
    return ( 0 );
  }

  /* Process 0 sends and Process 1 receives */
  int   *vector,
        vector_cardinality;

  switch ( my_rank )
  {
    case SENDER:
    {
      /* choose a random number to simulate workload */
      srand ( time ( NULL ) );
      vector_cardinality = (float) ( rand () % MAX_VECTOR_SIZE + 1 );

      /* Allocate a buffer to hold the outgoing elements */
      vector = ( int * ) malloc ( sizeof ( int ) * vector_cardinality );

      /* Send vector */
      MPI_Send ( &vector [0], vector_cardinality, MPI_INT, RECEIVER, VECT_TAG, MPI_COMM_WORLD);
      printf ( "p0 sent %d elements to p1\n", vector_cardinality );
      break;
    }
    case RECEIVER:
    {
      MPI_Status status;

      /* Probe for an incoming message from process 0 */
      MPI_Probe ( SENDER, VECT_TAG, MPI_COMM_WORLD, &status );

      /* When MPI_Probe returns, the status object has the size and other attributes
           of the incoming message. Get the message size */
      MPI_Get_count ( &status, MPI_INT, &vector_cardinality );

      /* Print the amount of elements, and additional information in the status object */
      printf ( "\tp1 will allocate memory for %d MPI_INT elements. Message source = %d, tag = %d\n",
                vector_cardinality, status.MPI_SOURCE, status.MPI_TAG );

      /* Allocate a buffer to hold the incoming elements */
      vector = ( int * ) malloc ( sizeof ( int ) * vector_cardinality );

      /* Now receive the message using the allocated buffer */
      MPI_Recv ( vector, vector_cardinality, MPI_INT, SENDER, VECT_TAG, MPI_COMM_WORLD, &status );

      /* Print amount of elements and additional information in the status object */
      printf ( "\tp1 received %d MPI_INT elements. Message source = %d, tag = %d\n",
              vector_cardinality, status.MPI_SOURCE, status.MPI_TAG );
      break;
    }
  }

  free ( vector );

  MPI_Finalize ();
  return ( 0 );
}
