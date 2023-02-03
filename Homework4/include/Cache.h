#pragma once

#include "Book.h"

#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <stdlib.h>  // malloc
#include <string.h>  // strlen
#include <stdio.h>   // printf

typedef struct Book T; // stored type

struct CacheEntry
{
  bool empty; // flag indicating if value is active
  T value;    // stored value
};

struct Cache
{
  struct CacheEntry *data;        // array indexed by the hashed value
  size_t size;                    // size of the array
  size_t count;                   // number of active entries
  float max_load_factor;          // maximum load factor (count/size)
  size_t (*hash)(const T *value); // hash function
  bool (*compare)(const T *value1,
                  const T *value2); // compare function
};

struct Cache *cache_new(size_t size, float max_load_factor,
                        size_t (*hash)(const T *value),
                        bool (*compare)(const T *value1, const T *value2));
void cache_delete(struct Cache **self);
void cache_resize(struct Cache *self, size_t size);
void cache_clear(struct Cache *self);

bool cache_insert(struct Cache *self, const T *value);
T *cache_find(struct Cache *self, const T *value);
bool cache_erase(struct Cache *self, const T *value);

void cache_print(const struct Cache *self, void (*print)(const T *value));
void cache_info(const struct Cache *self);
