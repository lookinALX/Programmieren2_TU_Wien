#include "Vector.h"

#include <assert.h> // assert
#include <stdio.h>  // printf

int main()
{

  struct Vector vec = {NULL, 0};
  size_t n = 10;
  double init = 0.0;
  vector_init(&vec, n, &init);

  assert(vec.data != NULL);
  assert(vec.size == n);

  for (size_t i = 0; i != vec.size; ++i)
    vec.data[i] = (T){i};

  printf("before reverse, ");
  vector_print(&vec);

  T *before = vec.data;
  vector_reverse(&vec);
  T *after = vec.data;

  printf("after reverse,  ");
  vector_print(&vec);

  assert(before == after);
  assert(vec.size == n);

  for (size_t i = n; i != 0; --i)
  {
    assert(vec.data[i - 1] == (T){n - i});
  }

  vector_free(&vec);

  assert(vec.data == NULL);
  assert(vec.size == 0);

  return 0;
}
