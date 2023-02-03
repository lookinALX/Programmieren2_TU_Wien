#include "Vector.h"
#include "helpers.h"
#include "numerics.h"

#include <stdio.h>  // printf
#include <assert.h> // assert

int main()
{

  {
    printf("11 values in the interval from 0 to 10\n");
    // 11 values in the interval from 0 to 10

    struct Vector *vec = num_linspace(0, 10, 11);

    for (int i = 0; i != 11; ++i)
    {
      assert(compare_releps(vec->data[i], i));
    }

    vector_print(vec);
    vector_delete(&vec);
  }

  {
    printf("21 values in the interval from -PI to +PIn");

    struct Vector *vec = num_linspace(-M_PI, +M_PI, 21);

    for (int i = 0; i != 21; ++i)
    {
      assert(compare_releps(vec->data[i], -M_PI + i * 2 * M_PI / 20));
    }

    vector_print(vec);
    vector_delete(&vec);
  }

  return 0;
}
