/*Ejercicio 2
 - Miguel ANgel Nivia
 - Daniel Andres Vasquez
 - Willian Chapid Tobar
*/

#include <stdio.h>
#include <mpi.h>

#define PROCESS0 0
#define MSGSIZE  1

enum msg_tags
{
  TAG
};


int main ( int argc, char *argv[] )
{
  int  my_rank, p, predecesor, sucesor,
  		 sumatoria = 0;
  		 
  MPI_Init ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );
  MPI_Comm_size ( MPI_COMM_WORLD, &p );
  
  if (my_rank == 0)
  {
    predecesor = (p - 1);
    sucesor = my_rank + 1;
  }
  else if (my_rank == (p - 1))
  {
  	predecesor = my_rank - 1;
    sucesor = 0;
  }
  else
  {
  	predecesor = my_rank - 1;
    sucesor = my_rank + 1;
  }
  
  if ( my_rank == 0)
  {
	  MPI_Send ( &sumatoria, MSGSIZE, MPI_INT, sucesor, TAG, MPI_COMM_WORLD );
		
		MPI_Recv ( &sumatoria, MSGSIZE, MPI_INT, predecesor, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
		if ((1/2) * (p - 1) * p == 0)
		{
			printf("Verificado, la sumatoria es: %d\n", sumatoria);
		}
		else
		{
			printf("Erroneo");
		}
  }
  else
  {
  	MPI_Recv ( &sumatoria, MSGSIZE, MPI_INT, predecesor, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
		// printf ( "proc%d SumatoriaR %d\n", my_rank, sumatoria );
				 		
		sumatoria += my_rank;
		MPI_Send ( &sumatoria, MSGSIZE, MPI_INT, sucesor, TAG, MPI_COMM_WORLD );
  }
  
  MPI_Finalize ();
  return 0;
}
