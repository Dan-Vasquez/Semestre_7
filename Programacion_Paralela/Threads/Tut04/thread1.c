/*******************************************************************************
*
*  thread1.c -    A simple program using threads
*
*   Notes:
*
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/***( Function prototypes )***********************************************/

void *thread_function ( void *arg_ptr );

/***( Global variables )**************************************************/

char message[] = "Hello World";       /* shared variable */

/***( Program Code )******************************************************/

/* Code to be executed by the main thread */
int main ( void )
{
  int       res;
  pthread_t a_thread;
  void      *thread_result;

  res = pthread_create ( &a_thread, NULL, thread_function, (void *) message );
  if ( res != 0 )
  {
    perror ( "Thread creation failed" );
    exit ( EXIT_FAILURE );
  }

  printf ( "Waiting for thread to finish...\n" );
  res = pthread_join ( a_thread, &thread_result );
  if ( res != 0 )
  {
    perror ( "Thread join failed" );
    exit ( EXIT_FAILURE );
  }
  printf ( "Thread joined, it returned `%s'\n", (char *) thread_result );

  printf ( "Message is now %s\n", message );

  exit ( EXIT_SUCCESS );
}

/* Code to be executed by the spawned thread */
void *thread_function ( void *arg_ptr )
{
  printf ( "\tthread_function is running. Argument was `%s'\n", (char *) arg_ptr );
  sleep ( 3 );
  strcpy ( message, "Bye!" );
  pthread_exit ( "Thank you for the CPU time" );
}
