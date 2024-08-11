#define gpuErrChk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert ( cudaError_t rc, const char *file, int line, bool abort=true )
{
  if ( rc != cudaSuccess )
  {
    fprintf ( stderr, "GPUassert: %s %s %d\n", cudaGetErrorString (rc), file, line );
    if ( abort )
      exit ( rc );
  }
}
