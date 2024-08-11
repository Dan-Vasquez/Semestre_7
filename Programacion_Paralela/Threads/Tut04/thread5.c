/*******************************************************************************
*
*  thread5.c -    A program that shows how to create as many threads as logical
*                   coreas are available in the executing platform
*
*   Notes:        Some error checking omitted...
*
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <pthread.h>

/***( Function prototypes )***********************************************/

void *printHello ( void *threadArg_ptr );

/***( Type declarations )*************************************************/

typedef struct
{
  long  thread_num;     /* thread numer */
  long  num_threads;    /* total number of threads */
} threadData;

/***( Program Code )******************************************************/

/* Code to be executed by the main thread */
int main ( void )
{
  pthread_t   *threads;
  long        *taskids;
  void        *thread_result;
  long        t_num;
  long        numCores,
              t;
  threadData  *threadArg_ptr;
  int         rc;

  /* Determine the number of logical cores currently online (available) */
  numCores = sysconf ( _SC_NPROCESSORS_ONLN );

  /* Allocate memory to store as many thread ids as logical cores are available:
      pthread_t threads [numCores] */
  threads = (pthread_t *) malloc ( numCores * sizeof(pthread_t) );
  if ( threads == NULL )
  {
    printf ( "Out of memory.\n" );
    return ( -1 );
  }

  /* Allocate memory to store as many task ids as logical cores are available:
      long taskids [numCores] */
  taskids = (long *) malloc ( numCores * sizeof(long) );
  if ( taskids == NULL )
  {
    printf ( "Out of memory.\n" );
    return ( -1 );
  }

  /* Allocate memory for 1D struct array: "threadData threadArg_ptr[numCores];" */
  threadArg_ptr = (threadData  *) malloc ( numCores * sizeof(threadData) );
  t = numCores;

  /* Determine the number of processors currently online (available) */
  numCores = sysconf ( _SC_NPROCESSORS_ONLN );

  /* Spwan as many threads as logical cores available in this machine */
  printf ( "%ld threads will execute the printHello function\n", numCores );
  for ( t_num = 0; t_num < numCores; t_num++ )
  {
    taskids [t_num] = t_num;              /* preserve task number */
    threadArg_ptr->thread_num = t_num;    /* pack task number into threadArg_ptr[num].thread_num */
    threadArg_ptr->num_threads = t;       /* pack number of tasks into threadArg_ptr[num].num_threads */
    rc = pthread_create ( &threads[t_num], NULL, printHello, (void *) threadArg_ptr );
    threadArg_ptr++;
    if ( rc != 0 )
    {
      printf ( "ERROR; return code from pthread_create() is %d (task %ld)\n", rc, t_num );
      return ( -1 );
    }
  }
  for ( t_num = 0; t_num < numCores; t_num++ )
  {
    rc = pthread_join ( threads[t_num], &thread_result );
    if ( rc != 0 )
    {
      printf ( "ERROR; return code from pthread_join() is %d (task %ld)\n", rc, t_num );
      return ( -1 );
    }
  }

  return ( 0 );
}

/* Code to be executed by the spawneds threads */
void *printHello ( void *threadArg_ptr )
{
  long  t_num,
        t;

  threadData *my_data;

  my_data = (threadData *) threadArg_ptr;
  t_num = my_data->thread_num;
  t = my_data->num_threads;

  printf ( "\tHello from spawned thread %ld out of %ld\n", t_num, t );
  pthread_exit ( NULL );
}
