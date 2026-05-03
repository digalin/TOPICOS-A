set term post eps enhanced color solid lw 1 size 5.0, 3.5 "Arial" 24
set output "../img/mm_c_cblas_1.png"
set encoding iso_8859_1
set grid

set title "Algorithms for matrix-matrix product"
set xlabel "size ({/Ital n})"
set ylabel "time ({/Ital seconds})"
set key left top
set logscale x 2
set logscale y
set format y "%.6g"
set xrange [8:4097]
set format y "%g"
set xtics("2^{3}" 8, "2^{4}" 16, "2^{5}" 32, "2^{6}" 64, \
          "2^{7}" 128, "2^{8}" 256, "2^{9}" 512, \
          "2^{10}" 1024, "2^{11}" 2048, "2^{12}" 4096)

set ytics ("0.000001" 0.000001, "0.00001" 0.00001, "0.0001" 0.0001, \
           "0.001" 0.001, "0.01" 0.01, "0.1" 0.1, \
           "1" 1, "10" 10, "100" 100, "1000" 1000, "10000" 10000)

plot "../src/mm/dgemm.dat"  using 1:2 title "Cblas" with lines lw 2 lc rgb "blue", \
     "../src/mm/mm_row.dat" using 1:2 title "C row" with lines lw 2 lc rgb "red", \
     "../src/mm/mm_col.dat" using 1:2 title "C column" with lines lw 2 lc rgb "pink"