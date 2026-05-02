clear
reset
set terminal push
set size 1.0, 1.0
set term post eps enhanced color solid lw 1 size 10.0, 3.5 "Arial" 24
set output "../img/mm_octave.eps"
set encoding iso_8859_1
set grid 
set xlabel "size ({/Ital n})" 
set ylabel "time ({/Ital seconds})" 
set xtics("2^{8}" 256, "2^{9}" 512, "2^{10}" 1024, \
          "2^{11}" 2048, "2^{12}" 4096, "2^{13}" 8192)
set key left 
set multiplot 
set size 0.5, 1.0 
set origin 0.0, 0.0 
set title "(a)" 
plot "../octave/mm.dat" using 1:2 title "mm function" with lines 
set size 0.5, 1.0 
set origin 0.5, 0.0
unset multiplot 
set output 
set terminal pop
