#include "List.h"

#include <assert.h> // assert
#include <string.h>  // strcmp

int main()
{

  struct List *list = list_new();

  list_push_back(list, &(T){.name = "N1"});
  assert(!strcmp(list->entry->prev->value.name, "N1"));
  list_push_back(list, &(T){.name = "N2"});
  assert(!strcmp(list->entry->prev->value.name, "N2"));
  list_push_back(list, &(T){.name = "N3"});
  assert(!strcmp(list->entry->prev->value.name, "N3"));

  list_print(list);

  assert(list_size(list) == 3);

  list_pop_back(list);
  assert(!strcmp(list->entry->prev->value.name, "N2"));
  list_pop_back(list);
  assert(!strcmp(list->entry->prev->value.name, "N1"));
  list_pop_back(list);

  assert(list_size(list) == 0);

  list_print(list);

  list_delete(&list);

  return 0;
}
