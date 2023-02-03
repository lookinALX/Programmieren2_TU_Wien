#include "Vector.h"

#include <assert.h> // assert
#include <stdio.h>  // printf

int main()
{

  struct Vector vec = {NULL, 0};
  double init = 0.0;
  vector_init(&vec, 0, &init);

  assert(vec.data == NULL);
  assert(vec.size == 0);

  printf("before push_front, ");
  vector_print(&vec);

  size_t n = 10;

  for (size_t i = 0; i != n; ++i)
  {
    vector_push_front(&vec, &(T){i});
    assert(vec.data[0] == (T){i});
  }

  printf("after push_front, ");
  vector_print(&vec);

  assert(vec.data != NULL);
  assert(vec.size == n);

  for (size_t i = n; i != 0; --i)
  {
    assert(vec.data[i - 1] == (T){n - i});
  }

  for (size_t i = 0; i != n; ++i)
  {
    vector_pop_front(&vec);
  }

  printf("after pop_front,  ");
  vector_print(&vec);

  assert(vec.data == NULL);
  assert(vec.size == 0);

  vector_free(&vec);

  assert(vec.data == NULL);
  assert(vec.size == 0);

  return 0;
}
