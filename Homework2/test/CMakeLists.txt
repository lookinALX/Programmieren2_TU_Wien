cmake_minimum_required(VERSION 3.16)

add_executable(test_linspace test_linspace.c)
target_link_libraries(test_linspace Vector m)
add_test(NAME test_linspace COMMAND test_linspace)

add_executable(test_sample test_sample.c)
target_link_libraries(test_sample Vector m)
add_test(NAME test_sample COMMAND test_sample)

add_executable(test_interpolate test_interpolate.c)
target_link_libraries(test_interpolate Vector m)
add_test(NAME test_interpolate COMMAND test_interpolate)

add_executable(test_grad test_grad.c)
target_link_libraries(test_grad Vector m)
add_test(NAME test_grad COMMAND test_grad)

add_executable(test_integrate test_integrate.c)
target_link_libraries(test_integrate Vector m)
add_test(NAME test_integrate COMMAND test_integrate)
