set term post eps enhanced color solid lw 1 size 5.0, 3.5 "Arial" 24
set output "../img/dot_octave_cblas.eps"
set encoding iso_8859_1
set grid

set title "Octave operator vs cblas\\_ddot function"
set xlabel "size ({/Ital n})"
set ylabel "time ({/Ital seconds})"
set key left top
set logscale x 2
set xrange [2097152:67108865]

set xtics("2^{21}" 2097152, "2^{22}" 4194304, "2^{23}" 8388608, "2^{24}" 16777216, "2^{25}" 33554432, "2^{26}" 67108864)

plot "../octave/dot.dat" using 1:2 title "Cblas" with lines lw 2 lc rgb "red", \
     "../src/dot/ddot.dat"  using 1:2 title "Octave" with lines lw 2 lc rgb "blue"
