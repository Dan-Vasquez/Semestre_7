/* Parcial #1 Prog. Paralela
 - Miguel Angel Nivia (8958691)
 - Daniel Andres Vasquez (8963154)
 - Willian Chapid Tobar (8965113)
 
 Codigo #2 Paralelo
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define PROCESS0 0
#define MSGSIZE  1

int dot_product(int size, int *vect1, int *vect2){
  int sum = 0; 
  for (int i = 0; i < size; i++) 
  {
    sum += vect1[i] * vect2[i];
  } 
  return sum;
}

int main(int argc, char *argv[]) {
	
  int  my_rank, p;
  int size;
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  // distribution between the processes
  int *vect1 = NULL;
  int *vect2 = NULL;
  int partition;
  if (my_rank == PROCESS0) 
  {
    // input size
    
    scanf("%d", &size);
    // dinamic vectors
      vect1 = (int *)malloc(sizeof(int) * size), vect2 = (int *)malloc(sizeof(int) * size);
    // input Vect1
    for (int i = 0; i < size; i++) 
    {
      scanf("%d,", &vect1[i]);
    }
    // input Vect2
    for (int i = 0; i < size; i++) 
    {
      scanf("%d,", &vect2[i]);
    }

    // partition calculation
    partition = size / p;
    MPI_Bcast(&partition, 1, MPI_INT, PROCESS0, MPI_COMM_WORLD);
    
    }
    int *sub_vect1 = NULL;
    int *sub_vect2 = NULL;
    sub_vect1 = (int *)malloc(sizeof(int) * partition), sub_vect2 = (int *)malloc(sizeof(int) * partition);
    MPI_Scatter(vect1, partition, MPI_INT,
                sub_vect1, partition, MPI_INT,
                PROCESS0, MPI_COMM_WORLD);
    MPI_Scatter(vect2, partition, MPI_INT,
                sub_vect2, partition, MPI_INT,
                PROCESS0, MPI_COMM_WORLD);
    int total_sum;
    total_sum = dot_product(partition, sub_vect1, sub_vect2);
    int *parcial_sum;
    if ( my_rank == PROCESS0)
    {
      parcial_sum = (int * ) malloc (sizeof (double) * p);
    }
    MPI_Gather(&total_sum, 1, MPI_INT,
                parcial_sum, 1, MPI_INT,
                PROCESS0, MPI_COMM_WORLD);
    total_sum = 0;
    if (my_rank == PROCESS0)
    {
      for ( int i = 0; i <p; i++)
      {
        total_sum+=parcial_sum[i];
      }
      int sequential_sum = 0;
      sequential_sum = dot_product(size, vect1, vect2);
      printf("sequential dot product: %d\n", sequential_sum);
      printf("parallel dot product: %d\n", total_sum);
      printf("difference %d", total_sum - sequential_sum);
      free(vect1);
      free(vect2);
    }
    free(sub_vect1);
    free(sub_vect2);
  MPI_Finalize();
  return 0;
}
