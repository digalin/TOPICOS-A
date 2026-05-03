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
#include <string.h>
#include <sys/time.h>

static int main_mv_col(const int m, const int n, const int elements_type,
                       const char* verbose);

int main
(
    int argc,
    char** argv
)
{
    fprintf(stdout, "mv_col: sample program for matrix-vector multiplication in C (column major).\n");
    fputc('\n', stdout);
    if(argc != 5)
    {
        fprintf(stdout, "Use: mv_col <m:int> <n:int> <0|1|2> <on|off>.\n");
        return EXIT_FAILURE;
    }
    main_mv_col(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4]);
    return EXIT_SUCCESS;
}

static int main_mv_col
(
    const int m,
    const int n,
    const int elements_type,
    const char* verbose
)
{
    double* A = NULL;
    double* x = NULL;
    double* y = NULL;
    int i, j;
    struct timeval start, finish;
    double runtime = 0.0;

    assert(m > 0);
    assert(n > 0);
    assert(elements_type >= ZEROS && elements_type <= RAND);
    A = array_new(m, n, elements_type);
    assert(A != NULL);
    x = array_new(n, 1, elements_type);
    assert(x != NULL);
    y = array_new(m, 1, ZEROS);
    assert(y != NULL);

    gettimeofday(&start, NULL);
    /* column major: inner loop traverses rows */
    for(j = 0; j < n; j++)
        for(i = 0; i < m; i++)
            y[i] += A[i*n + j] * x[j];
    gettimeofday(&finish, NULL);

    if(strcmp(verbose, "on") == 0)
    {
        array_show(m, n, A, "A");
        array_show(n, 1, x, "x");
    }
    array_show(m, 1, y, "y");
    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", m, runtime);
    free(A);
    free(x);
    free(y);
    return EXIT_SUCCESS;
}
