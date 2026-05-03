set term post eps enhanced color solid lw 1 size 5.0, 3.5 "Arial" 24
set output "../img/mm_octave_cblas.png"
set encoding iso_8859_1
set grid

set title "Octave operator vs cblas\\_dgemm function"
set xlabel "size ({/Ital n})"
set ylabel "time ({/Ital seconds})"
set key left top
set logscale x 2
set xrange [8:4097]
set xtics("2^{3}" 8, "2^{4}" 16, "2^{5}" 32, "2^{6}" 64, \
          "2^{7}" 128, "2^{8}" 256, "2^{9}" 512, \
          "2^{10}" 1024, "2^{11}" 2048, "2^{12}" 4096)

plot "../octave/mm.dat" using 1:2 title "Octave" with lines lw 2 lc rgb "red", \
     "../src/mm/dgemm.dat"  using 1:2 title "Cblas" with lines lw 2 lc rgb "blue"
