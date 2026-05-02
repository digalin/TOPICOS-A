set term post eps enhanced color solid lw 1 size 5.0, 3.5 "Arial" 24
set output "../../img/dgemv.eps"
set title "cblas_mv function" noenhanced
set xlabel "size ( {/Ital n})"
set ylabel "time ( {/Ital seconds})"
set grid
set key left
set xtics("2^{10}" 1024, "2^{11}" 2048, "2^{12}" 4096, "2^{13}" 8192, "2^{14}" 16384)
plot "dgemv.dat" using 1:2 title "dgemv runtime" with lines
