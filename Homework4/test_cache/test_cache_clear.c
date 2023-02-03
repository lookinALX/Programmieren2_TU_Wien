#include "Cache.h"
#include "Book.h"
#include "Logger.h"

#include <assert.h>  // assert
#include <stdbool.h> // bool
#include <stdio.h>   // sprinf

int main()
{

  size_t size = 100;
  double max_load_factor = 0.75;

  struct Cache *cache =
      cache_new(size, max_load_factor, book_hash_title, book_compare_title);

  for (size_t n = 10; n != 100; ++n)
  {
    struct Book book = {n, "TitleX", "Author1", n, n};
    sprintf(book.title, "Title %li", n);
    sprintf(book.author, "Author %li", n);
    bool res = cache_insert(cache, &book);
  }

  cache_print(cache, book_print);

  cache_clear(cache);

  assert(cache->count == 0);

  cache_delete(&cache);

  assert(cache == NULL);

  return 0;
}
