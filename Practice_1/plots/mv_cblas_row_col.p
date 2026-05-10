set term post eps enhanced color solid lw 1 size 8.0, 3.5 "Arial" 24
set output "../img/mv_c_cblas.eps"
set encoding iso_8859_1
set grid

set title "Algorithms for matrix-vector product"
set xlabel "size ({/Ital n})"
set ylabel "time ({/Ital seconds})"
set xtics("2^{10}" 1024, "2^{11}" 2048, "2^{12}" 4096, "2^{13}" 8192, "2^{14}" 16384, "2^{15}" 32768)
set key left 
set multiplot 
set size 1.0, 1.0
plot "../src/mv/dgemv.dat"  using 1:2 title "Cblas" with lines lw 2 lc rgb "blue", \
     "../src/mv/mv_row.dat" using 1:2 title "C row" with lines lw 2 lc rgb "red", \
     "../src/mv/mv_col.dat" using 1:2 title "C column" with lines lw 2 lc rgb "green"
set size 1.0, 1.0 
set origin 0.5, 0.0
unset multiplot 
set output 
set terminal pop
