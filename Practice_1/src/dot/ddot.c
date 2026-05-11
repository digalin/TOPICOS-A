/**
@brief Sample program for cblas_ddot function
@author Julio Jos&eacute; &Aacute;guila Guerrero
@date March 24th, 2022
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
static int main_ddot(const int n);
int main
(
int argc,
char** argv
)
{
    fprintf(stdout, "ddot: sample program for cblas_ddot function.\n");
    fputc('\n', stdout);
    if(argc != 2)
    {
        fprintf(stdout, "Use: ddot <n:int>.\n");
        return EXIT_FAILURE;
    }
    main_ddot(atoi(argv[1]));
    return EXIT_SUCCESS;
}
static int main_ddot
(
const int n
)
{
    double c = 0.0;
    double* x = NULL;
    double* y = NULL;
    int incx = 1;
    int incy = 1;
    struct timeval start, finish;
    double runtime = 0.0;
    assert(n > 0);
    x = array_new(n, 1, ONES);
    assert(x != NULL);
    y = array_new(n, 1, ONES);
    assert(y != NULL);
    gettimeofday(&start, NULL);
    c = cblas_ddot(n, x, incx, y, incy);
    gettimeofday(&finish, NULL);
    fprintf(stdout, "c = %lf\n", c);
    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", n, runtime);
    free(x);
    free(y);
    return EXIT_SUCCESS;
}
