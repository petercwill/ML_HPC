#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

void allocate(int *indices, double *array, unsigned int N)
{
  int i;
  for (i=0; i < N; i++)
  {
    indices[i] = i;
    array[i] = (double)i;
  }
}

void print_arrays(int *indices, double *array, unsigned int N)
{
  int i;
  for (i=0; i < N; i++)
  {
    printf("%u : %f\n", indices[i], array[i]);
  }
}

void seq_bandwidth(double *array, unsigned int N)
{
  /* Benchmark array sum for sequential access. 
   * Requres 3 arithmetic operations and 3 double precision memory operations.
   * AI = 3 / (8*3) = .125
   */
  unsigned int N_half = N/2;
  long total_bytes = N_half * 24;
  double sum = 0;
  clock_t start = clock();
  for (int i=0; i < N_half; i++)
  {	  
      sum += array[i] + array[i+N_half];
  }
  clock_t end = clock();

  double elapsed = (double)(end-start) / CLOCKS_PER_SEC;
  double estimated_bandwidth = total_bytes / elapsed;
  printf("****SEQUENTIAL****\n");
  printf("SUM %f\n", sum);
  printf("elapsed_time %f\n", elapsed);
  printf("estimated_bandwidth %liB/s\n", (long)estimated_bandwidth);
}

void rnd_bandwidth(int* indices, double *array, unsigned int N)
{
  /* Benchmark array sum for random access. 
   * Requres 3 arithmetic operations and 5 memory operations: 2 ints and 3 doubles.
   * AI = 3 / (4*2 + 8*3) = .09375
   */
  unsigned int N_half = N/2;
  long total_bytes = N_half * 32;
  double sum = 0;
  clock_t start = clock();
  for (int i=0; i < N_half; i++)
  {	  
      sum += array[indices[i]] + array[indices[i+N_half]];
  }
  clock_t end = clock();

  double elapsed = (double)(end-start) / CLOCKS_PER_SEC;
  double estimated_bandwidth = total_bytes / elapsed;
  printf("****RANDOM****\n");
  printf("SUM %f\n", sum);
  printf("elapsed_time %f\n", elapsed);
  printf("estimated_bandwidth %liB/s\n", (long)estimated_bandwidth);
}
int main(int argc, char * argv[])
{
  unsigned int N = 100000000; // size of array
  unsigned int N_half = N/2; // half array size
  int i, idx1, idx2, *indices;
  double sum, *array;

  indices = malloc(N * sizeof(int));
  array = malloc(N * sizeof(double));

  allocate(indices, array, N);
  seq_bandwidth(array, N);

  shuffle(indices, N);
  rnd_bandwidth(indices, array, N);

  exit(0);
}
