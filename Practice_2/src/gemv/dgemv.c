/**
@brief Sample program for cblas_dgemv function with OpenMP
@author Diego Andrés Galindo Almonacid
@date July 2nd, 2026

Parallelization strategy:
  - Coverage:    Matrix allocation and the matrix-vector product are parallelized.
  - Granularity: Each thread handles a contiguous band of m_local rows (coarse-grain),
                 calling cblas_dgemv on its sub-matrix A[offset..offset+m_local-1][:].
  - Load balance: Remainder rows are assigned to the last thread.
                 Because row work is uniform (each row touches n elements),
                 static block decomposition achieves good balance.
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
 
static int main_dgemv(const int m, const int n, const int elements_type,
                      const char* verbose, const int threads);
 
int main
(
    int argc,
    char** argv
)
{
    fprintf(stdout, "dgemv: programa de ejemplo para cblas_dgemv con OpenMP.\n");
    fputc('\n', stdout);
 
    if(argc != 6)
    {
        fprintf(stdout, "Uso: dgemv <m:int> <n:int> <0|1|2> <on|off> <hilos:int>.\n");
        return EXIT_FAILURE;
    }
 
    main_dgemv(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4], atoi(argv[5]));
    return EXIT_SUCCESS;
}
 
static int main_dgemv
(
    const int m,
    const int n,
    const int elements_type,
    const char* verbose,
    const int threads
)
{
    double* A        = NULL;     /* matriz A de m x n                     */
    double* x        = NULL;     /* vector x de entrada (n elementos)     */
    double* y        = NULL;     /* vector y resultado  (m elementos)     */
    double  alpha    = 1.0;
    double  beta     = 0.0;
    int     lda      = n;        /* leading dimension de A (row-major)    */
    int     incx     = 1;
    int     incy     = 1;
    int*    m_local  = NULL;     /* número de filas por hilo              */
    int     t_id     = 0;        /* identificador del hilo                */
    long    offset   = 0L;       /* desplazamiento en filas de A e y      */
    int     i        = 0;
    struct timeval start, finish;
    double runtime   = 0.0;
 
    assert(m > 0);
    assert(n > 0);
    assert(elements_type >= ZEROS && elements_type <= RAND);
 
    /* Reserva e inicializa la matriz y los vectores */
    A = array_new(m, n, elements_type);
    assert(A != NULL);
    x = array_new(n, 1, elements_type);
    assert(x != NULL);
    y = array_new(m, 1, ZEROS);
    assert(y != NULL);
 
    /* Calcula el número de filas por hilo */
    m_local = (int*)calloc(threads, sizeof(int));
    assert(m_local != NULL);
    for(i = 0; i < threads; i++)
        m_local[i] = m / threads;
 
    /* El último hilo absorbe el resto de la división */
    m_local[threads - 1] += m % threads;
 
    omp_set_num_threads(threads);
 
    gettimeofday(&start, NULL);
 
    /* Cada hilo procesa su banda de filas: y[offset..offset+m_local-1] = A_sub * x */
    #pragma omp parallel private(t_id, offset)
    {
        t_id   = omp_get_thread_num();
        offset = (m / threads) * t_id;   /* desplazamiento en filas */
 
        cblas_dgemv(CblasRowMajor, CblasNoTrans,
                    m_local[t_id], n,
                    alpha,
                    A + offset * n, lda,  /* submatriz de m_local filas */
                    x, incx,
                    beta,
                    y + offset, incy);    /* segmento correspondiente de y */
    }
 
    gettimeofday(&finish, NULL);
 
    /* Muestra matrices y vectores si se solicita modo verbose */
    if(strcmp(verbose, "on") == 0)
    {
        array_show(m, n, A, "A");
        array_show(n, 1, x, "x");
        array_show(m, 1, y, "y");
    }
 
    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", threads, runtime);
 
    /* Libera memoria */
    free(m_local);
    free(A);
    free(x);
    free(y);
    return EXIT_SUCCESS;
}
