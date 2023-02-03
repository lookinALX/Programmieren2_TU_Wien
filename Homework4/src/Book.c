#include "Book.h"
#include "Hashes.h"
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

int book_deserialize(const char *buffer, struct Book *book)
{
  char format[32];
  sprintf(format, "%%i;%%%i[^;];%%%i[^;];%%i;%%i", BOOK_TITLE_LENGTH - 1,
          BOOK_AUTHOR_LENGTH - 1);
  int read = sscanf(buffer, format, &book->id, book->title, book->author,
                    &book->year, &book->pages);
  return read != 5;
}
