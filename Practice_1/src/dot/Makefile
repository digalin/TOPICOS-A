#/**
# @brief Makefile for ddot: sample program for cblas_ddot function and other algorithms for the dot product of two vectors.
# @author Diego
# @date May 2nd, 2026
# */
CC = gcc
FLAGS = -O3 -s -pipe -Wall -fomit-frame-pointer -march=native \
	-I../array -w
LIBRARY = ../array/array.a
EXECS = ddot dot dot_unroll

all: ${EXECS}

ddot: ddot.c
	${CC} ${FLAGS} -c ddot.c
	${CC} ${FLAGS} -o ddot ddot.o ${LIBRARY} -lblas

dot: dot.c
	${CC} ${FLAGS} -c dot.c
	${CC} ${FLAGS} -o dot dot.o ${LIBRARY} -lblas

dot_unroll: dot_unroll.c
	${CC} ${FLAGS} -c dot_unroll.c
	${CC} ${FLAGS} -o dot_unroll dot_unroll.o ${LIBRARY} -lblas

clean:
	(rm -f core)
	(rm -f *.o)
	(rm -f *~)
	(rm -f ${EXECS})
