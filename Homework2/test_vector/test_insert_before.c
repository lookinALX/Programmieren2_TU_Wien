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

  printf("before insert_before, ");
  vector_print(&vec);

  assert(vec.size == n);

  size_t insert_bf = 5;
  vector_insert_before(&vec, insert_bf, 100);

  printf("after insert_before,  ");
  vector_print(&vec);

  assert(vec.size == n + 1);

  for (size_t i = 0; i != insert_bf; ++i)
  {
    assert(compare_releps(vec.data[i], i));
  }

  assert(compare_releps(vec.data[insert_bf], 100));

  for (size_t i = insert_bf + 1; i != n + 1; ++i)
  {
    assert(compare_releps(vec.data[i], i - 1));
  }

  vector_free(&vec);

  assert(vec.data == NULL);
  assert(vec.size == 0);

  return 0;
}
