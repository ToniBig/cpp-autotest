cmake_minimum_required (VERSION 2.8.0)
project (test_with_multiple_files)

add_executable(${PROJECT_NAME} main_test.cpp foo_test.cpp bar_test.cpp)
target_link_libraries(${PROJECT_NAME} autotest)
