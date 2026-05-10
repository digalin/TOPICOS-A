#/**
# \file
# @brief Makefile for dgemv: sample program for cblas_dgemv function and other algorithms for the matrix-vector product.
# @author Diego
# @date April 2nd, 2026
CC = gcc
FLAGS = -O3 -s -pipe -Wall -fomit-frame-pointer -march=native \
	-I../array -w
FLAGS_O0 = -O0 -s -pipe -Wall -fomit-frame-pointer -march=native \
	-I../array -w
LIBRARY = ../array/array.a
EXECS = dgemv mv_row mv_col

all: ${EXECS}

dgemv: dgemv.c
	${CC} ${FLAGS} -c dgemv.c
	${CC} ${FLAGS} -o dgemv dgemv.o ${LIBRARY} -lblas

mv_row: mv_row.c
	${CC} ${FLAGS} -c mv_row.c
	${CC} ${FLAGS} -o mv_row mv_row.o ${LIBRARY} -lblas

mv_col: mv_col.c
	${CC} ${FLAGS} -c mv_col.c
	${CC} ${FLAGS} -o mv_col mv_col.o ${LIBRARY} -lblas

clean:
	(rm -f core)
	(rm -f *.o)
	(rm -f *~)
	(rm -f ${EXECS})