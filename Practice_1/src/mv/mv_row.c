/**
@brief Sample program for matrix-vector multiplication in C (row major)
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

static int main_mv_row(const int n);

int main
(
    int argc,
    char** argv
)
{
    fprintf(stdout, "mv_row: sample program for matrix-vector multiplication in C (row major).\n");
    fputc('\n', stdout);
    if(argc != 2)
    {
        fprintf(stdout, "Use: mv_row <n:int>.\n");
        return EXIT_FAILURE;
    }
    main_mv_row(atoi(argv[1]));
    return EXIT_SUCCESS;
}

static int main_mv_row(const int n)
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
    /* row major: inner loop traverses columns sequentially (cache-friendly) */
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            y[i] += A[i*n + j] * x[j];
    gettimeofday(&finish, NULL);

    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", n, runtime);
    free(A);
    free(x);
    free(y);
    return EXIT_SUCCESS;
}