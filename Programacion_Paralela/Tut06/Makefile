#
# Departamento de Electronica y Ciencias de la Computacion
# Facultad de Ingenieria u Ciencias
# Pontificia Universidad Javeriana - CALI
#
# OpenMP Examples
# Sample Makefile
#

#
# Set the compilers and associated flags
#

CC		= gcc
OMPFLAGS	= -fopenmp
CFLAGS		= -Wall $(OMPFLAGS)

PROGRAM 	= for3

PROGRAMS        = for3 for4 for5 for6 mpi_omp0 cpit0

PROCS           = 2

THREADS		= 2

#
# Targets, in order of appearance
#

all: $(PROGRAMS)

mpi_omp0: mpi_omp0.c
	mpicc $(CFLAGS) mpi_omp0.c -o mpi_omp0

cpit0: cpit0.c
	mpicc $(CFLAGS) cpit0.c -o cpit0

#
# Other nice thingys
#

clean:
	rm -f *% *~ core *.o $(PROGRAMS) $(PROGRAM)

run:
	@echo "Will run $(PROGRAM) using $(THREADS) threads:"; export OMP_NUM_THREADS=$(THREADS); ./$(PROGRAM)

runa:
	@echo "Will run mpi_omp0 using $(PROCS) processes and $(THREADS) threads per process:"; export OMP_NUM_THREADS=$(THREADS); mpiexec -n $(PROCS) ./mpi_omp0

auto_run:
	@echo -e "Will run $(PROGRAM) using `getconf _NPROCESSORS_ONLN` CPUs (logical cores) on host `hostname`:\n`lscpu` "; ./$(PROGRAM)
