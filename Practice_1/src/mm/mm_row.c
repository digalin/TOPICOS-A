/**
@brief Sample program for matrix-matrix multiplication in C (row major)
@author Diego
@date May 2nd, 2026
*/
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef ARRAY_H
#include "array.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>

static int main_mm_row(const int m, const int n, const int k,
                       const int elements_type, const char* verbose);

int main
(
    int argc,
    char** argv
)
{
    fprintf(stdout, "mm_row: sample program for matrix-matrix multiplication in C (row major).\n");
    fputc('\n', stdout);
    if(argc != 6)
    {
        fprintf(stdout, "Use: mm_row <m:int> <n:int> <k:int> <0|1|2> <on|off>.\n");
        return EXIT_FAILURE;
    }
    main_mm_row(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]),
                atoi(argv[4]), argv[5]);
    return EXIT_SUCCESS;
}

static int main_mm_row
(
    const int m,
    const int n,
    const int k,
    const int elements_type,
    const char* verbose
)
{
    double* A = NULL;
    double* B = NULL;
    double* C = NULL;
    int i, j, l;
    struct timeval start, finish;
    double runtime = 0.0;

    assert(m > 0);
    assert(n > 0);
    assert(k > 0);
    assert(elements_type >= ZEROS && elements_type <= RAND);
    A = array_new(m, k, elements_type);
    assert(A != NULL);
    B = array_new(k, n, elements_type);
    assert(B != NULL);
    C = array_new(m, n, ZEROS);
    assert(C != NULL);

    gettimeofday(&start, NULL);
    /* row major: i -> j -> k, inner loop accesses B by columns */
    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++)
            for(l = 0; l < k; l++)
                C[i*n + j] += A[i*k + l] * B[l*n + j];
    gettimeofday(&finish, NULL);

    if(strcmp(verbose, "on") == 0)
    {
        array_show(m, k, A, "A");
        array_show(k, n, B, "B");
    }
    array_show(m, n, C, "C");
    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", m, runtime);
    free(A);
    free(B);
    free(C);
    return EXIT_SUCCESS;
}
