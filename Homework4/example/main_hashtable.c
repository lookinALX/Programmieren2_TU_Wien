#include "HashTable.h"
#include "Book.h"

#include <assert.h> // assert
#include <stdio.h>  // FILE
#include <string.h> // strcspn

static int load_books(const char *filename, struct HashTable *table,
                      int (*deserialize)(const char[], struct Book *book))
{
  static char buffer[BOOK_TITLE_LENGTH + BOOK_AUTHOR_LENGTH + 128];
  FILE *stream = fopen(filename, "r");
  int reads = 0;
  int duplicates = 0;
  if (stream != NULL)
  {
    while (!feof(stream))
    {
      if (fgets(buffer, BOOK_TITLE_LENGTH + BOOK_AUTHOR_LENGTH + 128, stream) ==
          NULL)
        break;
      buffer[strcspn(buffer, "\n")] = '\0';
      struct Book book;
      if (deserialize(buffer, &book))
        break;
      if (!hashtable_insert(table, &book))
      {
        ++duplicates;
        // printf("### duplicate: \"%s\" \n", book.title);
      }
      ++reads;
    }
    fclose(stream);
  }
  printf("num duplicates: %i\n", duplicates);
  return reads;
}

int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    printf("missing input file.\n usage example: ./main_hashtable "
           "programming_books_100.txt\n");
    return -1;
  }

  size_t size = 20;
  double max_load_factor = 0.75;

  struct HashTable *table =
      hashtable_new(size, max_load_factor, book_hash_title, book_compare_title);

  {
    int res = load_books(argv[1], table, book_deserialize);
    printf("parsed %i books from file %s .\n", res, argv[1]);
  }

  hashtable_print(table, book_print);
  hashtable_info(table);

  hashtable_delete(&table);

  return 0;
}
