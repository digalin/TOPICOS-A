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
echo "" > dot.dat
for val in "${vals[@]}"
do
    echo "" > data.dat
    for i in {1..7}
    do
        ./dot "${val}" | awk '/^Data/ { print $2 " " $3}' >> data.dat
        echo "${val} ${i} test finished"
    done
    cat data.dat | awk '{n = $1; sum += $2}; END{print n, sum/7}' >> dot.dat
done
cat dot.dat | awk '$0 != "" {print $0}'
