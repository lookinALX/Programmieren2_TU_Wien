#include "Vector.h"
#include "helpers.h"
#include "numerics.h"

#include <stdio.h>  // printf
#include <assert.h> // assert
#include <math.h>   // assert

double func(double x)
{
  return x * x;
}

int main()
{

  printf("sampling function in interval 0 to 4\n");

  size_t n = 101;
  double start = 0.0;
  double end = 4.0;

  struct Vector *x = num_linspace(start, end, n);
  struct Vector *f = num_sample(x, func);

  // vector_print(x);
  // vector_print(f);

  {
    printf("interpolation, interval 1 to 2\n");

    size_t n = 11;

    struct Vector *xinterp = num_linspace(1.0, 2.0, n);
    struct Vector *finterp = num_interpolate(xinterp, x, f);

    vector_print(finterp);
    vector_print(xinterp);

    for (int i = 0; i != n; ++i)
    {
      printf("%f %f %f \n", xinterp->data[i], finterp->data[i],
             func(xinterp->data[i]));
      assert(compare_abseps(finterp->data[i], func(xinterp->data[i]),
                                    1e-3));
    }

    vector_delete(&xinterp);
    vector_delete(&finterp);
  }

  {
    printf("interpolation, interval -1 to 5 \n");

    size_t n = 11;

    struct Vector *xinterp = num_linspace(-1.0, 5.0, n);
    struct Vector *finterp = num_interpolate(xinterp, x, f);

    vector_print(finterp);
    vector_print(xinterp);

    for (int i = 0; i != n; ++i)
    {
      printf("%f %f %f \n", xinterp->data[i], finterp->data[i],
             func(xinterp->data[i]));

      if (xinterp->data[i] <= start)
        assert(compare_releps(finterp->data[i], f->data[0]));

      if (xinterp->data[i] >= end)
        assert(compare_releps(finterp->data[i], f->data[f->size - 1]));

      if (start < xinterp->data[i] && xinterp->data[i] < end)
        assert(compare_abseps(finterp->data[i], func(xinterp->data[i]),
                                      1e-3));
    }

    vector_delete(&xinterp);
    vector_delete(&finterp);
  }

  vector_delete(&x);
  vector_delete(&f);

  return 0;
}
