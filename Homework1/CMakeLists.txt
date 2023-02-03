cmake_minimum_required(VERSION 3.20)

project(homework1 C)

add_compile_options(-std=c11)
add_compile_options(-Werror -Wall -pedantic)
add_compile_options(-fsanitize=address)
add_compile_options(-Wno-unused-variable)
add_compile_options(-Wno-unused-function)
add_compile_options(-Wno-error=return-type)
add_link_options(-fsanitize=address)


add_library(Vector OBJECT src/Vector.c include/Vector.h)
target_include_directories(Vector PUBLIC include)

enable_testing()
add_subdirectory(test)
