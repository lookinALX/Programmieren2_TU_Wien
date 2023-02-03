#include "Vector.h"
#include "helpers.h"
#include "numerics.h"

#include <stdio.h>  // printf
#include <assert.h> // assert
#include <math.h>   // sin

double func1(double x)
{
  return 1 * x;
}

int main()
{
  {
    printf("gradient of linear function\n");
    size_t n = 11;

    struct Vector *x = num_linspace(-2.0, 2.0, n);
    struct Vector *f = num_sample(x, func1);

    struct Vector *df = num_grad(x, f);

    vector_print(x);
    vector_print(f);
    vector_print(df);

    for (int i = 0; i != n; ++i)
    {
      assert(compare_releps(df->data[i], 1.0));
    }

    vector_delete(&x);
    vector_delete(&f);
    vector_delete(&df);
  }

  {
    printf("gradient of sin() \n");
    size_t n = 51;

    struct Vector *x = num_linspace(-0.0, 2 * M_PI, n);
    struct Vector *f = num_sample(x, sin);

    struct Vector *df = num_grad(x, f);

    vector_print(x);
    vector_print(f);
    vector_print(df);

    for (int i = 0; i != n; ++i)
    {
      assert(compare_abseps(df->data[i], cos(x->data[i]), 1e-2));
    }

    vector_delete(&x);
    vector_delete(&f);
    vector_delete(&df);
  }

  return 0;
}
