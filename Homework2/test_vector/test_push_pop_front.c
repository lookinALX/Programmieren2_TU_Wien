#include "Vector.h"
#include "helpers.h"

#include <assert.h> // assert
#include <stdio.h>  // printf

int main()
{

  struct Vector vec = {NULL, 0};
  double init = 0;
  vector_init(&vec, 0, init);

  assert(vec.data == NULL);
  assert(vec.size == 0);

  printf("before push_front, ");
  vector_print(&vec);

  int n = 10;

  for (int i = 0; i != n; ++i)
  {
    vector_push_front(&vec, i);
    assert(compare_releps(vec.data[0], i));
  }

  printf("after push_front, ");
  vector_print(&vec);

  assert(vec.data != NULL);
  assert(vec.size == n);

  for (int i = n; i != 0; --i)
  {
    assert(compare_releps(vec.data[i - 1], n - i));
  }

  for (int i = 0; i != n; ++i)
  {
    assert(compare_releps(vec.data[0], n - i - 1));
    vector_pop_front(&vec);
  }

  printf("after pop_front,  ");
  vector_print(&vec);

  assert(vec.size == 0);

  vector_free(&vec);

  assert(vec.data == NULL);
  assert(vec.size == 0);

  return 0;
}
