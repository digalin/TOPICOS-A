/**
@brief Sample program for cblas_dgemv function
@author Julio Jos&eacute; &Aacute;guila Guerrero
@date April 27th, 2021
*/
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef ARRAY_H
#include "array.h"
#endif
#include <cblas.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>
static int main_dgemv(const int m, const int n);
int main
(
    int argc,
    char** argv
)
{
    fprintf(stdout, "dgemv: sample program for cblas_dgemv function.\n");
    fputc('\n', stdout);
    if(argc != 3)
    {
        fprintf(stdout, "Use: dgemv <m:int> <n:int>.\n");
        return EXIT_FAILURE;
    }
    main_dgemv(atoi( argv[ 1]), atoi( argv[ 2]));
    
    return EXIT_SUCCESS;
}
static int main_dgemv
(
    const int m,
    const int n
)
{
    double* A = NULL;
    double* x = NULL;
    double* y = NULL;
    double alpha = 1.0;
    double beta = 0.0;
    int lda = n;
    int incx = 1;
    int incy = 1;
    struct timeval start, finish;
    double runtime = 0.0; // seconds.

    assert(m > 0);
    assert(n > 0);
    A = array_new(m, n, ONES);
    assert(A != NULL);
    x = array_new(n, 1, ONES);
    assert(x != NULL);
    y = array_new(m, 1, ZEROS);
    assert(y != NULL);
    gettimeofday(&start, NULL);
    cblas_dgemv(CblasRowMajor, CblasNoTrans, m, n, alpha, A, lda,
    x, incx, beta, y, incy);
    gettimeofday(&finish, NULL);
    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", m, runtime);
    free(A);
    free(x);
    free(y);

    return EXIT_SUCCESS;
}
