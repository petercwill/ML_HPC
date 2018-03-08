#include <stdlib.h>
#include <stdio.h>

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

int main(int argc, char * argv[])
{
  unsigned int N = 10; // size of array
  int i, idx1, idx2, *indices;
  double sum, *array;

  indices = malloc(N * sizeof(int));
  array = malloc(N * sizeof(double));

  allocate(indices, array, N);
  shuffle(indices, N);

  print_arrays(indices, array, N);
  sum = 0;
  for (i=0; i < N/2; i++)
  {	  
	  idx1 = indices[i];
	  idx2 = indices[i+N/2];
	  sum += array[idx1] + array[idx2];
  }

  printf("SUM %f\n", sum);

  exit(0);
}
