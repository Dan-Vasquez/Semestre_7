#include <stdlib.h>
#include <stdio.h>

#define TpB 32
#define BpG 32
__global__ void MatMulKernel ( int * MA, int * MB, int * MY, int N)
{
  __shared__ int sharedMA[TpB][TpB];
  __shared__ int sharedMB[TpB][TpB];
  int bx = blockIdx.x;
  int by = blockIdx.y;
  int tx = threadIdx.x;
  int ty = threadIdx.y;
  int row = by * TpB + ty;
  int col = bx * TpB + tx;

  int Yval = 0;
  for (int t = 0; t<N/TpB;++t){
  	sharedMA[ty][tx] = MA[row * N + t * TpB + tx];
  	sharedMB[ty][tx] = MB[(t * TpB + ty) * N + col];
  	__syncthreads();
  	for (int k = 0; k < TpB; ++k){
  		Yval += sharedMA[ty][k] * sharedMB[k][tx];
  	}
  	__syncthreads();
  }
  MY[row * N + col] = Yval;
}
/*--( Support functions )------------------------------------------------*/

/* Initialise matrices of the given size */


/* Print matrix of the given size */
void PrintMatrix ( int *matrix, int size )
{
  int row,
      col;

  for ( row = 0; row < size; row++ )
  {
    for ( col = 0; col < size; col++ )
      printf ( "%8d ", matrix [row * size + col] );
    printf ( "\n" );
  }
  printf ( "\n" );
}

/*--( Main function )----------------------------------------------------*/

int main ( int argc, char *argv[] )
{
  int *MA,
      *MB,
      *MY;
  int *d_MA,
      *d_MB,
      *d_MY;
  int N,
      size,
      TpBx,
      TpBy;


  scanf("%d", &N);
    size = N * N * sizeof(int);
    MA = (int *) malloc ( size );
    MB = (int *) malloc ( size );
    for (int i = 0; i < N * N; i++){
        scanf("%d,", &MA[i]);
    }
    for (int i = 0; i < N * N; i++){
        scanf("%d,", &MB[i]);
    }
  /* set MY = { {0} } */
  MY = (int *) malloc ( size );
  memset ( (void *) MY, 0, size );
  //Creacion de eventos para calculo de tiempo
  cudaEvent_t tstart, tstop;

  cudaEventCreate(&tstart);
  cudaEventCreate(&tstop);

  cudaEventRecord(tstart, 0);

  cudaMalloc ( &d_MA, size );
  cudaMalloc ( &d_MB, size );

  cudaMemcpy ( d_MA, MA, size, cudaMemcpyHostToDevice );
  cudaMemcpy ( d_MB, MB, size, cudaMemcpyHostToDevice );

  cudaMalloc ( &d_MY, size );
  cudaMemcpy ( d_MY, MY, size, cudaMemcpyHostToDevice );

  // Creacion del grid
  dim3 gridSize ( BpG, BpG );

  //---------------------------
  // int deviceId;
  //cudaGetDevice ( &deviceId );

 // cudaDeviceProp props;
  //cudaGetDeviceProperties ( &props, deviceId );

  //int MultiProcs = props.multiProcessorCount;
 // int warpSize = props.warpSize;

  /* Launch add () kernel on GPU */
  //printf ( "GPU vector addition of %d elements using %d blocks, %d threads per block; warp size = %d\n",
  //         N, 32 * MultiProcs, THREADS_PER_BLOCK, warpSize );
  //-------------------------------
  TpBx = N / gridSize.x;
  TpBy = N / gridSize.y;
  // Creacion de las particiones en cada bloque
  dim3 blockSize ( TpBx, TpBy );

  MatMulKernel <<< gridSize, blockSize >>> ( d_MA, d_MB, d_MY, N );

  cudaMemcpy ( MY, d_MY, size, cudaMemcpyDeviceToHost );

  cudaEventRecord( tstop, 0);
  cudaEventSynchronize( tstop);

  float elapsedTime;
  cudaEventElapsedTime(&elapsedTime, tstart, tstop);
  printf("Tiempo de ejecucion CUDA: %3.1f ms \n", elapsedTime);
  printf ( "\n%dx%d Y Matrix is \n", N, N );
  PrintMatrix ( MY, N );

  cudaFree ( d_MA );
  cudaFree ( d_MB );
  cudaFree ( d_MY );

  free ( MA );
  free ( MB );
  free ( MY );
}