################# metrics_dgemm.gp — Práctica 2 OpenMP
clear
reset
###################
# Prolog terminal
###################
set terminal push
set size 1.0, 1.0
set term post eps enhanced color solid lw 1 size 10.0, 7.0 "Helvetica" 24
set grid
set encoding iso_8859_1
set output "../img/Metrics_dgemm.eps"
###################
# Prolog multiplot
###################
set size 1.0, 1.0
set origin 0.0, 0.0
set multiplot
###############
# (a) Tiempo de ejecución
###############
set size 0.5,0.5
set origin 0.0,0.5
set title "Tiempo de ejecuci{/E \363}n dgemm"
set key right top
set xlabel "{/Ital p} (n{/E \372}mero de hilos OpenMP)"
set ylabel "{/Ital T_p} (segundos)"

set autoscale y
plot "../octave/Tp_dgemm.dat" using 1:3:xtic(2) title 'real'  with linespoints lw 2 pt 7, \
     "../octave/Tp_dgemm.dat" using 1:4:xtic(2) title 'ideal' with linespoints lw 2 dt 2 pt 0
#########
# (b) Speed-up
#########
set size 0.5,0.5
set origin 0.5,0.5
set title "Speed-up dgemm"
set key left top
set xlabel "{/Ital p} (n{/E \372}mero de hilos OpenMP)"
set ylabel "{/Ital S} = {/Ital T_s} / {/Ital T_p}"
set autoscale y
plot "../octave/S_dgemm.dat" using 1:3:xtic(2) title 'real'  with linespoints lw 2 pt 7, \
     "../octave/S_dgemm.dat" using 1:4:xtic(2) title 'ideal' with linespoints lw 2 dt 2 pt 0
###########
# (c) Eficiencia
###########
set size 0.5,0.5
set origin 0.0,0.0
set title "Eficiencia dgemm"
set key right top
set xlabel "{/Ital p} (n{/E \372}mero de hilos OpenMP)"
set ylabel "{/Ital E} = ({/Ital S} / {/Ital p}) {/Symbol \264} 100 (%)"
set yrange [0:120]
set ytic 0,20,120
plot "../octave/E_dgemm.dat" using 1:3:xtic(2) title 'real'  with linespoints lw 2 pt 7, \
     "../octave/E_dgemm.dat" using 1:4:xtic(2) title 'ideal' with linespoints lw 2 dt 2 pt 0
###########
# (d) Escalabilidad
###########
set size 0.5,0.5
set origin 0.5,0.0
set title "Escalabilidad dgemm"
set key bottom left
set xlabel "{/Ital p} (n{/E \372}mero de hilos OpenMP)"
set ylabel "{/Ital SC} = ({/Ital T_{p/2}} / (2 {/Ital T_p})) {/Symbol \264} 100 (%)"
set yrange [0:120]
set ytic 0,20,120
plot "../octave/SC_dgemm.dat" using 1:3:xtic(2) title 'real'  with linespoints lw 2 pt 7, \
     "../octave/SC_dgemm.dat" using 1:4:xtic(2) title 'ideal' with linespoints lw 2 dt 2 pt 0
####################
# Epilog multiplot
####################
unset multiplot
####################
# Epilog terminal
####################
set output
set terminal pop
