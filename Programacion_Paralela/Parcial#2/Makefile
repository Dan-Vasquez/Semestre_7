#
# Departamento de Electronica y Ciencias de la Computacion
# Facultad de Ingenieria y Ciencias
# Pontificia Universidad Javeriana - CALI
#
# MPI Examples
# Sample Makefile
#

#
# Set the compilers and associated flags
#

CC		= mpicc
CFLAGS		= -Wall -fopenmp

PROGRAM 	= Codigo_ParaleloOpenMP
PROGRAMS	= Codigo_Secuencial Codigo_ParaleloOpenMP Codigo_ParaleloMPI Codigo_ParaleloComplete
 
PROCS		= 2

THREADS	= 4

DATA = MyData4.csv

## prueba con banderas

VFLAGS1 = -fthread-jumps -faggressive-loop-optimizations
VFLAGS2 = -fstrict-aliasing -ftree-vectorize -march=native -std=gnu99
#
# Targets, in order of appearance
#

$(PROGRAM): $(PROGRAM).c
	$(CC) $(CFLAGS) $(VFLAGS2) $(PROGRAM).c -o $(PROGRAM)

#
# Other nice thingys
#

all: $(PROGRAMS)

clean:
	rm -f *% *~ core *.o $(PROGRAMS)

run:
	@clear; echo "Will run $(PROGRAM) using $(PROCS) processes:"; mpiexec -n $(PROCS) $(PROGRAM) < $(DATA)

runH:
	@echo "Will run $(PROGRAM) using $(THREADS) threads:"; export OMP_NUM_THREADS=$(THREADS); ./$(PROGRAM) < $(DATA)

runP:
	@echo "Will run $(PROGRAM) using $(THREADS) threads and $(PROCS) processes:"; export OMP_NUM_THREADS=$(THREADS); mpiexec -n $(PROCS) $(PROGRAM) < $(DATA)

auto_run:
	@clear; echo -e "Will run $(PROGRAM) using `getconf _NPROCESSORS_ONLN` CPUs (logical cores) on host `hostname`:\n`lscpu` "; mpiexec -n `getconf _NPROCESSORS_ONLN` $(PROGRAM)
