/**
@brief Sample program for cblas_dgemm function with OpenMP
@author Diego Andrés Galindo Almonacid
@date July 2nd, 2026

Parallelization strategy:
  - Coverage:    Matrix allocation (parallel sections) and the matrix product
                 are parallelized — maximizing the fraction F in Amdahl's law.
  - Granularity: Each thread handles a contiguous band of m_local rows of C
                 (coarse-grain), invoking one cblas_dgemm call per thread.
                 This avoids fine-grain loop overhead described in Chapter 8.
  - Load balance: Remainder rows go to the last thread. Row work is uniform
                 (each row of A multiplied by the full B matrix), so static
                 block assignment achieves balanced load.
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
 
static int main_dgemm(const int m, const int n, const int k,
                      const int elements_type, const char* verbose,
                      const int threads);
 
int main
(
    int argc,
    char** argv
)
{
    fprintf(stdout, "dgemm: programa de ejemplo para cblas_dgemm con OpenMP.\n");
    fputc('\n', stdout);
 
    if(argc != 7)
    {
        fprintf(stdout, "Uso: dgemm <m:int> <n:int> <k:int> <0|1|2> <on|off> <hilos:int>.\n");
        return EXIT_FAILURE;
    }
 
    main_dgemm(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]),
               atoi(argv[4]), argv[5], atoi(argv[6]));
    return EXIT_SUCCESS;
}
 
static int main_dgemm
(
    const int m,
    const int n,
    const int k,
    const int elements_type,
    const char* verbose,
    const int threads
)
{
    double* A        = NULL;     /* matriz A de m x k                     */
    double* B        = NULL;     /* matriz B de k x n (compartida)        */
    double* C        = NULL;     /* matriz resultado C de m x n           */
    double  alpha    = 1.0;
    double  beta     = 0.0;
    int     lda      = k;        /* leading dimension de A                */
    int     ldb      = n;        /* leading dimension de B                */
    int     ldc      = n;        /* leading dimension de C                */
    int*    m_local  = NULL;     /* número de filas por hilo              */
    int     t_id     = 0;        /* identificador del hilo                */
    long    offset   = 0L;       /* desplazamiento en filas de A y C      */
    int     i        = 0;
    struct timeval start, finish;
    double runtime   = 0.0;
 
    assert(m > 0);
    assert(n > 0);
    assert(k > 0);
    assert(elements_type >= ZEROS && elements_type <= RAND);
 
    /* Asignación paralela de A, B y C para aumentar la cobertura */
    #pragma omp parallel sections num_threads(3)
    {
        #pragma omp section
        {
            A = array_new(m, k, elements_type);
        }
        #pragma omp section
        {
            B = array_new(k, n, elements_type);
        }
        #pragma omp section
        {
            C = array_new(m, n, ZEROS);
        }
    }
    assert(A != NULL);
    assert(B != NULL);
    assert(C != NULL);
 
    /* Calcula el número de filas por hilo para A y C */
    m_local = (int*)calloc(threads, sizeof(int));
    assert(m_local != NULL);
    for(i = 0; i < threads; i++)
        m_local[i] = m / threads;
 
    /* El último hilo absorbe el resto de la división */
    m_local[threads - 1] += m % threads;
 
    omp_set_num_threads(threads);
 
    gettimeofday(&start, NULL);
 
    /* Cada hilo calcula su submatriz: C_sub = A_sub * B
     * B es compartida en modo solo lectura (sin condición de carrera) */
    #pragma omp parallel private(t_id, offset)
    {
        t_id   = omp_get_thread_num();
        offset = (m / threads) * t_id;   /* desplazamiento en filas */
 
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                    m_local[t_id], n, k,
                    alpha,
                    A + offset * k, lda,  /* submatriz A_sub de m_local filas */
                    B, ldb,               /* B completa, solo lectura          */
                    beta,
                    C + offset * n, ldc); /* segmento correspondiente de C     */
    }
 
    gettimeofday(&finish, NULL);
 
    /* Muestra matrices si se solicita modo verbose */
    if(strcmp(verbose, "on") == 0)
    {
        array_show(m, k, A, "A");
        array_show(k, n, B, "B");
        array_show(m, n, C, "C");
    }
 
    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", threads, runtime);
 
    /* Liberación paralela de memoria (simetría con la asignación) */
    #pragma omp parallel sections num_threads(3)
    {
        #pragma omp section
        free(A);
        #pragma omp section
        free(B);
        #pragma omp section
        free(C);
    }
    free(m_local);
    return EXIT_SUCCESS;
}
