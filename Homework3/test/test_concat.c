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

  struct List *clone = list_clone(list);
  struct ListNode *cloneN1 = list_node_at(clone, 0);
  struct ListNode *cloneN2 = list_node_at(clone, 1);
  struct ListNode *cloneN3 = list_node_at(clone, 2);

  list_print(clone);

  list_concat(list, clone);

  assert(list_size(list) == 6);
  assert(list_size(clone) == 0);

  assert(cloneN1 == list_node_at(list, 3));
  assert(cloneN2 == list_node_at(list, 4));
  assert(cloneN3 == list_node_at(list, 5));

  list_delete(&list);

  list_delete(&clone);

  return 0;
}
