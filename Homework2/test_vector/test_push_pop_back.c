#include "Vector.h"
#include "helpers.h"

#include <stdio.h>  // printf
#include <assert.h> // assert

int main()
{

  struct Vector vec = {NULL, 0};
  double init = 0;
  vector_init(&vec, 0, init);

  assert(vec.data == NULL);
  assert(vec.size == 0);

  size_t n = 10;

  printf("before push_back, ");
  vector_print(&vec);

  for (size_t i = 0; i != n; ++i)
  {
    vector_push_back(&vec, i);
  }

  printf("after push_back,  ");
  vector_print(&vec);

  assert(vec.data != NULL);
  assert(vec.size == n);
  for (size_t i = 0; i != n; ++i)
  {
    assert(compare_releps(vec.data[i], i));
  }

  for (size_t i = 0; i != n; ++i)
  {
    vector_pop_back(&vec);
  }

  printf("after pop_back,   ");
  vector_print(&vec);

  assert(vec.size == 0);

  vector_free(&vec);

  assert(vec.data == NULL);
  assert(vec.size == 0);

  return 0;
}
