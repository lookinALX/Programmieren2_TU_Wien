#include "HashTable.h"
#include "Book.h"
#include "Logger.h"

#include <assert.h>  // assert
#include <stdbool.h> // bool
#include <stdio.h>   // sprinf
#include <string.h>  // strcmp

int main()
{

  size_t size = 100;
  double max_load_factor = 0.75;

  struct HashTable *table =
      hashtable_new(size, max_load_factor, book_hash_title, book_compare_title);

  {
    struct Book book = {1, "Title One", "Author1", 2001, 101};
    bool res = hashtable_insert(table, &book);
    assert(res == true);
  }
  {
    struct Book book = {2, "Title Two", "Author2", 2002, 102};
    bool res = hashtable_insert(table, &book);
    assert(res == true);
  }
  {
    struct Book book = {3, "Title Three", "Author3", 2003, 102};
    bool res = hashtable_insert(table, &book);
    assert(res == true);
  }

  hashtable_print(table, book_print);

  {
    struct Book book = {0, "Title Three", "", 0, 0};
    struct Book *res = hashtable_find(table, &book);
    assert(res != NULL);
    assert(res != &book);
    assert(!strcmp(res->title, "Title Three"));
    assert(!strcmp(res->author, "Author3"));
  }

  hashtable_delete(&table);

  assert(table == NULL);

  return 0;
}
