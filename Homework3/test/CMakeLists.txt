cmake_minimum_required(VERSION 3.16)

add_executable(test_new_delete test_new_delete.c)
target_link_libraries(test_new_delete List)
add_test(NAME test_new_delete COMMAND test_new_delete)

add_executable(test_clear_size test_clear_size.c)
target_link_libraries(test_clear_size List)
add_test(NAME test_clear_size COMMAND test_clear_size)

add_executable(test_node_at test_node_at.c)
target_link_libraries(test_node_at List)
add_test(NAME test_node_at COMMAND test_node_at)

add_executable(test_push_back_pop_back test_push_back_pop_back.c)
target_link_libraries(test_push_back_pop_back List)
add_test(NAME test_push_back_pop_back COMMAND test_push_back_pop_back)

add_executable(test_find test_find.c)
target_link_libraries(test_find List)
add_test(NAME test_find COMMAND test_find)

add_executable(test_concat test_concat.c)
target_link_libraries(test_concat List)
add_test(NAME test_concat COMMAND test_concat)

add_executable(test_clone test_clone.c)
target_link_libraries(test_clone List)
add_test(NAME test_clone COMMAND test_clone)

add_executable(test_reverse test_reverse.c)
target_link_libraries(test_reverse List)
add_test(NAME test_reverse COMMAND test_reverse)

