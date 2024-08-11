#
# Departamento de Electronica y Ciencias de la Computacion
# Facultad de Ingenieria u Ciencias
# Pontificia Universidad Javeriana - CALI
#
# MPI Examples
# Sample Makefile
#

#
# Set the compilers and associated flags
#

CC		= mpicc

OMPFLAGS = -fopenmp

CFLAGS		= -Wall $(OMPFLAGS)

PROGRAM 	= dot_vector_mpi

PROGRAMS 	= pi_mp pi_mp_mpi cpi_serial dot_vector_mpi

PROCS		= 2

#
# Targets, in order of appearance
#

all: $(PROGRAMS)

cpi_serial: cpi_serial.c
	gcc -Wall -o cpi_serial cpi_serial.c

#
# Other nice thingys
#

clean:
	rm -f *% *~ core *.o $(PROGRAMS)

run:
	@echo "Will run $(PROGRAM) using $(PROCS) processes:"; mpiexec -n $(PROCS) $(PROGRAM)

auto_run:
	@echo -e "Will run $(PROGRAM) using `getconf _NPROCESSORS_ONLN` CPUs (logical cores) on host `hostname`:\n`lscpu` "; mpiexec -n `getconf _NPROCESSORS_ONLN` $(PROGRAM)
