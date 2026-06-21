# Makefile for dgemv with OpenMP
CC      = gcc
FLAGS   = -O3 -s -pipe -Wall -fomit-frame-pointer -march=native \
          -I../array -w
LIBRARY = ../array/array.a
EXEC    = dgemv

all: $(EXEC)

$(EXEC): $(EXEC).c
	$(CC) $(FLAGS) -c $(EXEC).c -fopenmp
	$(CC) $(FLAGS) -o $(EXEC) $(EXEC).o $(LIBRARY) -lblas -fopenmp

clean:
	(rm -f core *.o *~ $(EXEC))
