#include "List.h"

#include <assert.h> // assert

int main()
{

  struct List *list = list_new();

  assert(list->entry->next == list->entry);
  assert(list->entry->prev == list->entry);

  list_delete(&list);

  assert(list == NULL);

  return 0;
}
