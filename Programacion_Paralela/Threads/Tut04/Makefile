#
# Makefile for make
#
# Compiler: gcc
#

CC = gcc

CFLAGS=-D_REENTRANT -Wall
LDLIBS=-lpthread
PROG = thread0
PROGS = thread0 thread1 thread2 thread3 thread4 thread5

all: $(PROGS)

clean:
	rm -f $(PROGS) *~ *.o
run: @clear; 