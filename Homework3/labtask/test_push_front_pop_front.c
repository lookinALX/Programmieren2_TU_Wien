#include "List.h"

#include <assert.h> // assert
#include <stdio.h>  // printf
#include <string.h> // strcmp
#include <stdlib.h> // malloc free

void list_pop_front(struct List *self)
{
  // TODO: implement
}

void list_push_front(struct List *self, const T *value)
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

  T front = {.name = "front"};

  // applying 'list_pop_front' pop first value again
  list_pop_front(list);
  list_print(list);

  // TODO: implement asserts to check expectations
  assert(false); // TODO: remove this failing assert
  // TODO assert: check if list has now size '2'
  // TODO assert: check if value.name of first element is now "N2" (use 'strcmp(a,b) == 0')

  // applying 'list_push_front' to push value 'front'
  list_push_front(list, &front);
  list_print(list);

  // TODO: implement asserts to check expectations
  assert(false); // TODO: remove this failing assertW
  // TODO assert: check if list has now again size '3' 
  // TODO assert: check if value.name of first element is no "front" (use 'strcmp(a,b) == 0')

  list_delete(&list);

  return 0;
}