#!/bin/bash
i=0
vals[0]=2097152
while [ $i -lt 5 ]
do
    valtmp=${vals[$(($i))]}
    newval=$(echo "$valtmp * 2" | bc)
    i=$(($i + 1))
    vals[$i]=$newval
done
unset LC_ALL
export LC_NUMERIC=C
echo "" > dot_unroll.dat
for val in "${vals[@]}"
do
    echo "" > data.dat
    for i in {1..7}
    do
        ./dot_unroll "${val}" 1 off | awk '/^Data/ { print $2 " " $3}' >> du_data.dat
        echo "${val} ${i} test finished"
    done
    cat du_data.dat | awk '{n = $1; sum += $2}; END{print n, sum/7}' >> dot_unroll.dat
done
cat dot_unroll.dat | awk '$0 != "" {print $0}'
gnuplot < dot_unroll.p
