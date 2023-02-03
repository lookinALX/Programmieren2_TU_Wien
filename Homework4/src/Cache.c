#include "Cache.h"
#include "Logger.h"

#include <errno.h>   // errno
#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <stdlib.h>  // malloc ...
#include <string.h>  // strerror
#include <stdio.h>   // printf
#include <stdlib.h>  // EXIT_FAILURE, malloc, realloc

static void *wrap_malloc(size_t bytes)
{
  if (bytes > 0)
  {
    void *ptr = malloc(bytes);
    if (ptr == NULL)
    {
      printf("error allocating %ld bytes: %s \n", bytes, strerror(errno));
      exit(EXIT_FAILURE);
    }
    return ptr;
  }
  else
  {
    return NULL;
  }
}

static void *wrap_realloc(void *ptr, size_t new_bytes)
{
  if (new_bytes > 0)
  {
    ptr = realloc(ptr, new_bytes);
    if (ptr == NULL)
    {
      printf("error reallocating %ld bytes: %s \n", new_bytes, strerror(errno));
      exit(EXIT_FAILURE);
    }
    return ptr;
  }
  else
  {
    free(ptr);
    return NULL;
  }
}

static void wrap_free(void *ptr)
{
  free(ptr);
}

static void cache_init(struct Cache *self, size_t size, float max_load_factor,
                       size_t (*hash)(const T *value),
                       bool (*compare)(const T *value1, const T *value2))
{
  self->count = 0;
  self->max_load_factor = max_load_factor;
  self->hash = hash;
  self->compare = compare;
  self->size = size;
  self->data = wrap_malloc(size * sizeof(struct CacheEntry));
  for (size_t n = 0; n != self->size; ++n)
    self->data[n].empty = true;
}

void cache_resize(struct Cache *self, size_t size)
{
  struct Cache res;
  cache_init(&res, size, self->max_load_factor, self->hash, self->compare);

  for (size_t n = 0; n != self->size; ++n)
    if (self->data[n].empty == false)
      cache_insert(&res, &self->data[n].value);

  wrap_free(self->data);
  *self = res;
}

struct Cache *cache_new(size_t size, float max_load_factor,
                        size_t (*hash)(const T *value),
                        bool (*compare)(const T *value1, const T *value2))
{
  struct Cache *res = wrap_malloc(sizeof(struct Cache));
  cache_init(res, size, max_load_factor, hash, compare);
  return res;
}

void cache_clear(struct Cache *self)
{
  for (size_t n = 0; n != self->size; ++n)
    self->data[n].empty = true;
  self->count = 0;
}

void cache_delete(struct Cache **self)
{
  wrap_free((*self)->data);
  wrap_free(*self);
  *self = NULL;
}

T *cache_find(struct Cache *self, const T *value)
{
  size_t idx = self->hash(value) % self->size;
  if (self->data[idx].empty == false &&
      self->compare(&self->data[idx].value, value))
    return &self->data[idx].value;
  return NULL;
}

double cache_load_factor(const struct Cache *self)
{
  return self->count / (double)self->size;
}

bool cache_insert(struct Cache *self, const T *value)
{
  if (self->count / (double)self->size > self->max_load_factor)
    cache_resize(self, self->size * 2.0);
  size_t idx = self->hash(value) % self->size;
  self->data[idx].value = *value;
  bool res = self->data[idx].empty;
  if (res)
    ++self->count;
  self->data[idx].empty = false;
  return res;
}

bool cache_erase(struct Cache *self, const T *value)
{
  size_t idx = self->hash(value) % self->size;
  if (self->data[idx].empty == false &&
      self->compare(&self->data[idx].value, value))
  {
    --self->count;
    return self->data[idx].empty = true;
  }
  return false;
}

void cache_print(const struct Cache *self, void (*print)(const T *value))
{
  printf("------- Cache start\n");
  for (size_t n = 0; n != self->size; ++n)
  {
    if (self->data[n].empty == false)
    {
      print(&self->data[n].value);
    }
  }
  printf("------- Cache end\n");
}

void cache_info(const struct Cache *self)
{
  printf("Cache Info (count=%li, size=%li, "
         "max_load_factor=%f,current_load_factor=%f)\n",
         self->count, self->size, self->max_load_factor,
         self->count / (double)self->size);
}
