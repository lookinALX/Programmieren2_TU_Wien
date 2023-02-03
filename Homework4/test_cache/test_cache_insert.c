#include "Cache.h"
#include "Book.h"
#include "Logger.h"

#include <assert.h>  // assert
#include <stdbool.h> // bool
#include <stdio.h>   // sprinf

int main()
{

  size_t size = 20;
  double max_load_factor = 0.75;

  struct Cache *cache =
      cache_new(size, max_load_factor, book_hash_title, book_compare_title);

  struct Book book = {1, "Title X", "Author X", 2001, 101};
  {
    bool res = cache_insert(cache, &book);
    assert(res == true);
  }
  {
    bool res = cache_insert(cache, &book);
    assert(res == false);
  }

  for (size_t n = 0; n != 100; ++n)
  {
    sprintf(book.title, "Title %li", n);
    bool res = cache_insert(cache, &book);
    assert((cache->count - 1) / (double)cache->size <= max_load_factor);
  }

  cache_print(cache, book_print);

  cache_delete(&cache);

  assert(cache == NULL);

  return 0;
}
