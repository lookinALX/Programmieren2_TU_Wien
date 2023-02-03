#include "List.h"

#include <assert.h>  // assert
#include <stdio.h>   // printf
#include <string.h>  // strcmp
#include <stdbool.h> // false
#include <stdlib.h>  // malloc free

void list_insert_before(struct ListNode *iter, const T *value)
{
  // TODO: implement
}

void list_insert_after(struct ListNode *iter, const T *value)
{
  // TODO: implement
}

int main()
{

  struct List *list = list_new();

  list_push_back(list, &(T){.name = "N1"});
  list_push_back(list, &(T){.name = "N2"});
  list_push_back(list, &(T){.name = "N3"});

  list_print(list);

  struct ListNode *n2 = list_node_at(list, 1);
  T before = {.name = "before"};
  T after = {.name = "after"};

  // applying 'list_insert_before' to add element 'before' before 'n2'
  list_insert_before(n2, &before);
  // applying 'list_insert_after' to add element 'after' after 'n2'
  list_insert_after(n2, &after);

  list_print(list);

  // TODO: implement asserts to check expectations
  assert(false); // TODO: remove this failing assert
  // TODO assert: check if size of list is now 5
  // TODO assert: check if value.name of node before 'n2' is equal "before" (use 'strcmp(a,b) == 0')
  // TODO assert: check if value.name of node after 'n2' is equal "after" (use 'strcmp(a,b) == 0')

  list_delete(&list);

  return 0;
}