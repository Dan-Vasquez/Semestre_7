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
CFLAGS		= -Wall

PROGRAM 	= Ejercicio1_2

PROGRAMS	= Ejercicio1_1 Ejercicio1_2

PROCS		= 2

#
# Targets, in order of appearance
#

$(PROGRAM): $(PROGRAM).c
	$(CC) $(CFLAGS) $(PROGRAM).c -o $(PROGRAM)

#
# Other nice thingys
#

all: $(PROGRAMS)

clean:
	rm -f *% *~ core *.o $(PROGRAMS)

run:
	@clear; echo "Will run $(PROGRAM) using $(PROCS) processes:"; mpiexec -n $(PROCS) $(PROGRAM)

auto_run:
	@clear; echo -e "Will run $(PROGRAM) using `getconf _NPROCESSORS_ONLN` CPUs (logical cores) on host `hostname`:\n`lscpu` "; mpiexec -n `getconf _NPROCESSORS_ONLN` $(PROGRAM)
