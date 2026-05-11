set term post eps enhanced color solid lw 1 size 9.0, 5.0 "Arial" 24
set output "../img/mm_c_cblas.eps"
set encoding iso_8859_1
set size 1.0, 1.0
set grid

set title "Algorithms for matrix-matrix product"
set xlabel "size ({/Ital n})"
set ylabel "time ({/Ital seconds})"
set xtics("2^{3}" 8, "2^{4}" 16, "2^{5}" 32, "2^{6}" 64, \
          "2^{7}" 128, "2^{8}" 256, "2^{9}" 512, \
          "2^{10}" 1024, "2^{11}" 2048, "2^{12}" 4096)
set key left 
set multiplot 
set size 1.0, 1.0

plot "../src/mm/dgemm.dat"  using 1:2 title "Cblas" with lines lw 2 lc rgb "blue", \
     "../src/mm/mm_row.dat" using 1:2 title "C Opt" with lines lw 2 lc rgb "red", \
     "../src/mm/mm_col.dat" using 1:2 title "C Base" with lines lw 2 lc rgb "green"
set size 1.0, 1.0 
set origin 0.0, 0.0
unset multiplot 
set output 
set terminal pop
