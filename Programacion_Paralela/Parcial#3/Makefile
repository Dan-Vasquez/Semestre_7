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
SS = gcc
CC	= mpicc
CUCU = nvcc
CFLAGS		= -Wall -fopenmp

PROGRAM 	= Codigo_ParaleloMPI

PROGRAMS	= Codigo_Secuencial Codigo_ParaleloMPI DotMatMat
 
PROCS		= 2

THREADS	= 4

DATA = MyData4.csv


all: $(PROGRAMS)

DotMatMat: DotMatMat.cu
	$(CUCU) $(CFLAGS) DotMatMat.cu -o DotMatMat
Secuencial: Codigo_Secuencial.c
	$(SS) $(CFLAGS) Codigo_Secuencial.c -o Codigo_Secuencial
ParaleloMPI: Codigo_ParaleloMPI.c
	$(CC) $(CFLAG) Codigo_ParaleloMPI.c -o Codigo_ParaleloMPI
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

