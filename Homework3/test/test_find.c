#include "List.h"

#include <assert.h> // assert
#include <string.h> // strcmp

bool findN3(const T *value)
{
  return (strcmp(value->name, "N3") == 0);
}

bool findN4(const T *value)
{
  return (strcmp(value->name, "N4") == 0);
}

int main()
{

  struct List *list = list_new();

  list_push_back(list, &(T){.name = "N1"});
  list_push_back(list, &(T){.name = "N2"});
  list_push_back(list, &(T){.name = "N3"});
  list_push_back(list, &(T){.name = "N2"});
  list_push_back(list, &(T){.name = "N3"});

  list_print(list);

  struct ListNode *start = list->entry->next;
  struct ListNode *end = list->entry;
  {
    struct ListNode *res = list_find(start, end, findN3);
    assert(res == list_node_at(list, 2));
  }

  {
    struct ListNode *res = list_find(start, end, findN4);
    assert(res == end);
  }

  list_delete(&list);

  return 0;
}
