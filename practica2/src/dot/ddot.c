/**
@brief Sample program for cblas_ddot function with OpenMP
@author Diego Andrés Galindo Almonacid
@date July 2nd, 2026

Parallelization strategy:
  - Coverage:    Both vector initialization and the dot product are parallelized.
  - Granularity: Each thread operates on a contiguous block of n/threads elements
                 (coarse-grain approach) to minimize parallel-region overhead.
  - Load balance: If n is not divisible by threads, the last thread absorbs
                 the remainder (at most threads-1 extra elements).
*/
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef ARRAY_H
#include "array.h"
#endif
#include <cblas.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>
 
static int main_ddot(const long n, const int elements_type,
                     const char* verbose, const int threads);
 
int main
(
    int argc,
    char** argv
)
{
    fprintf(stdout, "ddot: programa de ejemplo para cblas_ddot con OpenMP.\n");
    fputc('\n', stdout);
 
    if(argc != 5)
    {
        fprintf(stdout, "Uso: ddot <n:long> <0|1|2> <on|off> <hilos:int>.\n");
        return EXIT_FAILURE;
    }
 
    main_ddot(atol(argv[1]), atoi(argv[2]), argv[3], atoi(argv[4]));
    return EXIT_SUCCESS;
}
 
static int main_ddot
(
    const long n,
    const int elements_type,
    const char* verbose,
    const int threads
)
{
    double  c        = 0.0;      /* resultado final (suma de parciales)   */
    double* x        = NULL;     /* vector x de entrada                   */
    double* y        = NULL;     /* vector y de entrada                   */
    double* c_local  = NULL;     /* resultados parciales por hilo         */
    long*   n_local  = NULL;     /* tamaño de bloque por hilo             */
    int     incx     = 1;
    int     incy     = 1;
    int     t_id     = 0;        /* identificador del hilo                */
    long    offset   = 0L;       /* desplazamiento en el arreglo          */
    int     i        = 0;
    struct timeval start, finish;
    double runtime   = 0.0;
 
    assert(n > 0);
    assert(elements_type >= ZEROS && elements_type <= RAND);
 
    /* Reserva e inicializa los vectores de entrada */
    x = array_new(n, 1, elements_type);
    assert(x != NULL);
    y = array_new(n, 1, elements_type);
    assert(y != NULL);
 
    /* Reserva arreglos de resultados parciales y tamaños de bloque */
    c_local = (double*)calloc(threads, sizeof(double));
    n_local = (long*)calloc(threads, sizeof(long));
    assert(c_local != NULL);
    assert(n_local != NULL);
 
    /* Distribuye los elementos en bloques iguales */
    for(i = 0; i < threads; i++)
        n_local[i] = n / threads;
 
    /* El último hilo absorbe el resto de la división */
    n_local[threads - 1] += n % threads;
 
    omp_set_num_threads(threads);
 
    gettimeofday(&start, NULL);
 
    /* Cada hilo calcula su producto punto parcial (grano grueso) */
    #pragma omp parallel private(t_id, offset)
    {
        t_id   = omp_get_thread_num();
        offset = (n / threads) * t_id;
 
        c_local[t_id] = cblas_ddot(n_local[t_id],
                                   x + offset, incx,
                                   y + offset, incy);
    }
 
    /* Reducción serial: suma los resultados parciales de cada hilo */
    for(i = 0; i < threads; i++)
        c += c_local[i];
 
    gettimeofday(&finish, NULL);
 
    /* Muestra los vectores si se solicita modo verbose */
    if(strcmp(verbose, "on") == 0)
    {
        array_show(n, 1, x, "x");
        array_show(n, 1, y, "y");
    }
 
    fprintf(stdout, "c = %lf\n", c);
    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", threads, runtime);
 
    /* Libera memoria */
    free(c_local);
    free(n_local);
    free(x);
    free(y);
    return EXIT_SUCCESS;
}
