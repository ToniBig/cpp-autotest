cmake_minimum_required (VERSION 2.8.0)
project (autotest_demo)

set (CMAKE_CXX_STANDARD 11)

include_directories(library)

add_subdirectory( library )
add_subdirectory( examples/test_with_multiple_files)