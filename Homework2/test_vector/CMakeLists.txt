cmake_minimum_required(VERSION 3.16)

add_executable(test_init_free test_init_free.c)
target_link_libraries(test_init_free Vector)
add_test(NAME test_init_free COMMAND test_init_free)

add_executable(test_new_delete test_new_delete.c)
target_link_libraries(test_new_delete Vector)
add_test(NAME test_new_delete COMMAND test_new_delete)

add_executable(test_reserve_shrink test_reserve_shrink.c)
target_link_libraries(test_reserve_shrink Vector)
add_test(NAME test_reserve_shrink COMMAND test_reserve_shrink)

add_executable(test_push_pop_back test_push_pop_back.c)
target_link_libraries(test_push_pop_back Vector)
add_test(NAME test_push_pop_back COMMAND test_push_pop_back)

add_executable(test_push_pop_front test_push_pop_front.c)
target_link_libraries(test_push_pop_front Vector)
add_test(NAME test_push_pop_front COMMAND test_push_pop_front)

add_executable(test_reverse test_reverse.c)
target_link_libraries(test_reverse Vector)
add_test(NAME test_reverse COMMAND test_reverse)

add_executable(test_erase test_erase.c)
target_link_libraries(test_erase Vector)
add_test(NAME test_erase COMMAND test_erase)

add_executable(test_insert_before test_insert_before.c)
target_link_libraries(test_insert_before Vector)
add_test(NAME test_insert_before COMMAND test_insert_before)




