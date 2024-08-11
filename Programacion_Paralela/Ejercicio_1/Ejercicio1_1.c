/*Ejercicio 1
 - Miguel ANgel Nivia
 - Daniel Andres Vasquez
 - Willian Chapid Tobar
*/

#include <stdio.h>
#include <mpi.h>

#define PROCESS0 0
#define MSGSIZE  1
#define PINGS		 5

enum role_ranks
{
  pPing,
  pPong
};

enum msg_tags
{
  ERR_TAG,
  PING,
  PONG
};

#define ERROR_CODE -1

int main ( int argc, char *argv[] )
{
  int  my_rank, p,
  		 paquete = 0;
  		 
  MPI_Init ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );
  MPI_Comm_size ( MPI_COMM_WORLD, &p );
  
  if ( p != 2 )
  {
    int err_code = ERROR_CODE;

    if ( my_rank == PROCESS0 )
    {
      printf ( "\n%s Solo 2 procesos. \n\n", argv[0]);
      for ( int rank = 1; rank < p; rank++ )
        MPI_Send ( &err_code, MSGSIZE, MPI_INT, rank, ERR_TAG, MPI_COMM_WORLD );
    }
    else
      MPI_Recv ( &err_code, MSGSIZE, MPI_INT, PROCESS0, ERR_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE );

    MPI_Finalize ();
    return ( 0 );
  }
  
  while (paquete < PINGS)
  {
		switch ( my_rank )
		{
		  case pPing:
		  {

		  		if (paquete != 0)
		  		{
		    		MPI_Recv ( &paquete, MSGSIZE, MPI_INT, pPong, PONG, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
		    		// printf ( "Recibido %d\n", paquete );
		   		}
		   		
		    	paquete++;
		    	MPI_Send ( &paquete, MSGSIZE, MPI_INT, pPong, PING, MPI_COMM_WORLD );
		    	printf ( "Ping %d\n", paquete );
		    break;
		  }
		  case pPong:
		  {
				  MPI_Recv ( &paquete, MSGSIZE, MPI_INT, pPing, PING, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
		    		printf ( "Pong %d\n", paquete );
				  
				  MPI_Send ( &paquete, MSGSIZE, MPI_INT, pPing, PONG, MPI_COMM_WORLD);
		    	// printf ( "Enviado %d\n", paquete );
				  break;
		  }
		}
	}
  
  MPI_Finalize ();
  return 0;
}
