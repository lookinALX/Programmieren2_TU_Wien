#include "Vector.h"
#include "helpers.h"

#include <assert.h> // assert
#include <stdio.h>  // printf

int main()
{

  struct Vector vec = {NULL, 0};
  size_t n = 10;
  double init = 0;
  vector_init(&vec, n, init);

  assert(vec.data != NULL);
  assert(vec.size == n);

  for (size_t i = 0; i != vec.size; ++i)
    vec.data[i] = i;

  printf("before reverse, ");
  vector_print(&vec);

  double *before = vec.data;
  vector_reverse(&vec);
  double *after = vec.data;

  printf("after reverse,  ");
  vector_print(&vec);

  assert(before == after);
  assert(vec.size == n);

  for (size_t i = n; i != 0; --i)
  {
    assert(compare_releps(vec.data[i - 1], n - i));
  }

  vector_free(&vec);

  assert(vec.data == NULL);
  assert(vec.size == 0);

  return 0;
}
