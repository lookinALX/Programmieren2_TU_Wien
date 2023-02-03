#include "List.h"

#include <assert.h>  // assert
#include <errno.h>   // errno
#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <stdio.h>   // printf
#include <stdlib.h>  // errno, EXIT_FAILURE, malloc, realloc
#include <string.h>  // strerror

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

struct List *list_new()
{
  struct List *res = wrap_malloc(sizeof(struct List));
  res->entry = wrap_malloc(sizeof(struct ListNode));
  res->entry->prev = res->entry;
  res->entry->next = res->entry;
  return res;
}

void list_delete(struct List **self)
{
  list_clear(*self);
  wrap_free((*self)->entry);
  wrap_free(*self);
  *self = NULL;
}

void list_clear(struct List *self)
{
  struct ListNode *iter = self->entry->next;
  while (iter != self->entry)
  {
    struct ListNode *next = iter->next;
    list_erase(iter);
    iter = next;
  }
}

void list_erase(struct ListNode *node)
{
  node->prev->next = node->next;
  node->next->prev = node->prev;
  node->prev = NULL;
  node->next = NULL;
  wrap_free(node);
}

struct ListNode *list_at(struct List *self, size_t n)
{
  struct ListNode *iter = self->entry->next;
  size_t pos = 0;
  while (pos != n)
  {
    iter = iter->next;
    ++pos;
  }
  return iter;
}

size_t list_size(const struct List *self)
{
  struct ListNode *iter = self->entry->next;
  size_t pos = 0;
  while (iter != self->entry)
  {
    iter = iter->next;
    ++pos;
  }
  return pos;
}

struct ListNode *list_node_at(struct List *self, size_t n)
{
  struct ListNode *iter = self->entry->next;
  size_t pos = 0;
  while (pos != n)
  {
    iter = iter->next;
    ++pos;
  }
  return iter;
}

void list_push_back(struct List *self, const T *value)
{
  struct ListNode *node = wrap_malloc(sizeof(struct ListNode));
  node->value = *value;
  node->prev = self->entry->prev;
  node->next = self->entry;
  self->entry->prev->next = node;
  self->entry->prev = node;
}

void list_pop_back(struct List *self)
{
  list_erase(self->entry->prev);
}

void list_print(const struct List *self)
{
  printf("List(entry=%p): \n", (void *)self->entry);
  struct ListNode *iter = self->entry->next;
  while (iter != self->entry)
  {
    printf("%s \n", iter->value.name);
    iter = iter->next;
  }
  printf("\n");
}

// start homework

struct List *list_clone(const struct List *other)
{
  struct List *list_clone = list_new();
  int size = list_size(other);
  struct ListNode *tmp_node = other->entry->next;
  for (int i = 0; i < size; i++)
  {
    struct Item tmp_value = tmp_node->value;
    list_push_back(list_clone, &(tmp_value));
    tmp_node = tmp_node->next;
  }
  return list_clone;
}

void list_reverse(struct List *self)
{
  struct ListNode *node_first = self->entry;
  struct ListNode *node_second = self->entry->next;
  int size = list_size(self);

  for (int i = 0; i < size + 1; i++)
  {
    node_second->prev = node_second->next;
    node_second->next = node_first;
    node_first = node_second;
    node_second = node_second->prev;
  }
}

void list_concat(struct List *dest, struct List *src)
{
  int size = list_size(src);
  struct ListNode *tmp_node = src->entry;
  tmp_node->next = src->entry->next;
  tmp_node->prev = src->entry->prev;

  dest->entry->prev->next = tmp_node->next;
  tmp_node->prev->next = dest->entry;
  tmp_node->next->prev = dest->entry->prev;

  src->entry->next = src->entry;
  src->entry->prev = src->entry;
}

struct ListNode *list_find(struct ListNode *start, struct ListNode *end,
                           bool (*predicate)(const T *value))
{
  struct ListNode *node_next = start;

  while (node_next != end)
  {
    if (predicate(&(node_next->value)))
    {
      return node_next;
    }
    else
    {
      node_next = node_next->next;
    }
  }
  return end;
}
