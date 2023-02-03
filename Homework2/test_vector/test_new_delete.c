#include "Vector.h"
#include "helpers.h"

#include <stdio.h>  // printf
#include <assert.h> // assert

int main()
{

  struct Vector *vec = vector_new();

  printf("before init, ");
  vector_print(vec);

  {
    size_t n = 15;
    double init = 100;
    vector_init(vec, n, init);
    printf("after first init, ");
    vector_print(vec);
  }

  size_t n = 10;
  double init = 0;
  vector_init(vec, n, init);

  printf("after second init, ");
  vector_print(vec);

  assert(vec->data != NULL);
  assert(vec->size == n);

  for (size_t i = 0; i != vec->size; ++i)
    assert(compare_releps(vec->data[i], init));

  vector_delete(&vec);

  assert(vec == NULL);

  return 0;
}
