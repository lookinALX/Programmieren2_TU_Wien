#pragma once

#include <stddef.h>  // size_t
#include <stdbool.h> // bool

struct Item // type to be stored in the list
{
  char name[128];
};

typedef struct Item T;

struct ListNode // type for nodes in the list
{
  struct ListNode *prev; // pointer to previous node
  struct ListNode *next; // pointer to next node
  T value;               // value (struct Item)
};

struct List
{
  struct ListNode *entry; // cyclic entry node (before first AND after last)
};

// provided
struct List *list_new();
void list_delete(struct List **self);
void list_clear(struct List *self);
size_t list_size(const struct List *self);
void list_push_back(struct List *self, const T *value);
void list_pop_back(struct List *self);
struct ListNode *list_node_at(struct List *self, size_t n);
void list_print(const struct List *self);
void list_erase(struct ListNode *node);

// homework
struct List *list_clone(const struct List *self);
void list_concat(struct List *dest, struct List *src);
void list_reverse(struct List *self);
struct ListNode *list_find(struct ListNode *start, struct ListNode *end,
                           bool (*predicate)(const T *value));
