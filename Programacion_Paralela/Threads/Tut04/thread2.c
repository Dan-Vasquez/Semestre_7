/*******************************************************************************
*
*  thread2.c -    A program that executes 2 threads concurrenly
*
*   Notes:
*
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/***( Function prototypes )***********************************************/

void  *thread_function ( void *arg_ptr );

/***( Global variables )**************************************************/

int   run_now;                            /* global, shared variable */

/***( Program Code )******************************************************/

/* Code to be executed by the main thread */
int main ( void )
{
  int       res;
  pthread_t a_thread;
  void      *thread_result;
  int       print_count1;

  run_now = 1;
  print_count1 = 0;
  res = pthread_create ( &a_thread, NULL, thread_function, NULL );
  if (res != 0)
  {
    perror ( "Thread creation failed" );
    exit ( EXIT_FAILURE );
  }

  while ( print_count1++ < 20 )
  {
    if ( run_now == 1 )
    {
      printf ( "m " );
      fflush ( stdout );
      run_now = 2;
    }
    else
      sleep ( 1 );
  }

  printf ( "\nWaiting for spawned thread to finish...\n" );
  res = pthread_join ( a_thread, &thread_result );
  if ( res != 0 )
  {
    perror ( "Thread join failed" );
    exit ( EXIT_FAILURE );
  }
  printf ( "Thread joined\n" );
  exit ( EXIT_SUCCESS );
}

/* Code to be executed by the spawned thread */
void *thread_function ( void *arg_ptr )
{
  int print_count2;

  print_count2 = 0;
  while ( print_count2++ < 20 )
  {
    if ( run_now == 2 )
    {
      printf ( "s " );
      fflush ( stdout );
      run_now = 1;
    }
    else
      sleep ( 1 );
  }

  sleep ( 3 );
  pthread_exit ( NULL );
}
