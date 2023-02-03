cmake_minimum_required(VERSION 3.16)

project(Labor3 C)

if(UNIX)
    add_compile_options(-std=c11 -g)
    add_compile_options(-Werror -Wall -pedantic)
    add_compile_options(-fsanitize=address)
    add_compile_options(-Wno-unused-variable)
    add_compile_options(-Wno-unused-function)
    add_compile_options(-Wno-error=return-type)
    add_link_options(-fsanitize=address)
endif(UNIX)


add_library(List OBJECT ../src/List.c ../include/List.h)
target_include_directories(List PUBLIC ../include)

enable_testing()

add_executable(test_push_front_pop_front test_push_front_pop_front.c)
target_link_libraries(test_push_front_pop_front List)
add_test(NAME test_push_front_pop_front COMMAND test_push_front_pop_front)

add_executable(test_insert_before_insert_after test_insert_before_insert_after.c)
target_link_libraries(test_insert_before_insert_after List)
add_test(NAME test_insert_before_insert_after COMMAND test_insert_before_insert_after)
