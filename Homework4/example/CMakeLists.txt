cmake_minimum_required(VERSION 3.16)

add_executable(main_cache main_cache.c)
target_link_libraries(main_cache Cache)

add_executable(main_hashtable main_hashtable.c)
target_link_libraries(main_hashtable HashTable)


configure_file(programming_books_10.txt programming_books_10.txt COPYONLY)
configure_file(programming_books_100.txt programming_books_100.txt COPYONLY)
configure_file(programming_books_7142.txt programming_books_7142.txt COPYONLY)
