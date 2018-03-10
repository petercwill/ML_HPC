#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "C4.h"

double f(int i, int j)
{
    return (.5 +(double)((i+j)%50 - 30)/50);
}

void init(double *W1, double *x1, double *W2, int dim1, int dim2, int dim3)
{
    int i,j;
    for(j=0; j<dim1; j++)
    {
        x1[j] = f(j,0);
        for(i=0; i<dim2; i++)
        {
            W1[j+(i*dim1)] = f(i,j);
        }
    }

    for(j=0; j<dim2; j++)
    {
        for(i=0; i<dim3; i++)
        {
            W2[j+(i*dim2)] = f(i,j);
        }
    }

}

double loop_compute(
        double *W1, double *x1, double *z1, double *W2,
        double *z2, int dim1, int dim2, int dim3
        )
{
    int i,j;
    double tot;
    double checksum = 0.0;
    for(i=0; i<dim2; i++)
    {
        tot = 0;
        for(j=0; j<dim1; j++)
        {
            tot += W1[j+(i*dim1)]*x1[j];
        }
        z1[i] = tot > 0 ? tot : 0;
    }

    for(i=0; i<dim3; i++)
    {
        tot = 0;
        for(j=0; j<dim2; j++)
        {
            tot += W2[j+(i*dim2)]*z1[j];
        }
        z2[i] = tot > 0 ? tot : 0;

    }

    for(j=0; j<dim3; j++)
    {
        checksum += z2[j];
    }
    return checksum;
}


int C4()
{
    int dim1 = 50176;
    int dim2 = 4000;
    int dim3 = 1000;
    double *W1, *x1, *W2, *z1, *z2, checksum;

    W1 = malloc(dim2*dim1*sizeof(double));
    x1 = malloc(dim1*sizeof(double));
    z1 = malloc(dim2*sizeof(double));
    W2 = malloc(dim3*dim2*sizeof(double));
    z2 = malloc(dim3*sizeof(double));

    struct timespec start, end;

    init(W1, x1, W2, dim1, dim2, dim3);

    clock_gettime(CLOCK_MONOTONIC, &start);
    checksum = loop_compute(W1, x1, z1, W2, z2, dim1, dim2, dim3);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_sec = (((double)end.tv_sec + (double)end.tv_nsec / 1000000000) - 
            ((double)start.tv_sec + (double)start.tv_nsec / 1000000000));

    printf("*********************************************\n");
    printf("RUNNING PART C4: C Iterative Calc. of Network\n");
    printf("*********************************************\n\n");
    printf("\tCHECKSUM %f\n", checksum);
    printf("\tElapsed Time (sec) %f\n\n", time_sec);
    free(W1);
    free(x1);
    free(z1);
    free(W2);
    free(z2);
    return 0; 

}
