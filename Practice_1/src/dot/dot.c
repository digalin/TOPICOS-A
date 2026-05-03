/**
@brief Sample program for dot product in C
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

static int main_dot(const int n, const int elements_type,
                    const char* verbose);

int main
(
    int argc,
    char** argv
)
{
    fprintf(stdout, "dot: sample program for dot product in C.\n");
    fputc('\n', stdout);
    if(argc != 4)
    {
        fprintf(stdout, "Use: dot <n:int> <0|1|2> <on|off>.\n");
        return EXIT_FAILURE;
    }
    main_dot(atoi(argv[1]), atoi(argv[2]), argv[3]);
    return EXIT_SUCCESS;
}

static int main_dot
(
    const int n,
    const int elements_type,
    const char* verbose
)
{
    double c = 0.0;
    double* x = NULL;
    double* y = NULL;
    int i;
    struct timeval start, finish;
    double runtime = 0.0;

    assert(n > 0);
    assert(elements_type >= ZEROS && elements_type <= RAND);
    x = array_new(n, 1, elements_type);
    assert(x != NULL);
    y = array_new(n, 1, elements_type);
    assert(y != NULL);

    gettimeofday(&start, NULL);
    for(i = 0; i < n; i++)
        c += x[i] * y[i];
    gettimeofday(&finish, NULL);

    if(strcmp(verbose, "on") == 0)
    {
        array_show(n, 1, x, "x");
        array_show(n, 1, y, "y");
    }
    fprintf(stdout, "c = %lf\n", c);
    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", n, runtime);
    free(x);
    free(y);
    return EXIT_SUCCESS;
}
