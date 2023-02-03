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

  struct ListNode *listN1 = list_node_at(list, 0);
  struct ListNode *listN2 = list_node_at(list, 1);
  struct ListNode *listN3 = list_node_at(list, 2);

  list_reverse(list);

  assert(list_size(list) == 3);

  assert(listN1 == list_node_at(list, 2));
  assert(listN2 == list_node_at(list, 1));
  assert(listN3 == list_node_at(list, 0));

  list_delete(&list);


  return 0;
}
