#include "HashTable.h"
#include "Book.h"
#include "Logger.h"

#include <assert.h>  // assert
#include <stdbool.h> // bool
#include <stdio.h>   // sprinf

int main()
{

  size_t size = 20;
  double max_load_factor = 0.5;

  struct HashTable *table =
      hashtable_new(size, max_load_factor, book_hash_title, book_compare_title);

  struct Book book = {1, "TitleX", "AuthorX", 2001, 101};
  {
    bool res = hashtable_insert(table, &book);
    assert(res == true);
  }
  {
    bool res = hashtable_insert(table, &book);
    assert(res == false);
  }

  for (size_t n = 0; n != 30; ++n)
  {
    sprintf(book.title, "Title %li", n);
    bool res = hashtable_insert(table, &book);
    assert(res == true); 
    assert((table->count -1 ) / (double)table->size <= max_load_factor);
  }

  hashtable_print(table, book_print);

  assert(table->count == 31);

  hashtable_delete(&table);

  assert(table == NULL);

  return 0;
}
