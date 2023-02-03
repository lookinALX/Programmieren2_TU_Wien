#include <stddef.h> // size_t
#include <assert.h> // assert
#include <stdio.h>  // printf
#include <stdlib.h> // malloc, realloc
#include <math.h>   // sin

#include "Vector.h"

struct Vector *num_linspace(double start, double stop, size_t n)
{
  assert(n > 1);
  struct Vector *res = vector_new();
  vector_reserve(res, n);
  double step = (stop - start) / (n - 1);
  for (int i = 0; i != n; ++i)
    vector_push_back(res, start + i * step);
  return res;
}

struct Vector *num_sample(const struct Vector *x, double (*func)(double))
{
  struct Vector *res = vector_new();
  vector_reserve(res, x->size);
  for (size_t i = 0; i != x->size; ++i)
    vector_push_back(res, func(x->data[i]));
  return res;
}

// TODO: implement num_interpolate
struct Vector *num_interpolate(const struct Vector *xinterp,
                               const struct Vector *x, const struct Vector *f)
{
  return NULL; // TODO: remove this placeholder and implement function here.
}

double func(double x)
{
  return x * x;
}

int main()
{
  size_t n = 10;
  struct Vector *x = num_linspace(-2.0, 0.0, n);
  vector_print(x);

  size_t ninterp = 5;
  struct Vector *xinterp = num_linspace(-3.0, 1.0, ninterp);
  vector_print(xinterp);

  // TODO:
  // 1. sample 'func' for the 10 provided x-values ('x') using 'num_sample'.
  // 2. interpolate function values for the 5 provided x-values ('xinterp')
  // using 'num_interpolate'.
  // 3. print the sampled function values and the interpolated function values
  // using 'vector_print'.

  vector_delete(&x);
  vector_delete(&xinterp);

  return 0;
}