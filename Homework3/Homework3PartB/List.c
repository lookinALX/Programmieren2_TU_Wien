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
    iter->prev->next = iter->next;
    iter->next->prev = iter->prev;
    wrap_free(iter);
    iter = next;
  }
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

void list_push_back(struct List *self, const T *value)
{
  struct ListNode *node = wrap_malloc(sizeof(struct ListNode));
  node->value = *value;
  node->prev = self->entry->prev;
  node->next = self->entry;
  self->entry->prev->next = node;
  self->entry->prev = node;
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

