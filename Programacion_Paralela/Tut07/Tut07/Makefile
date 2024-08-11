#
# Departamento de Electronica y Ciencias de la Computacion
# Facultad de Ingenieria u Ciencias
# Pontificia Universidad Javeriana - CALI
#
# Sample Makefile
#

#
# Set the compilers and associated flags
#

CC		= gcc
CFLAGS		= -O4
#VFLAGS		= -fstrict-aliasing -ftree-vectorize -march=native -mtune=native -fopt-info-vec-optimized -std=gnu99
# use the one below if running on a Xeon Phi x200 (or later) and Skylake-X (7th generation or later)
VFLAGS		= -fstrict-aliasing -ftree-vectorize -march=native -mtune=native -fopt-info-vec-optimized -mprefer-vector-width=512 -std=gnu99

#
# Targets, in order of appearance
#

all: rowVcol_major cpit1 stream_triad_plain stream_triad

timer.o: timer.c timer.h
	gcc -Wall -c timer.c

rowVcol_major: rowVcol_major.c timer.o
	gcc -Wall -c rowVcol_major.c; gcc -o rowVcol_major rowVcol_major.o timer.o

cpit1: cpit1.c timer.o
	mpicc -Wall -fopenmp -c cpit1.c; mpicc -fopenmp -o cpit1 cpit1.o timer.o

stream_triad_plain: stream_triad.c timer.o
	gcc -Wall -c stream_triad.c -o stream_triad_plain.o; gcc -o stream_triad_plain stream_triad_plain.o timer.o

stream_triad: stream_triad.c timer.o
	gcc -Wall -c $(CFLAGS) $(VFLAGS) stream_triad.c; gcc -o stream_triad stream_triad.o timer.o

clean:
	-rm -f *.o *.s rowVcol_major cpit1 stream_triad_plain stream_triad
