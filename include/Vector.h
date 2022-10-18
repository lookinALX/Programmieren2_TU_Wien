#pragma once

#include <stddef.h> // size_t

typedef double T;

struct Vector
{
  T *data;
  size_t size;
};

void vector_init(struct Vector *self, size_t n, const T *init);
void vector_free(struct Vector *self);

void vector_push_back(struct Vector *self, const T *value);
void vector_pop_back(struct Vector *self);

void vector_push_front(struct Vector *self, const T *value);
void vector_pop_front(struct Vector *self);

void vector_insert_before(struct Vector *self, size_t n, const T *value);
void vector_erase(struct Vector *self, size_t n);

void vector_reverse(struct Vector *self);

void vector_print(const struct Vector *self);
