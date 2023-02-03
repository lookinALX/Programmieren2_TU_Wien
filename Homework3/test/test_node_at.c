#include "List.h"

#include <assert.h> // assert
#include <string.h>  // strcmp

int main()
{

  struct List *list = list_new();

  list_push_back(list, &(T){.name = "N1"});
  list_push_back(list, &(T){.name = "N2"});
  list_push_back(list, &(T){.name = "N3"});

  list_print(list);

  struct ListNode *node = list_node_at(list,2);

  assert(!strcmp(node->value.name, "N3"));

  list_print(list);

  list_delete(&list);

  return 0;
}
