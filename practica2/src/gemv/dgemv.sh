#!/bin/bash
# Recolecta tiempos de ejecucion paralela para dgemv
# Uso: ./dgemv.sh > ../octave/dgemv.dat
M=16384
N=16384
ELEMENTS=1
VERBOSE=off

EXEC=./dgemv

> ../../octave/dgemv.dat

for p in 1 2 4 8 12; do
    OUTPUT=$($EXEC $M $N $ELEMENTS $VERBOSE $p 2>/dev/null | grep "^Data:")
    THREADS=$(echo $OUTPUT | awk '{print $2}')
    TIME=$(echo $OUTPUT   | awk '{print $3}')
    echo "$THREADS $TIME"  | tee -a ../../octave/dgemv.dat
done
