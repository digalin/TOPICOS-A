/**
@brief Sample program for matrix-matrix multiplication in C (column major)
@author Diego
@date May 10th, 2026
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

static int main_mm_col(const int n);

int main
(
    int argc,
    char** argv
)
{
    fprintf(stdout, "mm_col: sample program for matrix-matrix multiplication in C (column major).\n");
    fputc('\n', stdout);
    if(argc != 2)
    {
        fprintf(stdout, "Use: mm_col <n:int>.\n");
        return EXIT_FAILURE;
    }
    main_mm_col(atoi(argv[1]));
    return EXIT_SUCCESS;
}

static int main_mm_col(const int n)
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
    /* Column-oriented access: k -> i -> j loop structure */
    for(k = 0; k < n; k++)
    {
        for(i = 0; i < n; i++)
        {
            double r = A[i*n + k];  /* Cache A[i][k] in register */
            for(j = 0; j < n; j++)
                C[i*n + j] += r * B[k*n + j];  /* Sequential access to B */
        }
    }
    gettimeofday(&finish, NULL);

    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", n, runtime);
    free(A);
    free(B);
    free(C);
    return EXIT_SUCCESS;
}
