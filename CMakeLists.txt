cmake_minimum_required(VERSION 3.26)
project(ed)

enable_testing()

include(GoogleTest)
include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(bst_test test/bst.cpp)
target_link_libraries(bst_test gtest gtest_main)
gtest_add_tests(TARGET bst_test)

add_executable(avl_test test/avl.cpp)
target_link_libraries(avl_test gtest gtest_main)
gtest_add_tests(TARGET avl_test)

add_executable(set_test test/set.cpp)
target_link_libraries(set_test gtest gtest_main)
gtest_add_tests(TARGET set_test)

add_executable(map_test test/map.cpp)
target_link_libraries(map_test gtest gtest_main)
gtest_add_tests(TARGET map_test)
