#include "List.h"

#include <assert.h> // assert
#include <string.h> // strcmp
#include <ctype.h>  // isdigit
#include <stdlib.h> // malloc/free

struct List *list_extract_if(struct List *src,
                             bool (*predicate)(const T *value))
{

  struct ListNode *node = src->entry->next;
  int size = list_size(src);
  for(int i = 0; i < size; i++){
    if(predicate(&(node->value)))
    {
        struct ListNode *node_tmp = node->next;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = NULL;
        node->next = NULL;
        free(node);
        node = node_tmp;
    }
    else{
      node = node->next;
    } 
  }
  return NULL;
}

bool str_starts_with_digit(const T *value)
{
  return isdigit(value->name[0]);
}

int main()
{

  struct List *list = list_new();

  list_push_back(list, &(T){.name = "AN1"});
  list_push_back(list, &(T){.name = "1N2"});
  list_push_back(list, &(T){.name = "BN3"});
  list_push_back(list, &(T){.name = "3N4"});

  list_print(list);

  list_extract_if(list,&str_starts_with_digit);
  list_print(list);

  list_delete(&list);

  return 0;
}
