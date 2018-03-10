#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include "C1.h"

void shuffle(int *indices, size_t n)
{
  size_t i;
  for (i = 0; i < n - 1; i++)
  {
    size_t j = 1 + rand() / (RAND_MAX / (n-1) + 1);
    int t = indices[j];
    indices[j] = indices[i];
    indices[i] = t;
  }
}

void allocate(int *indices, double *array, int N)
{
  int i;
  for (i=0; i < N; i++)
  {
    indices[i] = i;
    array[i] = (double)i;
  }
}

void print_arrays(int *indices, double *array, int N)
{
  int i;
  for (i=0; i < N; i++)
  {
    printf("%u : %f\n", indices[i], array[i]);
  }
}

void seq_bandwidth(double *array, int N)
{
  /* Benchmark array sum for sequential access. 
   * Requres 3 arithmetic operations and 2 double precision memory operations.
   * AI = 3 / (8*2) = .1875.
   */
  int N_half = N/2;
  long total_bytes = N_half * 16;
  int i, itr;
  double sum;
  double best_elapsed = DBL_MAX;
  double best_bandwidth = DBL_MAX;
  struct timespec start, end;
  for (itr=0; itr<16; itr++)
  {
    sum = 0;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i=0; i < N_half; i++)
    {	  
        sum += array[i] + array[i+N_half];
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_sec = (((double)end.tv_sec + (double)end.tv_nsec / 1000000000) - 
            ((double)start.tv_sec + (double)start.tv_nsec / 1000000000));
    double estimated_bandwidth = total_bytes / time_sec;

    if (time_sec < best_elapsed)
    {
        best_elapsed = time_sec;
        best_bandwidth = estimated_bandwidth;
    }
  }

  printf("\tSEQUENTIAL ACCESS BEST OF 16 TRIALS\n");
  printf("\t\tSUM %f\n", sum);
  printf("\t\telapsed_time %f\n", best_elapsed);
  printf("\t\testimated_bandwidth %liB/s\n\n", (long)best_bandwidth);
}

void rnd_bandwidth(int* indices, double *array, int N)
{
  /* Benchmark array sum for random access. 
   * Requres 3 arithmetic operations and 4 memory operations: 2 ints and 2 doubles.
   * AI = 3 / (4*2 + 8*2) = .125
   */
  int N_half = N/2;
  long total_bytes = N_half * 24;
  int i, itr;
  double sum;
  double best_elapsed = DBL_MAX;
  double best_bandwidth = DBL_MAX;
  struct timespec start, end;
  for (itr=0; itr<16; itr++)
  {
    sum = 0;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i=0; i < N_half; i++)
    {	  
      sum += array[indices[i]] + array[indices[i+N_half]];
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_sec = (((double)end.tv_sec + (double)end.tv_nsec / 1000000000) - 
            ((double)start.tv_sec + (double)start.tv_nsec / 1000000000));
    double estimated_bandwidth = total_bytes / time_sec;

    if (time_sec < best_elapsed)
    {
        best_elapsed = time_sec;
        best_bandwidth = estimated_bandwidth;
    }
  }

  printf("\tRANDOM ACCESS BEST OF 16 TRIALS\n");
  printf("\t\tSUM %f\n", sum);
  printf("\t\telapsed_time %f\n", best_elapsed);
  printf("\t\testimated_bandwidth %liB/s\n\n", (long)best_bandwidth);
}

int C1()
{
  int N = 100000000; // size of array
  int *indices;
  double *array;

  indices = malloc(N * sizeof(int));
  array = malloc(N * sizeof(double));

  printf("****************************************************\n");
  printf("RUNNING PART C1: C Bandwidth Array of Size %d\n", N);
  printf("****************************************************\n\n");
  allocate(indices, array, N);
  seq_bandwidth(array, N);
  shuffle(indices, N);
  rnd_bandwidth(indices, array, N);

  free(indices);
  free(array);
  return(0);
}
