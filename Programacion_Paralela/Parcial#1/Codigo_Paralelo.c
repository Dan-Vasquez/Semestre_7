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
  int sum = 0;
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  // distribution between the processes
  if (my_rank == PROCESS0) 
  {
    // input size
    int size;
    scanf("%d", &size);
    // dinamic vectors
    int *vect1 = (int *)malloc(sizeof(int) * size), *vect2 = (int *)malloc(sizeof(int) * size);
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
    int partition = size / p;
    // size calculation to send
    int start = partition, end = partition * 2;
    // send of data to processes
    for (int i = 1; i < p; i++) 
    {
      MPI_Send(&partition, MSGSIZE, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(&vect1[start], partition, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(&vect2[start], partition, MPI_INT, i, 0, MPI_COMM_WORLD);
      start = end;
      end = (start + partition);
    }
    int total_sum;
    total_sum = dot_product(partition, vect1,vect2);

    for (int i = 1; i < p; i++) {
      MPI_Recv(&sum, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      total_sum += sum;
    }
    int sequential_sum = 0;
    sequential_sum = dot_product(size, vect1, vect2);
    printf("sequential dot product: %d\n", sequential_sum);
    printf("parallel dot product: %d\n", total_sum);
    printf("difference %d", total_sum - sequential_sum);
    free(vect1);
    free(vect2);
  } 
  else 
  {
    // partition receipt
    int received_partition;
    MPI_Recv(&received_partition, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // vector creation
    int *sub_vect1 = (int *)malloc(sizeof(int) * received_partition), *sub_vect2 = (int *)malloc(sizeof(int) * received_partition);
    MPI_Recv(sub_vect1, received_partition, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(sub_vect2, received_partition, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    sum = dot_product(received_partition, sub_vect1,sub_vect2);
    
    MPI_Send(&sum, 1, MPI_INT, PROCESS0, 0, MPI_COMM_WORLD);
    free(sub_vect1);
    free(sub_vect2);
  }
  MPI_Finalize();
  return 0;
}
