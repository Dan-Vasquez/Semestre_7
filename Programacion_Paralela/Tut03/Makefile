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
CFLAGS		= -Wall
LDLIBS		= -lm

PROGRAM 	= cpi_p2p

PROGRAMS 	= cpi_copns probe-status MPITimeIt0 MPITimeIt1 MPITimeIt2 MPITimeIt3 MPITimeIt4 scatter-gather scatter-allgather allreduce

PROCS		= 2

#
# Targets, in order of appearance
#

all: $(PROGRAMS)

#allreduce: allreduce.c
#	mpicc -Wall allreduce.c -lm -o allreduce

#
# Other nice thingys
#

clean:
	rm -f *% *~ core *.o $(PROGRAMS)

run:
	@echo "Will run $(PROGRAM) using $(PROCS) processes:"; mpiexec -n $(PROCS) $(PROGRAM)

auto_run:
	@echo -e "Will run $(PROGRAM) using `getconf _NPROCESSORS_ONLN` CPUs (logical cores) on host `hostname`:\n`lscpu` "; mpiexec -n `getconf _NPROCESSORS_ONLN` $(PROGRAM)
