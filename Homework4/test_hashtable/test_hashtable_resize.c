#include "HashTable.h"
#include "Book.h"
#include "Logger.h"

#include <assert.h>  // assert
#include <stdbool.h> // bool
#include <stdio.h>   // sprinf

int main()
{

  size_t size = 10;
  double max_load_factor = 0.75;

  struct HashTable *table =
      hashtable_new(size, max_load_factor, book_hash_title, book_compare_title);

  assert(table->size == size);
  assert(table->count == 0);

  struct Book book = {1, "Title X", "Author X", 2001, 101};

  for (size_t n = 0; n != 10; ++n)
  {
    sprintf(book.title, "Title %li", n);
    assert(hashtable_insert(table, &book));
  }

  hashtable_print(table, book_print);

  assert(table->count == 10);

  hashtable_resize(table, 100);

  assert(table->size == 100);
  assert(table->count == 10);

  for (size_t n = 0; n != 10; ++n)
  {
    sprintf(book.title, "Title %li", n);
    assert(hashtable_find(table, &book));
  }

  hashtable_delete(&table);

  assert(table == NULL);

  return 0;
}
