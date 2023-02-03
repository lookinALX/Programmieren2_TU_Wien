cmake_minimum_required(VERSION 3.16)

project(homework2 C)

if(UNIX)
    add_compile_options(-std=c11)
    add_compile_options(-Werror -Wall -pedantic)
    add_compile_options(-fsanitize=address)
    add_compile_options(-Wno-unused-variable)
    add_compile_options(-Wno-unused-function)
    add_compile_options(-Wno-error=return-type)
    add_link_options(-fsanitize=address)
endif(UNIX)

add_library(Vector OBJECT src/Vector.c include/Vector.h src/numerics.c include/numerics.h)
target_include_directories(Vector PUBLIC include)

enable_testing()

option(TEST_VECTOR "enable tests for Vector" OFF)
if(TEST_VECTOR)
    add_subdirectory(test_vector)
endif(TEST_VECTOR)
add_subdirectory(test)
