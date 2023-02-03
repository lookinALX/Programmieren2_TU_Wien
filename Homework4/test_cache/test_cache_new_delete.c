#include "Cache.h"
#include "Book.h"
#include "Logger.h"

#include <assert.h> // assert

int main()
{

  size_t size = 11;
  double max_load_factor = 0.75;

  struct Cache *cache =
      cache_new(size, max_load_factor, book_hash_title, book_compare_title);

  assert(cache->size == size);
  assert(cache->max_load_factor == max_load_factor);
  assert(cache->count == 0);

  cache_delete(&cache);

  assert(cache == NULL);

  return 0;
}
