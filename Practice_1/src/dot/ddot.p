set term post eps enhanced color solid lw 1 size 5.0, 3.5 "Arial" 24
set output "ddot.eps"
set title "cblas_ddot function" noenhanced
set xlabel "size ( {/Ital n})"
set ylabel "time ( {/Ital seconds})"
set grid
set key left
set xtics("2^{21}" 2097152, "2^{23}" 8388608, "2^{24}" 16777216, "2^{25}" 33554432, "2^{26}" 67108864)
plot "ddot.dat" using 1:2 title "runtime" with lines
