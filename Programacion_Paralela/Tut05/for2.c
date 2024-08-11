/*******************************************************************************
*                                                                              *
*  for2.c - A program to illustrate using nested loops and
*           the parallel for directive
*                                                                              *
*   Departamento de Electronica y Ciencias de la Computacion                   *
*   Pontificia Universidad Javeriana - CALI                                    *
*                                                                              *
*******************************************************************************/


#include <stdio.h>
#include <omp.h>

#define SIZE  1024

int main ( int argc, char *argv[] )
{
  int row,
      col,
      matrix [SIZE][SIZE];

  #pragma omp parallel for private(col)
  for ( row = 0; row < SIZE; row++ )
    for ( col = 0; col < SIZE; col++ )
      matrix [row][col] = 0;

  return ( 0 );
}
