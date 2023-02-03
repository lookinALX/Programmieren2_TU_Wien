#include "Vector.h"
#include "helpers.h"

#include <assert.h>  // assert
#include <stdio.h>   // printf
#include <stdbool.h> // printf

int main()
{

  struct Vector vec = {NULL, 0};
  size_t cap = 10;

  vector_reserve(&vec, cap);

  printf("after vector_reserve, ");
  vector_print(&vec);

  assert(vec.data != NULL);
  assert(vec.size == 0);
  assert(vec.cap == cap);

  vector_reserve(&vec, cap);

  double *data_reserve = vec.data;

  size_t n = 5;
  for (size_t i = 0; i != n; ++i)
    vector_push_back(&vec,i);

  printf("after push_back, ");
  vector_print(&vec);

  assert(vec.size == n);
  assert(vec.cap == cap);
  assert(vec.data == data_reserve);

  vector_shrink(&vec);

  printf("after vector_shrink, ");
  vector_print(&vec);

  assert(vec.size == n);
  assert(vec.cap == n);
  assert(vec.data != data_reserve);

  vector_shrink(&vec);

  vector_free(&vec);

  assert(vec.data == NULL);
  assert(vec.size == 0);

  return 0;
}
