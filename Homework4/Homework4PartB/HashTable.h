#pragma once

#include "Book.h"

#include <stdbool.h> // bool
#include <stddef.h>  // size_t

void *wrap_malloc(size_t bytes);
void *wrap_realloc(void *ptr, size_t new_bytes);
void wrap_free(void *ptr);

typedef struct Book T; // stored type

struct Node
{
  struct Node *next; // next node in list (or NULL if last node in list)
  T value;           // stored value
};

struct HashTableEntry
{
  struct Node *list; // first node in list (or NULL if list is empty)
};

struct HashTable
{
  struct HashTableEntry *data;    // array indexed by the hashed value
  size_t size;                    // size of the array
  size_t count;                   // number of aktive entries
  size_t (*hash)(const T *value); // hash function for entries/keys
  bool (*compare)(const T *value1,
                  const T *value2); // compare function for entries/keys
};

struct HashTable *hashtable_new(size_t size, size_t (*hash)(const T *value),
                                bool (*compare)(const T *value1,
                                                const T *value2));
void hashtable_delete(struct HashTable **self);
void hashtable_clear(struct HashTable *self);

void hashtable_print(const struct HashTable *self,
                     void (*print)(const T *value));
void hashtable_info(const struct HashTable *self);
bool hashtable_insert(struct HashTable *self, const T *value);
