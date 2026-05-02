#/**
# \file
# @brief Makefile for dgemm: sample program for cblas_dgemm function
# @author Julio Jos&eacute; &Aacute;guila Guerrero
# @date April 30th, 2021
# */
CC = gcc
FLAGS = -O3 -s -pipe -Wall -fomit-frame-pointer -march=native \
	-I../array -w
LIBRARY = ../array/array.a
EXEC = dgemm
all: ${EXEC}
${EXEC}: ${EXEC}.c
	${CC} ${FLAGS} -c ${EXEC}.c
	${CC} ${FLAGS} -o ${EXEC} ${EXEC}.o ${LIBRARY} -lblas
clean:
	(rm -f core)
	(rm -f *.o)
	(rm -f *~)
	(rm ${EXEC})