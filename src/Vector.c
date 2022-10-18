#include "Vector.h"

#include <stddef.h> // size_t
#include <stdio.h>  // printf

// TODO: add required includes here

void vector_init(struct Vector *self, size_t n, const T *init)
{
  // TODO
}

void vector_free(struct Vector *self)
{
  // TODO
}

void vector_push_back(struct Vector *self, const T *value)
{
  // TODO
}

void vector_pop_back(struct Vector *self)
{
  // TODO
}

void vector_push_front(struct Vector *self, const T *value)
{
  // TODO
}

void vector_pop_front(struct Vector *self)
{
  // TODO
}

void vector_insert_before(struct Vector *self, size_t n, const T *value)
{
  // TODO
}

void vector_erase(struct Vector *self, size_t n)
{
  // TODO
}

void vector_reverse(struct Vector *self)
{
  // TODO
}

void vector_print(const struct Vector *self)
{
  printf("Vector(size=%li, data=%p): ", self->size, (void *)self->data);
  for (size_t i = 0; i != self->size; ++i)
  {
    printf("%f ", self->data[i]);
  }
  printf("\n");
}
