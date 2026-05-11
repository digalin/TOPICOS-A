/**
@brief Sample program for matrix-vector multiplication in C (column major)
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

static int main_mv_col(const int n);

int main
(
    int argc,
    char** argv
)
{
    fprintf(stdout, "mv_col: sample program for matrix-vector multiplication in C (column major).\n");
    fputc('\n', stdout);
    if(argc != 2)
    {
        fprintf(stdout, "Use: mv_col <n:int>.\n");
        return EXIT_FAILURE;
    }
    main_mv_col(atoi(argv[1]));
    return EXIT_SUCCESS;
}

static int main_mv_col(const int n)
{
    double* A = NULL;
    double* x = NULL;
    double* y = NULL;
    int i, j;
    struct timeval start, finish;
    double runtime = 0.0;

    assert(n > 0);
    A = array_new(n, n, ONES);
    assert(A != NULL);
    x = array_new(n, 1, ONES);
    assert(x != NULL);
    y = array_new(n, 1, ZEROS);
    assert(y != NULL);

    gettimeofday(&start, NULL);
    /* column-major semantics: access A so columns are contiguous in memory */
    for(j = 0; j < n; j++)
    {
        double xj = x[j];
        int base = j * n;
        for(i = 0; i < n; i++)
            y[i] += A[base + i] * xj;
    }
    gettimeofday(&finish, NULL);

    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", n, runtime);
    free(A);
    free(x);
    free(y);
    return EXIT_SUCCESS;
}