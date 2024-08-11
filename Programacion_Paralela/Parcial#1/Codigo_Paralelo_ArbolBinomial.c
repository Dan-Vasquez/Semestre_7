/* Parcial #1 Prog. Paralela
 - Miguel Angel Nivia (8958691)
 - Daniel Andres Vasquez (8963154)
 - Willian Chapid Tobar (8965113)
 
 Codigo #3 Paralelo Arbol Binomial
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define PROCESS0 0
#define MSGSIZE  1
#define iterations(x) (log(x)/log(2)) 
#define send(x, n) (x + pow(2,n))
#define receive(x, n) (x - pow(2,n))

enum msg_tags
{
  SENDTAG,
  RECEIVETAG
};

int dot_product(int size, int *vect1, int *vect2){
  int sum = 0; 
  for (int i = 0; i < size; i++) 
  {
    sum += vect1[i] * vect2[i];
  } 
  return sum;
}
int main ( int argc, char *argv[] )
{
  int  my_rank, p;
  MPI_Init ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );
  MPI_Comm_size ( MPI_COMM_WORLD, &p );
  int end, partition, num_iterations, sum, total_sum;
  total_sum = 0;
  sum = 0;
  num_iterations = 0;
  end = 0;
  partition = 0;
  num_iterations = (int)(iterations(p));
  int son;
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
    // sending partitions
    end = size;
    for( int i = 0; i<num_iterations;i++)
    {
      son = send(my_rank, i);
      partition = (int)(end/2);
      end = partition;
      MPI_Send(&partition, MSGSIZE, MPI_INT, son, SENDTAG, MPI_COMM_WORLD);
      MPI_Send(&vect1[end], partition,MPI_INT, son,SENDTAG,MPI_COMM_WORLD);
      MPI_Send(&vect2[end], partition, MPI_INT, son, SENDTAG, MPI_COMM_WORLD);
    }
    // dot product calculation
    total_sum = dot_product(end, vect1,vect2);
    //partial sums receipt
    for(int i = num_iterations-1; i>= 0;i--)
    {
      son = send(my_rank, i);
      MPI_Recv(&sum, MSGSIZE, MPI_INT, son, RECEIVETAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      total_sum += sum;
    }
    //result vs sequential calculation
    int sequential_sum;
    sequential_sum = dot_product(size, vect1, vect2);
    printf("parallel binomial dot product: %d\n", total_sum);
    printf("sequential dot product: %d\n", sequential_sum); 
    printf("difference %d", total_sum - sequential_sum);
    free(vect1);
    free(vect2);
  }
  else
  {
    int daddy;
    int my_level;
    //nivel calculation
    my_level = ceil(log2(my_rank + 1 ));
    //dad calculation
    daddy = receive(my_rank, my_level-1);
    // partition receipt
    MPI_Recv(&partition, MSGSIZE, MPI_INT, daddy, SENDTAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // vectors creation
    int *sub_vect1 = (int *)malloc(sizeof(int) * partition), *sub_vect2 = (int *)malloc(sizeof(int) * partition);
    // vectors data receipt
    MPI_Recv(sub_vect1, partition, MPI_INT, daddy, SENDTAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(sub_vect2, partition, MPI_INT, daddy, SENDTAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //sending of partitions
    end = partition;
    for( int i = my_level; i < num_iterations;i++)
    {
      son = send(my_rank, i);
      partition = (int)(end/2);
      end = partition;
      MPI_Send(&partition, MSGSIZE, MPI_INT, son, SENDTAG, MPI_COMM_WORLD);
      MPI_Send(&sub_vect1[end], partition,MPI_INT,son,SENDTAG,MPI_COMM_WORLD);
      MPI_Send(&sub_vect2[end], partition, MPI_INT, son, SENDTAG, MPI_COMM_WORLD);

    }
    // dot product calculation
    total_sum = dot_product(end, sub_vect1,sub_vect2);
    // partial sums receipt
    for(int i = my_level; i < num_iterations;i++)
    {
      son = send(my_rank,i);
      MPI_Recv(&sum, MSGSIZE, MPI_INT, son , RECEIVETAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      total_sum += sum;
    }
    // sending partial sum
    MPI_Send(&total_sum, MSGSIZE, MPI_INT, daddy, RECEIVETAG, MPI_COMM_WORLD);
    free(sub_vect1);
    free(sub_vect2);

  }
  MPI_Finalize ();
	return 0;
}
