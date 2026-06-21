#!/bin/bash
# Recolecta tiempos de ejecucion paralela para ddot
# Uso: ./ddot.sh > ../octave/ddot.dat
N=100000000
ELEMENTS=1   # 1 = ONES (deterministic, fast to init)
VERBOSE=off

EXEC=./ddot

> ../../octave/ddot.dat

for p in 1 2 4 8 12; do
    # Run 3 times and take median (simple: just run once here)
    OUTPUT=$($EXEC $N $ELEMENTS $VERBOSE $p 2>/dev/null | grep "^Data:")
    THREADS=$(echo $OUTPUT | awk '{print $2}')
    TIME=$(echo $OUTPUT   | awk '{print $3}')
    echo "$THREADS $TIME"  | tee -a ../../octave/ddot.dat
done
