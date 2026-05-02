clear
reset
set terminal push
set size 1.0, 1.0
set term post eps enhanced color solid lw 1 size 10.0, 3.5 "Arial" 24
set output "../img/dot_octave.eps"
set encoding iso_8859_1
set grid 
set xlabel "size ({/Ital n})" 
set ylabel "time ({/Ital seconds})" 
set xtics("2^{21}" 2097152, "2^{22}" 4194304, "2^{23}" 8388608, \
          "2^{24}" 16777216, "2^{25}" 33554432, "2^{26}" 67108864)
set key left 
set multiplot 
set size 0.5, 1.0 
set origin 0.0, 0.0 
set title "(a)" 
plot "../octave/dot.dat" using 1:2 title "dot function" with lines 
set size 0.5, 1.0 
set origin 0.5, 0.0
unset multiplot 
set output 
set terminal pop
