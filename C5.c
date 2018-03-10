#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mkl.h>
#include "C5.h"
#include "C4.h"

double mkl_compute(
        double *W1, double *x1, double *z1, double *W2,
        double *z2, int dim1, int dim2, int dim3
        )
{
    int i;
    double checksum = 0;

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, dim2, 1, dim1, 1.0, W1, dim1, x1, 1, 0, z1, 1);
    for(i=0; i<dim2; i++)
    {
        z1[i] = z1[i] < 0 ? 0 : z1[i];
    }

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, dim3, 1, dim2, 1.0, W2, dim2, z1, 1, 0, z2, 1);

    for(i=0; i<dim3; i++)
    {
        checksum += z2[i] < 0 ? 0: z2[i];
    }
    return checksum;
}


int C5()
{
    int dim1 = 50176;
    int dim2 = 4000;
    int dim3 = 1000;
    double *W1, *x1, *W2, *z1, *z2, checksum;

    W1 = (double *)mkl_malloc(dim2*dim1*sizeof(double), 64);
    x1 = (double *)mkl_malloc(dim1*sizeof(double), 64);
    z1 = (double *)mkl_malloc(dim2*sizeof(double), 64);
    W2 = (double *)mkl_malloc(dim3*dim2*sizeof(double), 64);
    z2 = (double *)mkl_malloc(dim3*sizeof(double), 64);

    struct timespec start, end;

    init(W1, x1, W2, dim1, dim2, dim3);

    clock_gettime(CLOCK_MONOTONIC, &start);
    checksum = mkl_compute(W1, x1, z1, W2, z2, dim1, dim2, dim3);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_sec = (((double)end.tv_sec + (double)end.tv_nsec / 1000000000) - 
            ((double)start.tv_sec + (double)start.tv_nsec / 1000000000));

    printf("**************************************\n");
    printf("RUNNING PART C5: C mkl Calc of Network\n");
    printf("**************************************\n\n");
    printf("\tCHECKSUM %f\n", checksum);
    printf("\tElapsed Time (sec) %f\n\n", time_sec);
    return 0; 

}
