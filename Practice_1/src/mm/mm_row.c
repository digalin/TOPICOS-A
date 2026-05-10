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
#include <sys/time.h>

static int main_mm_row(const int n);

int main
(
    int argc,
    char** argv
)
{
    fprintf(stdout, "mm_row: sample program for matrix-matrix multiplication in C (row major).\n");
    fputc('\n', stdout);
    if(argc != 2)
    {
        fprintf(stdout, "Use: mm_row <n:int>.\n");
        return EXIT_FAILURE;
    }
    main_mm_row(atoi(argv[1]));
    return EXIT_SUCCESS;
}

static int main_mm_row(const int n)
{
    double* A = NULL;
    double* B = NULL;
    double* C = NULL;
    int i, j, k;
    struct timeval start, finish;
    double runtime = 0.0;

    assert(n > 0);
    A = array_new(n, n, ONES);
    assert(A != NULL);
    B = array_new(n, n, ONES);
    assert(B != NULL);
    C = array_new(n, n, ZEROS);
    assert(C != NULL);

    gettimeofday(&start, NULL);
    /* row major: inner loop traverses columns sequentially (cache-friendly) */
    for(i = 0; i < n; i++)
        for(k = 0; k < n; k++)
        {
            double r = A[i*n + k];
            for(j = 0; j < n; j++)
                C[i*n + j] += r * B[k*n + j];
        }
    gettimeofday(&finish, NULL);

    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", n, runtime);
    free(A);
    free(B);
    free(C);
    return EXIT_SUCCESS;
}
