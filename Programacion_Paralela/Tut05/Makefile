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

PROGRAM 	= omp0

PROGRAMS        = omp0 omp1 omp2 omp3 omp4 omp5 omp6 omp7 omp8 for0 for1 for2 for3 races critical atomic reduction

THREADS		= 2

#
# Targets, in order of appearance
#

all: $(PROGRAMS)

#
# Other nice thingys
#

clean:
	rm -f *% *~ core *.o $(PROGRAMS) $(PROGRAM)

run:
	@echo "Will run $(PROGRAM) using $(THREADS) threads:"; export OMP_NUM_THREADS=$(THREADS); ./$(PROGRAM)

auto_run:
	@echo -e "Will run $(PROGRAM) using `getconf _NPROCESSORS_ONLN` CPUs (logical cores) on host `hostname`:\n`lscpu` "; ./$(PROGRAM)
