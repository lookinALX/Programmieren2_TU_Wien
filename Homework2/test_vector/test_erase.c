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

  assert(vec.size == n);

  printf("before erase, ");
  vector_print(&vec);

  size_t erase_at = 5;
  vector_erase(&vec, erase_at);

  printf("after erase,  ");
  vector_print(&vec);

  assert(vec.size == n - 1);

  for (size_t i = 0; i != erase_at; ++i)
  {
    assert(compare_releps(vec.data[i], i));
  }

  for (size_t i = erase_at; i != n - 1; ++i)
  {
    assert(compare_releps(vec.data[i], i + 1));
  }

  vector_free(&vec);

  assert(vec.data == NULL);
  assert(vec.size == 0);

  return 0;
}
