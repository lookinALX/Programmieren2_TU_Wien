#pragma once

#include <stddef.h>  // size_t
#include <stdbool.h> // bool

struct Vector
{
  double *data; // invariant: points to first element
  size_t size;  // invariant: current number of elements
  size_t cap;   // invariant: current capacity
};

void vector_reserve(struct Vector *self, size_t cap);
void vector_shrink(struct Vector *self);

struct Vector *vector_new();
void vector_delete(struct Vector **self);

void vector_init(struct Vector *self, size_t n, double init);
void vector_free(struct Vector *self);
void vector_clear(struct Vector *self);

void vector_push_back(struct Vector *self, double value);
void vector_pop_back(struct Vector *self);

void vector_push_front(struct Vector *self, double value);
void vector_pop_front(struct Vector *self);

void vector_insert_before(struct Vector *self, size_t n, double value);
void vector_erase(struct Vector *self, size_t n);

void vector_reverse(struct Vector *self);

void vector_print(const struct Vector *self);
