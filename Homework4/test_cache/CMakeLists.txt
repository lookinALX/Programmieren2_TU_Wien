cmake_minimum_required(VERSION 3.16)

add_executable(test_cache_new_delete test_cache_new_delete.c)
target_link_libraries(test_cache_new_delete Cache)
add_test(NAME test_cache_new_delete COMMAND test_cache_new_delete)

add_executable(test_cache_insert test_cache_insert.c)
target_link_libraries(test_cache_insert Cache)
add_test(NAME test_cache_insert COMMAND test_cache_insert)

add_executable(test_cache_find test_cache_find.c)
target_link_libraries(test_cache_find Cache)
add_test(NAME test_cache_find COMMAND test_cache_find)

add_executable(test_cache_erase test_cache_erase.c)
target_link_libraries(test_cache_erase Cache)
add_test(NAME test_cache_erase COMMAND test_cache_erase)

add_executable(test_cache_clear test_cache_clear.c)
target_link_libraries(test_cache_clear Cache)
add_test(NAME test_cache_clear COMMAND test_cache_clear)

add_executable(test_cache_resize test_cache_resize.c)
target_link_libraries(test_cache_resize Cache)
add_test(NAME test_cache_resize COMMAND test_cache_resize)
