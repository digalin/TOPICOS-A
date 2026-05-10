#/**
# \file
# @brief Makefile for dgemm: sample program for cblas_dgemm function and other algorithms for the matrix-matrix product.
# @author Diego
# @date May 2nd, 2026
# */
CC = gcc
FLAGS = -O3 -s -pipe -Wall -fomit-frame-pointer -march=native \
	-I../array -w
FLAGS_O0 = -O0 -s -pipe -Wall -fomit-frame-pointer -march=native \
	-I../array -w
LIBRARY = ../array/array.a
EXECS = dgemm mm_row mm_col
all: ${EXECS}

dgemm: dgemm.c
	${CC} ${FLAGS} -c dgemm.c
	${CC} ${FLAGS} -o dgemm dgemm.o ${LIBRARY} -lblas

mm_row: mm_row.c
	${CC} ${FLAGS} -c mm_row.c
	${CC} ${FLAGS} -o mm_row mm_row.o ${LIBRARY} -lblas

mm_col: mm_col.c
	${CC} ${FLAGS} -c mm_col.c
	${CC} ${FLAGS} -o mm_col mm_col.o ${LIBRARY} -lblas

clean:
	(rm -f core)
	(rm -f *.o)
	(rm -f *~)
	(rm -f ${EXECS})