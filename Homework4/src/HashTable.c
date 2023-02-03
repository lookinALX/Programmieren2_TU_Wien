#include "HashTable.h"
#include "Logger.h"

#include <errno.h>   // errno
#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <stdlib.h>  // malloc/realloc
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

void hashtable_print(const struct HashTable *self, void (*print)(const T *item))
{
  printf("---------- Hashtable start\n");
  for (size_t n = 0; n != self->size; ++n)
  {
    struct Node *iter = self->data[n].list;
    while (iter != NULL)
    {
      print(&iter->value);
      iter = iter->next;
    }
  }
  printf("--------- Hashtable end\n");
}

void hashtable_info(const struct HashTable *self)
{
  printf("Hashtable Info (count=%li, size=%li, "
         "max_load_factor=%f,current_load_factor=%f)\n",
         self->count, self->size, self->max_load_factor,
         self->count / (double)self->size);
}

struct HashTable *hashtable_new(size_t size, float max_load_factor,
                                size_t (*hash)(const T *item),
                                bool (*compare)(const T *a, const T *b))
{
  return NULL; // TODO: implement
}

void hashtable_resize(struct HashTable *self, size_t size)
{
  // TODO: implement
}

void hashtable_clear(struct HashTable *self)
{
  // TODO: implement
}

void hashtable_delete(struct HashTable **self)
{
  // TODO: implement
}

T *hashtable_find(struct HashTable *self, const T *value)
{
  return NULL; // TODO: implement
}

bool hashtable_insert(struct HashTable *self, const T *value)
{
  return false; // TODO: implement
}

bool hashtable_erase(struct HashTable *self, const T *value)
{
  return false; // TODO: implement
}

