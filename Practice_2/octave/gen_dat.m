## gen_dat.m  —  Genera archivos .dat para gnuplot (Práctica 2)
## Uso: octave gen_dat.m
##
## Lee: ddot.dat  dgemv.dat  dgemm.dat   (columnas: p  Tp)
## Escribe por función:
##   Tp_<func>.dat   columnas: idx  p  Tp_real  Tp_ideal
##   S_<func>.dat    columnas: idx  p  S_real   S_ideal
##   E_<func>.dat    columnas: idx  p  E_real   E_ideal
##   SC_<func>.dat   columnas: idx  p  SC_real  SC_ideal   (desde p=2)

close all; clear;

function write_dat(fname, idx, p_labels, col_real, col_ideal)
    fid = fopen(fname, 'w');
    for i = 1:length(idx)
        fprintf(fid, '%d\t%d\t%.6f\t%.6f\n', idx(i), p_labels(i), col_real(i), col_ideal(i));
    endfor
    fclose(fid);
    printf("  -> %s\n", fname);
endfunction

function process(raw, fname)
    p   = raw(:,1);
    Tp  = raw(:,2);
    N   = length(p);
    idx = (1:N)';

    ## Ideal Tp: Ts/p
    Tp_ideal = Tp(1) ./ p;

    ## Speed-up
    S_real  = Tp(1) ./ Tp;
    S_ideal = p;              % S = p (lineal)

    ## Efficiency
    E_real  = S_real  ./ p * 100;
    E_ideal = ones(N,1) * 100;

    ## Scalability (desde p=2, i.e. fila 2 en adelante)
    Tp2  = [0; Tp(1:end-1)];
    _2Tp = 2 .* Tp;
    SC_real  = Tp2 ./ _2Tp;        % SC(1) = 0 → se excluye
    SC_ideal = ones(N,1);

    ## Print tabla de resumen
    printf("\n=== %s ===\n", fname);
    printf("  p     Tp         S       E(%%)    SC(%%)\n");
    for i = 1:N
        printf("  %-3d  %.6f  %6.3f  %6.2f  %6.2f\n",
               p(i), Tp(i), S_real(i), E_real(i), SC_real(i)*100);
    endfor

    ## Tp .dat
    write_dat(['Tp_' fname '.dat'], idx, p, Tp, Tp_ideal);

    ## S .dat
    write_dat(['S_' fname '.dat'], idx, p, S_real, S_ideal);

    ## E .dat
    write_dat(['E_' fname '.dat'], idx, p, E_real, E_ideal);

    ## SC .dat  — desde fila 2
    idx2 = idx(2:end);
    p2   = p(2:end);
    write_dat(['SC_' fname '.dat'], idx2, p2, SC_real(2:end)*100, SC_ideal(2:end)*100);
endfunction

process(load("ddot.dat"),  "ddot");
process(load("dgemv.dat"), "dgemv");
process(load("dgemm.dat"), "dgemm");

printf("\nListo. Ejecuta: cd ../plot && gnuplot metrics_ddot.gp  metrics_dgemv.gp  metrics_dgemm.gp\n");
