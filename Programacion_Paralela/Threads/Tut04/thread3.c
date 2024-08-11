/*******************************************************************************
*
*  thread3.c -    A program that synchronizes threads using semaphores.
*
*   Notes:        Some error checking omitted...
*
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

/***( Manifest constants )************************************************/

#define WORK_SIZE 1024

/***( Function prototypes )***********************************************/

void *thread_function ( void *arg_ptr );

/***( Global variables )**************************************************/

sem_t bin_sem;                    /* semaphore */

char  work_area [WORK_SIZE];      /* CRITICAL REGION */

/***( Program Code )******************************************************/

/* Code to be executed by the main thread */
int main ( void )
{
  int       res;
  pthread_t a_thread;
  void      *thread_result;

  res = sem_init ( &bin_sem, 0, 0 );
  if  ( res != 0 )
  {
    perror ( "Semaphore initialisation failed" );
    exit ( EXIT_FAILURE );
  }

  res = pthread_create ( &a_thread, NULL, thread_function, NULL );
  if  ( res != 0 )
  {
    perror ( "Thread creation failed" );
    exit ( EXIT_FAILURE );
  }

  printf ( "Input some text. Enter 'end' to finish\n" );
  while ( strncmp ( "end", work_area, 3 ) != 0 )
  {
    fgets ( work_area, WORK_SIZE, stdin );
    sem_post ( &bin_sem );
  }

  printf ( "\nWaiting for thread to finish...\n" );
  res = pthread_join ( a_thread, &thread_result );
  if  ( res != 0 )
  {
    perror ( "Thread join failed" );
    exit ( EXIT_FAILURE );
  }
  printf ( "Thread joined\n" );

  sem_destroy ( &bin_sem );

  exit ( EXIT_SUCCESS );
}

/* Code to be executed by the spawned thread */
void *thread_function ( void *arg_ptr )
{
  sem_wait ( &bin_sem );
  while ( strncmp ( "end", work_area, 3 ) != 0 )
  {
    printf ( "\tYou input %d characters\n", ( int ) ( strlen (work_area) - 1 ) );
    sem_wait ( &bin_sem );
  }
  pthread_exit ( NULL );
}
