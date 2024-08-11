/*******************************************************************************
*
*  thread0.c -    Shows how to obtain some thread attributes
*
*   Notes:        Error checking omitted...
*
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/***( Function prototypes )***********************************************/

void *thread_function ( void *arg_ptr );

/***( Program Code )******************************************************/

/* Code to be executed by the main thread */
int main ( int argc, char *argv[] )
{
  pid_t       pid;            /* This process PId */
  pthread_t   a_thread;       /* Spawned thread TId */
  pthread_t   tid;            /* This thread TId */
  void        *thread_result;

  pid = getpid ();            /* Get process PId */
  tid = pthread_self ();      /* Get thread PId */
  printf ( "This process is called %s, its PId is %d; thread TId is %lu\n",
            argv[0], pid, tid );

  pthread_create ( &a_thread, NULL, thread_function, NULL );

  printf ( "Main thread is waiting for thread with TId %lu to finish...\n", a_thread );
  pthread_join ( a_thread, &thread_result );
  printf ( "Thread with TId %lu joined, it returned `%s´\n", a_thread,
           (char *) thread_result );

  exit ( EXIT_SUCCESS );
}

/* Code to be executed by the spawned thread */
void *thread_function ( void *arg_ptr )
{
  pid_t       pid;            /* This process PId */
  pthread_t   tid;            /* This thread TId */

  pid = getpid ();            /* Get process PId */
  tid = pthread_self ();      /* Get thread PId */
  printf ( "\tThis process PId is %d; thread TId is %lu\n", pid, tid );

  pthread_exit ( "Bye!" );
}
