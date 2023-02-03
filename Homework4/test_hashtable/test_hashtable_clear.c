#include "HashTable.h"
#include "Book.h"
#include "Logger.h"

#include <assert.h>  // assert
#include <stdbool.h> // bool
#include <stdio.h>   // sprinf

int main()
{

  size_t size = 100;
  double max_load_factor = 0.75;

  struct HashTable *table =
      hashtable_new(size, max_load_factor, book_hash_title, book_compare_title);

  for (size_t n = 10; n != 20; ++n)
  {
    struct Book book = {n, "Title X", "Author X", n, n};
    sprintf(book.title, "Title %li", n);
    sprintf(book.author, "Author %li", n);
    bool res = hashtable_insert(table, &book);
  }

  hashtable_print(table, book_print);

  hashtable_clear(table);

  assert(table->count == 0);

  hashtable_delete(&table);

  assert(table == NULL);

  return 0;
}
