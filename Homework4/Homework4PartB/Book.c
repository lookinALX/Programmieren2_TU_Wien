#include "Book.h"
#include "Hash.h"
#include <stdbool.h> // bool
#include <stddef.h>  // size_t
#include <string.h>  // strlen
#include <stdio.h>   // printf

size_t book_hash_title(const struct Book *book)
{
  return FNV1_64(book->title, strlen(book->title));
}

bool book_compare_title(const struct Book *book1, const struct Book *book2)
{
  return !strcmp(book1->title, book2->title);
}

void book_print(const struct Book *book)
{
  printf("%i;%s;%s;%i;%i\n", book->id, book->title, book->author, book->year,
         book->pages);
}
