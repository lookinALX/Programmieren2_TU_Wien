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
  struct HashTable *ht = wrap_malloc(sizeof(struct HashTable));
  ht->size = size;
  ht->max_load_factor = max_load_factor;
  ht->hash = hash;
  ht->compare = compare;
  ht->count = 0;
  ht->data = wrap_malloc(size * sizeof(struct HashTableEntry));
  for (int i = 0; i < size; i++)
  {
    ht->data[i].list = NULL;
  }
  return ht;
}

void hashtable_resize(struct HashTable *self, size_t size)
{
  size_t old_size = self->size;
  struct HashTableEntry *old_data =
      malloc(old_size * sizeof(struct HashTableEntry));
  for (int i = 0; i < old_size; i++)
  {
    old_data[i] = self->data[i];
  }
  self->size = size;
  self->data = wrap_realloc(self->data, size * sizeof(struct HashTableEntry));
  hashtable_clear(self);
  for (int i = 0; i < old_size; i++)
  {
    struct Node *iter = old_data[i].list;
    while (iter != NULL)
    {
      hashtable_insert(self, &(iter->value));
      iter = iter->next;
    }
  }
}

void hashtable_clear(struct HashTable *self)
{
  for (int i = 0; i < self->size; i++)
  {
    self->data[i].list = NULL;
    self->count = 0;
  }
}

void hashtable_delete(struct HashTable **self)
{
  wrap_free((*self)->data);
  wrap_free(*self);
  *self = NULL;
}

T *hashtable_find(struct HashTable *self, const T *value)
{
  size_t index = self->hash(value) % self->size;
  struct Node *iter = self->data[index].list;
  while (iter != NULL)
  {
    if (self->compare(&(iter->value), value))
    {
      return &(iter->value);
    }
    iter = iter->next;
  }
  return NULL;
}

bool hashtable_insert(struct HashTable *self, const T *value)
{
  if (self == NULL)
    return false;
  size_t index = self->hash(value) % self->size;
  printf("%zu, %zu \n", index, self->size);
  if (self->data[index].list != NULL)
  {
    struct Node *iter = self->data[index].list;
    while (iter != NULL)
    {
      if (self->compare(&(iter->value), value))
      {
        return false;
      }
      iter = iter->next;
    }
    self->count += 1;
    if (self->max_load_factor < (self->count / (double)self->size))
    {
      hashtable_resize(self, 2 * self->size);
      self->count += 1;
    }
    struct Node *new_node = wrap_malloc(sizeof(struct Node));
    new_node->next = self->data[index].list->next;
    new_node->value = *value;
    self->data[index].list->next = new_node;
    return true;
  }
  else
  {
    self->count += 1;
    if (self->max_load_factor < (self->count / (double)self->size))
    {
      hashtable_resize(self, 2 * self->size);
      self->count += 1;
    }
    self->data[index].list = wrap_malloc(sizeof(struct Node));
    self->data[index].list->value = *value;
    self->data[index].list->next = NULL;
    return true;
  }
}

bool hashtable_erase(struct HashTable *self, const T *value)
{
  size_t index = self->hash(value) % self->size;
  struct Node *current_node = self->data[index].list;
  struct Node *prev_node = NULL;
  while (current_node != NULL)
  {
    if (self->compare(&(current_node->value), value))
    {
      if (prev_node == NULL)
      {
        self->data[index].list = current_node->next;
        //current_node = NULL;
        wrap_free(current_node);
        self->count -= 1;
      }
      else
      {
        prev_node->next = current_node->next;
        //current_node = NULL;
        wrap_free(current_node);
        self->count -= 1;
      }
      return true;
    }
    prev_node = current_node;
    current_node = current_node->next;
  }
  return false;
}
