#include "HashTable.h"
#include "Book.h"
#include "Logger.h"

#include <assert.h> // assert

int main()
{

  size_t size = 11;
  double max_load_factor = 0.75;

  struct HashTable *table =
      hashtable_new(size, max_load_factor, book_hash_title, book_compare_title);

  assert(table->size == size);
  assert(table->max_load_factor == max_load_factor);
  assert(table->count == 0);

  hashtable_delete(&table);

  assert(table == NULL);

  return 0;
}
