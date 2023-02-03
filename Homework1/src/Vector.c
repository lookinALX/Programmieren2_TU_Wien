#include "Vector.h"

#include <stddef.h> // size_t
#include <stdio.h>  // printf
#include <stdlib.h>

void vector_init(struct Vector *self, size_t n, const T *init)
{
  if (self->data != NULL)
  {
    free(self->data);
  }

  if (n > 0)
  {
    self->data = malloc(n * sizeof(const T));
    self->size = n;

    for (int i = 0; i != n; ++i)
    {
      *(self->data + i) = *init;
    }
  }
}

void vector_free(struct Vector *self)
{
  if (self->data != NULL)
  {
    free(self->data);
    self->data = NULL;
    self->size = 0;
  }
}

void vector_push_back(struct Vector *self, const T *value)
{
  if (self->size == 0)
  {
    self->data = malloc(sizeof(const T));
  }
  size_t oldsize = self->size;
  self->size = oldsize + 1;
  self->data = realloc(self->data, (self->size) * sizeof(const T));
  self->data[self->size - 1] = *value;
}

void vector_pop_back(struct Vector *self)
{
  if (self->size == 0)
  {
    vector_free(self);
  }
  else
  {
    size_t oldsize = self->size;
    double newdata[oldsize - 1];

    for (int i = 0; i != oldsize - 1; i++)
    {
      newdata[i] = self->data[i];
    }

    self->size = oldsize - 1;

    if (self->size == 0)
    {
      vector_free(self);
    }
    else
    {
      self->data = malloc((oldsize - 1) * sizeof(const T));
      for (int i = 0; i != oldsize - 1; i++)
      {
        self->data[i] = newdata[i];
      }
    }
  }
}

void vector_push_front(struct Vector *self, const T *value)
{
  size_t newsize = self->size + 1;

  if (self->size == 0)
  {
    self->data = malloc(sizeof(const T));
    self->data[0] = *value;
    self->size = newsize;
  }
  else
  {
    self->data = realloc(self->data, newsize * sizeof(const T));
    self->size = newsize;
    for (int i = newsize - 1; i >= 0; i--)
    {
      if (i != 0)
      {
        self->data[i] = self->data[i - 1];
      }
      else
      {
        self->data[i] = *value;
      }
    }
  }
}

void vector_pop_front(struct Vector *self)
{
  if (self->size - 1 <= 0)
  {
    vector_free(self);
  }
  else
  {
    size_t newsize = self->size - 1;
    double newdata[newsize];
    for (int i = 1; i != self->size; ++i)
    {
      newdata[i - 1] = self->data[i];
    }
    vector_free(self);
    self->size = newsize;
    self->data = malloc(newsize * sizeof(const T));
    for (int i = 0; i != newsize; i++)
    {
      self->data[i] = newdata[i];
    }
  }
}

void vector_insert_before(struct Vector *self, size_t n, const T *value)
{
  if (self->size == 0)
  {
    printf("You have to init the Vector!");
  }
  else
  {
    self->size = self->size + 1;
    self->data = realloc(self->data, self->size * sizeof(const T));
    double tmp;
    for (int i = self->size - 1; i >= n; i--)
    {
      if (i == n)
      {
        self->data[i] = *value;
      }
      else
      {
        self->data[i] = self->data[i - 1];
      }
    }
  }
}

void vector_erase(struct Vector *self, size_t n)
{
  if (self->size == 0)
  {
    printf("You have to init the Vector!");
  }
  else
  {
    size_t newsize = self->size - 1;
    double newdata[newsize];
    for (int i = 0; i != newsize; i++)
    {
      if (i >= n)
      {
        newdata[i] = self->data[i+1];
      }
      else
      {
        newdata[i] = self->data[i];
      }
    }
    vector_free(self);
    self->size = newsize;
    self->data = malloc(newsize * sizeof(const T));
    for (int i = 0; i != newsize; i++)
    {
      self->data[i] = newdata[i];
    }
  }
}

void vector_reverse(struct Vector *self)
{
  double tmp = 0;
  double size = self->size;
  for (int i = 0; i < 0.5 * (size); i++)
  {
    tmp = self->data[i];
    self->data[i] = self->data[(self->size - 1) - i];
    self->data[(self->size - 1) - i] = tmp;
  }
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
