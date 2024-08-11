/*******************************************************************************
*
*  thread4.c -    A program that shows how to pass arguments to a thread
*                   and how the thread can receive and use these parameters
*
*   Notes:        Some error checking omitted...
*
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/***( Function prototypes )***********************************************/

void *thread_function1 ( void *arg_ptr );
void *thread_function2 ( void *arg_ptr );

/***( Program Code )******************************************************/

/* Code to be executed by the main thread */
int main ( void )
{
  pid_t       pid;            /* This process PId */
  pthread_t   a_thread[10];   /* Spawned thread TIds */
  pthread_t   tid;            /* This thread TId */
  int         i;
  void        *thread_result;

  pid = getpid ();            /* Get process PId */
  tid = pthread_self ();      /* Get thread PId */
  printf ( "This process PId is %d; main thread TId is %lu\n", pid, tid );

  for ( i = 0; i < 5; i++ )
  {
    pthread_create ( &a_thread[i], NULL, thread_function1, (void *) &i );
    usleep ( 100000 );
  }
  for ( ; i < 10; i++ )
  {
    pthread_create ( &a_thread[i], NULL, thread_function2, (void *) &i );
    usleep ( 100000 );
  }

  for ( i = 0; i < 10; i++ )
  {
    pthread_join ( a_thread[i], &thread_result );
  }

  exit ( EXIT_SUCCESS );
}

/* Code to be executed by the first five spawned threads */
void *thread_function1 ( void *arg_ptr )
{
  pid_t       pid;            /* This process PId */
  pthread_t   tid;            /* This thread TId */
  int         my_data,
              *data_ptr;

  data_ptr = (int *) arg_ptr;
  my_data = *data_ptr;

  pid = getpid ();            /* Get process PId */
  tid = pthread_self ();      /* Get thread PId */
  printf ( "\tThis process PId is %d. Hello from spawned thread %d; TId is %lu\n", pid, my_data, tid );

  pthread_exit ( NULL );
}

/* Code to be executed by the last five spawned threads */
void *thread_function2 ( void *arg_ptr )
{
  pid_t       pid;            /* This process PId */
  pthread_t   tid;            /* This thread TId */
  int         my_data,
              *data_ptr;

  data_ptr = (int *) arg_ptr;
  my_data = *data_ptr;

  pid = getpid ();            /* Get process PId */
  tid = pthread_self ();      /* Get thread PId */
  printf ( "\t\tThis process PId is %d. Greetings from spawned thread %d; TId is %lu\n", pid, my_data, tid );

  pthread_exit ( NULL );
}
