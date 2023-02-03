#include "Vector.h"
#include "helpers.h"
#include "numerics.h"

#include <stdio.h>  // printf
#include <assert.h> // assert
#include <math.h>   // cos

int main()
{

  {
    printf("sample cos() in the range 0 to 2*PI\n");

    int n = 21;

    struct Vector *x = num_linspace(0, 2 * M_PI, n);
    struct Vector *y = num_sample(x, cos);

    vector_print(x);
    vector_print(y);

    for (int i = 0; i != n; ++i)
      assert(compare_releps(y->data[i], cos(x->data[i])));

    vector_delete(&x);
    vector_delete(&y);
  }

  return 0;
}
