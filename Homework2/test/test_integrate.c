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
    printf("expected zero integral of linear function around origin\n");
    size_t n = 21;

    double start = -2.0;
    double end = 2.0;
    struct Vector *x = num_linspace(-2.0, 2.0, n);
    struct Vector *f = num_sample(x, func1);

    double integral = num_integrate(x, f);

    printf("integral = %e \n ", integral);

    // vector_print(x);
    // vector_print(f);

    assert(compare_abseps(integral, 0.0, 1e-9));

    vector_delete(&x);
    vector_delete(&f);
  }

  {
    printf("integral of sin() from 0 to PI/2\n");

    size_t n = 30;

    struct Vector *x = num_linspace(0, M_PI/2, n);
    struct Vector *f = num_sample(x, sin);

    double integral = num_integrate(x, f);

    printf("integral = %e \n ", integral);
 
    // vector_print(x);
    // vector_print(f);

    assert(compare_abseps(integral, 1.0, 1e-3));

    vector_delete(&x);
    vector_delete(&f);
  }

  return 0;
}
