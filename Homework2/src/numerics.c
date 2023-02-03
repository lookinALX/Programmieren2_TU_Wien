#include "Vector.h"
#include "numerics.h"

#include <stdio.h>  // printf
#include <assert.h> // assert
#include <math.h>   // fabs

struct Vector *num_linspace(double start, double stop, size_t n)
{
  struct Vector *vec = vector_new();
  vector_init(vec, n, 0.);
  double step = fabs((stop - start) / (n - 1));
  int iterator = 0;
  double tmp_step = start;
  while (iterator < n)
  {
    vector_push_back(vec, tmp_step);
    vector_pop_front(vec);
    tmp_step += step;
    iterator += 1;
  }
  return vec;
}

struct Vector *num_sample(const struct Vector *x, double (*func)(double))
{
  struct Vector *res = vector_new();
  vector_init(res, x->size, 0.);
  for (int i = 0; i < x->size; i++)
  {
    vector_push_back(res, func(x->data[i]));
    vector_pop_front(res);
  }
  return res;
}

struct Vector *num_interpolate(const struct Vector *xinterp,
                               const struct Vector *x, const struct Vector *f)
{
  // y = y1 + (x-x1)*(y2-y1)/(x2-x1)
  struct Vector *resf = vector_new();
  vector_init(resf, xinterp->size, 0.);
  for (int i = 0; i < xinterp->size; i++)
  {
    if (xinterp->data[i] < x->data[0])
    {
      resf->data[i] = f->data[0];
    }
    else if (xinterp->data[i] > x->data[x->size - 1])
    {
      resf->data[i] = f->data[f->size - 1];
    }
    else
    {
      double x1 = 0;
      double x2 = 0;
      double y1 = 0;
      double y2 = 0;
      for (int j = 0; i < x->size; j++)
      {
        if (x->data[j] > xinterp->data[i])
        {
          x2 = x->data[j];
          x1 = x->data[j - 1];
          y2 = f->data[j];
          y1 = f->data[j - 1];
          resf->data[i] = y1 + (xinterp->data[i] - x1) * (y2 - y1) / (x2 - x1);
          break;
        }
        else if (x->data[j] == xinterp->data[i])
        {
          resf->data[i] = f->data[j];
          break;
        }
      }
    }
  }
  return resf;
}

struct Vector *num_grad(const struct Vector *x, const struct Vector *f)
{
  struct Vector *grad = vector_new();
  vector_init(grad, x->size, 0.);
  int size = x->size - 1;
  grad->data[0] = (f->data[1] - f->data[0]) / (x->data[1] - x->data[0]);
  for (int i = 1; i < size + 1; i++)
  {
    grad->data[i] =
        (f->data[i + 1] - f->data[i - 1]) / (x->data[i + 1] - x->data[i - 1]);
    if (i == size)
    {
      grad->data[i] =
          (f->data[i] - f->data[i - 1]) / (x->data[i] - x->data[i - 1]);
    }
  }
  return grad;
}

double num_integrate(const struct Vector *x, const struct Vector *f)
{
  double final_integral = 0;
  for (int i = 0; i < x->size - 1; i++)
  {
    final_integral +=
        (x->data[i + 1] - x->data[i]) * (f->data[i] + f->data[i + 1]) / 2;
  }
  return final_integral;
}
