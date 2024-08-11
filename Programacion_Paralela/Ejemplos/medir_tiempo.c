
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


#include <unistd.h>


#define PROCESS0 0
int main(int argc, char *argv[]){

	int p, my_rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Synchronise all the processes so they start at about the same time */
	MPI_Barrier ( MPI_COMM_WORLD );
	double tstart,
	e_time;
	/* Start timer */
	tstart = MPI_Wtime ();
	/* Compute local workload */
	/* Stop timer */
	sleep(my_rank);
	e_time = MPI_Wtime () - tstart;
	double e_times [p];
	/* gather all the execution times to process 0 */
	MPI_Gather ( &e_time, 1, MPI_DOUBLE,
	e_times, 1, MPI_DOUBLE, PROCESS0, MPI_COMM_WORLD );
	/* print execution times */
	if ( my_rank == PROCESS0 )
	{
	for ( int rank = 0; rank < p; rank++ )
		printf ( "Execution time for proc%d is %lf\n",
	rank, e_times [rank] );
}
	MPI_Finalize();
	return 0;
}
