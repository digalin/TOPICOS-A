#!/bin/bash
# Recolecta tiempos de ejecucion paralela para dgemm
# Uso: ./dgemm.sh > ../octave/dgemm.dat

M=8192
N=8192
K=8192
ELEMENTS=1
VERBOSE=off

EXEC=./dgemm

> ../../octave/dgemm.dat

for p in 1 2 4 8 12; do
    OUTPUT=$($EXEC $M $N $K $ELEMENTS $VERBOSE $p 2>/dev/null | grep "^Data:")
    THREADS=$(echo $OUTPUT | awk '{print $2}')
    TIME=$(echo $OUTPUT   | awk '{print $3}')
    echo "$THREADS $TIME"  | tee -a ../../octave/dgemm.dat
done
