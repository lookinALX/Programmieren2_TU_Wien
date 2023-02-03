#include "HashTable.h"
#include "Book.h"

#include <assert.h>  // assert
#include <stdbool.h> // bool
#include <stdio.h>   // snprintf

bool hashtable_erase(struct HashTable *self, const T *value)
{
  size_t index = self->hash(value) % self->size;
  struct Node *cur_node = self->data[index].list;
  struct Node *prev_node = NULL;
  while (cur_node != NULL)
  {
    if (self->compare(&(cur_node->value), value))
    {
      if (prev_node == NULL)
      {
        self->count -= 1;
        self->data[index].list = cur_node->next;
        wrap_free(cur_node);
      }
      else
      {
        self->count -= 1;
        prev_node->next = cur_node->next;
        wrap_free(cur_node);
      }
      return true;
    }
    prev_node = cur_node;
    cur_node = cur_node->next;
  }
  return false;
}

int main()
{

  size_t size = 3;

  struct HashTable *table =
      hashtable_new(size, book_hash_title, book_compare_title);

  for (size_t n = 1; n <= 6; ++n)
  {
    struct Book bookn = {n, "", "", 2000 + n, 100 + n};
    snprintf(bookn.title, BOOK_TITLE_LENGTH, "Title %li", n);
    snprintf(bookn.author, BOOK_TITLE_LENGTH, "Author %li", n);
    bool res = hashtable_insert(table, &bookn);
    assert(res == true);
  }

  hashtable_print(table, book_print);
  assert(table->count == 6);

  {
    struct Book book1 = {0, "Title 2", "", 0, 0};
    bool res1 = hashtable_erase(table, &book1);
    assert(res1 == true);
    bool res2 = hashtable_erase(table, &book1);
    assert(res2 == false);
  }

  hashtable_print(table, book_print);
  assert(table->count == 5);

  struct Book book7 = {7, "Title 7", "Author 7", 2007, 107};
  bool res = hashtable_insert(table, &book7);
  assert(res == true);

  hashtable_print(table, book_print);

  {
    struct Book book7 = {0, "Title 7", "0", 0, 0};
    bool res1 = hashtable_erase(table, &book7);
    assert(res1 == true);
    bool res2 = hashtable_erase(table, &book7);
    assert(res2 == false);
  }

  hashtable_print(table, book_print);
  hashtable_info(table);
  assert(table->count == 5);

  hashtable_delete(&table);

  return 0;
}
