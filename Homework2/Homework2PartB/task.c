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
  // y = y1 + (x-x1)(y2-y1)/(x2-x1)
  struct Vector *res = vector_new();
  vector_reserve(res, xinterp->size);
  for(int i = 0; i < xinterp->size; i++){
    if(xinterp->data[i] < x->data[0]){
      res->data[i] = f->data[0];
    }
    else if (xinterp->data[i] > x->data[x->size - 1])
    {
      res->data[i] = f->data[f->size-1];
    }
    else{
      double x1 = 0;
      double x2 = 0;
      double y1 = 0;
      double y2 = 0;
      for (int j = 0; j < x->size; j++)
      {
        if(x->data[j] > xinterp->data[i]){
          x1 = x->data[j-1];
          x2 = x->data[j];
          y1 = f->data[j-1];
          y2 = f->data[j];
          res->data[i] = y1 + (xinterp->data[i] - x1)*(y2-y1)/(x2-x1);
        }
      }
      
    }
  }
  return res; // TODO: remove this placeholder and implement function here.
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

  struct Vector *f = num_sample(x, &func);

  // 2. interpolate function values for the 5 provided x-values ('xinterp')
  // using 'num_interpolate'.

  struct Vector *fint= num_interpolate(xinterp,x, f);

  // 3. print the sampled function values and the interpolated function values
  // using 'vector_print'.

  vector_print(f);
  vector_print(fint);

  vector_delete(&x);
  vector_delete(&xinterp);

  vector_delete(&f);
  vector_delete(&fint);

  return 0;
}