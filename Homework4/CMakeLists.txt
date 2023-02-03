cmake_minimum_required(VERSION 3.16)

project(homework4 C)

if(UNIX)
    add_compile_options(-std=c11 -g)
    add_compile_options(-Werror -Wall -pedantic)
    add_compile_options(-fsanitize=address)
    add_compile_options(-Wno-unused-variable)
    add_compile_options(-Wno-unused-function)
    add_compile_options(-Wno-error=return-type)
    add_link_options(-fsanitize=address)
endif(UNIX)


add_library(Cache OBJECT src/Cache.c src/Book.c src/Logger.c)
add_library(HashTable OBJECT src/HashTable.c src/Book.c src/Logger.c)
target_include_directories(Cache PUBLIC include)
target_include_directories(HashTable PUBLIC include)

enable_testing()
add_subdirectory(test_cache)
add_subdirectory(test_hashtable)

add_subdirectory(example)
