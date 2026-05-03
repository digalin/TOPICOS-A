#!/bin/bash
i=0
vals[0]=8
while [ $i -lt 9 ]
do
    valtmp=${vals[$(($i))]}
    newval=$(echo "$valtmp * 2" | bc)
    i=$(($i + 1))
    vals[$i]=$newval
done
unset LC_ALL
export LC_NUMERIC=C
echo "" > mm_row.dat
for val in "${vals[@]}"
do
    echo "" > data.dat
    for i in {1..7}
    do
        ./mm_row "${val}" "${val}" "${val}" 1 off | awk '/^Data/ { print $2 " " $3}' >> data.dat
        echo "${val} ${i} test finished"
    done
    cat data.dat | awk '{ n = $1; sum += $2 } END { if (NR>0) print n, sum/7; else print "", 0 }' >> mm_row.dat
done
cat mm_row.dat | awk '$0 != "" {print $0}'