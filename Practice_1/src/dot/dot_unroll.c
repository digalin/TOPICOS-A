/**
@brief Sample program for dot product in C with loop unrolling
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

static int main_dot_unroll(const int n, const int elements_type,
                            const char* verbose);

int main
(
    int argc,
    char** argv
)
{
    fprintf(stdout, "dot_unroll: sample program for dot product in C with loop unrolling.\n");
    fputc('\n', stdout);
    if(argc != 4)
    {
        fprintf(stdout, "Use: dot_unroll <n:int> <0|1|2> <on|off>.\n");
        return EXIT_FAILURE;
    }
    main_dot_unroll(atoi(argv[1]), atoi(argv[2]), argv[3]);
    return EXIT_SUCCESS;
}

static int main_dot_unroll
(
    const int n,
    const int elements_type,
    const char* verbose
)
{
    double c0 = 0.0, c1 = 0.0, c2 = 0.0, c3 = 0.0;
    double* x = NULL;
    double* y = NULL;
    int i;
    int n4 = (n / 4) * 4;
    struct timeval start, finish;
    double runtime = 0.0;

    assert(n > 0);
    assert(elements_type >= ZEROS && elements_type <= RAND);
    x = array_new(n, 1, elements_type);
    assert(x != NULL);
    y = array_new(n, 1, elements_type);
    assert(y != NULL);

    gettimeofday(&start, NULL);
    /* unrolled loop: 4 iterations at a time */
    for(i = 0; i < n4; i += 4)
    {
        c0 += x[i]   * y[i];
        c1 += x[i+1] * y[i+1];
        c2 += x[i+2] * y[i+2];
        c3 += x[i+3] * y[i+3];
    }
    /* remainder loop */
    for(i = n4; i < n; i++)
        c0 += x[i] * y[i];
    gettimeofday(&finish, NULL);

    if(strcmp(verbose, "on") == 0)
    {
        array_show(n, 1, x, "x");
        array_show(n, 1, y, "y");
    }
    fprintf(stdout, "c = %lf\n", c0 + c1 + c2 + c3);
    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", n, runtime);
    free(x);
    free(y);
    return EXIT_SUCCESS;
}
