cmake_minimum_required(VERSION 3.16)

project(List C)

if(UNIX)
    add_compile_options(-std=c11 -g)
    add_compile_options(-Werror -Wall -pedantic)
    add_compile_options(-fsanitize=address)
    add_compile_options(-Wno-unused-variable)
    add_compile_options(-Wno-unused-function)
    add_compile_options(-Wno-error=return-type)
    add_link_options(-fsanitize=address)
endif(UNIX)


add_library(List OBJECT src/List.c include/List.h)
target_include_directories(List PUBLIC include)


enable_testing()
add_subdirectory(test)