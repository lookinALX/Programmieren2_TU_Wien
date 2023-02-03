#include "HashTable.h"

#include <errno.h>   // errno
#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <stdlib.h>  // malloc/realloc
#include <string.h>  // strerror
#include <stdio.h>   // printf
#include <stdlib.h>  // EXIT_FAILURE, malloc, realloc

void *wrap_malloc(size_t bytes)
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

void *wrap_realloc(void *ptr, size_t new_bytes)
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

void wrap_free(void *ptr)
{
  free(ptr);
}

static void hashtable_init(struct HashTable *self, size_t size,
                           size_t (*hash)(const T *item),
                           bool (*compare)(const T *a, const T *b))
{
  self->count = 0;
  self->hash = hash;
  self->compare = compare;
  self->size = size;
  self->data = wrap_malloc(size * sizeof(struct HashTableEntry));
  for (size_t n = 0; n != self->size; ++n)
    self->data[n].list = NULL;
}

struct HashTable *hashtable_new(size_t size, size_t (*hash)(const T *item),
                                bool (*compare)(const T *a, const T *b))
{
  struct HashTable *res = wrap_malloc(sizeof(struct HashTable));
  hashtable_init(res, size, hash, compare);
  return res;
}

void hashtable_clear(struct HashTable *self)
{
  for (size_t n = 0; n != self->size; ++n)
  {
    struct Node *iter = self->data[n].list;
    while (iter != NULL)
    {
      struct Node *tmp = iter;
      iter = iter->next;
      wrap_free(tmp);
      --self->count;
    }
    self->data[n].list = NULL;
  }
}

void hashtable_delete(struct HashTable **self)
{
  hashtable_clear(*self);
  wrap_free((*self)->data);
  wrap_free(*self);
  *self = NULL;
}

void hashtable_print(const struct HashTable *self, void (*print)(const T *item))
{
  printf("--------- HashTable start\n");
  for (size_t n = 0; n != self->size; ++n)
  {
    struct Node *iter = self->data[n].list;
    while (iter != NULL)
    {
      printf("[idx=%ld] ", n);
      print(&iter->value);
      iter = iter->next;
    }
  }
  printf("--------- HashTable end\n");
}

void hashtable_info(const struct HashTable *self)
{
  printf("HashTable Info (count=%li, size=%li, load_factor=%f)\n", self->count,
         self->size, self->count / (double)self->size);
}

bool hashtable_insert(struct HashTable *self, const T *value)
{
  size_t idx = self->hash(value) % self->size;

  struct Node *iter = self->data[idx].list;

  if (iter == NULL)
  {
    self->data[idx].list = wrap_malloc(sizeof(struct Node));
    self->data[idx].list->next = NULL;
    self->data[idx].list->value = *value;
    ++self->count;
    return true;
  }

  while (iter != NULL)
  {
    if (self->compare(&iter->value, value))
      return false;
    iter = iter->next;
  }

  struct Node *nnode = wrap_malloc(sizeof(struct Node));
  nnode->next = self->data[idx].list;
  nnode->value = *value;
  self->data[idx].list = nnode;
  ++self->count;
  return true;
}
