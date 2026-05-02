set term post eps enhanced color solid lw 1 size 5.0, 3.5 "Arial" 24
set output "dgemm.eps"
set title "cblas_dgemm function" noenhanced
set xlabel "size ( {/Ital n})"
set ylabel "time ( {/Ital seconds})"
set key left
set grid
set xtics("2^{3}" 8, "2^{8}" 256, "2^{9}" 512, "2^{10}" 1024, "2^{11}" 2048,
"2^{12}" 4096)
plot "../src/mm/dgemm.dat" using 1:2 title "runtime" with lines