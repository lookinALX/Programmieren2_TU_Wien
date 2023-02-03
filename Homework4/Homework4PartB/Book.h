#pragma once

#include <stdbool.h> // bool
#include <stddef.h>  // size_t

#define BOOK_TITLE_LENGTH 512
#define BOOK_AUTHOR_LENGTH 512

// {ID};{TITLE};{AUTHOR};{YEAR};{PAGES}

struct Book {
  int id;
  char title[BOOK_TITLE_LENGTH]; 
  char author[BOOK_AUTHOR_LENGTH];
  int year;
  int pages;
};

size_t book_hash_title(const struct Book *book);

bool book_compare_title(const struct Book *book1, const struct Book *book2);

void book_print(const struct Book *book);
