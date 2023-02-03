#include "List.h"

#include <assert.h> // assert
#include <string.h> // strcmp

int main()
{

  struct List *list = list_new();

  list_push_back(list, &(T){.name = "N1"});
  list_push_back(list, &(T){.name = "N2"});
  list_push_back(list, &(T){.name = "N3"});

  list_print(list);

  assert(list_size(list) == 3);

  struct List *clone = list_clone(list);

  list_print(clone);

  assert(list_size(clone) == list_size(list));
  assert(list->entry != clone->entry);

  assert(list_node_at(clone, 0) != list_node_at(list, 0));
  assert(list_node_at(clone, 1) != list_node_at(list, 1));
  assert(list_node_at(clone, 2) != list_node_at(list, 2));

  assert(!strcmp(list_node_at(clone, 0)->value.name,
                list_node_at(list, 0)->value.name));
  assert(!strcmp(list_node_at(clone, 1)->value.name,
                list_node_at(list, 1)->value.name));
  assert(!strcmp(list_node_at(clone, 2)->value.name,
                list_node_at(list, 2)->value.name));

  list_delete(&list);
  list_delete(&clone);  

  return 0;
}
