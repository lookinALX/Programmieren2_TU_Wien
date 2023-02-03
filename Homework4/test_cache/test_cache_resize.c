#include "Cache.h"
#include "Book.h"
#include "Logger.h"

#include <assert.h>  // assert
#include <stdbool.h> // bool
#include <stdio.h>   // sprinf

int main()
{

  size_t size = 10;
  double max_load_factor = 0.75;

  struct Cache *cache =
      cache_new(size, max_load_factor, book_hash_title, book_compare_title);

  assert(cache->size == size);
  assert(cache->count == 0);  

  struct Book book = {1, "Title1", "Author1", 2001, 101};

  bool res = cache_insert(cache, &book);
  assert(res == true);

  cache_print(cache, book_print);

  cache_resize(cache, 100);
  assert(cache->size == 100);
  assert(cache->count == 1);      

  assert(cache_find(cache, &book));

  cache_delete(&cache);

  assert(cache == NULL);

  return 0;
}
