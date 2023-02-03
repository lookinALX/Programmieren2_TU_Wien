#include "List.h"

#include <assert.h> // assert
#include <stdio.h>  // printf

int main()
{

  struct List *list = list_new();

  list_push_back(list, &(T){.name = "N1"});
  list_push_back(list, &(T){.name = "N2"});
  list_push_back(list, &(T){.name = "N3"});

  list_print(list);

  assert(list_size(list) == 3);

  list_clear(list);

  list_print(list);

  assert(list_size(list) == 0);
  assert(list->entry->next == list->entry);
  assert(list->entry->prev == list->entry);  

  list_delete(&list);

  return 0;
}
