cmake_minimum_required (VERSION 3.4.0)
project (autotest)

set (CMAKE_CXX_STANDARD 11)

set (SOURCES 
     util/name_stack.cpp
     util/timer.cpp
		 check/check_broker.cpp
		 test/invoking_visitor.cpp
		 test/listing_visitor.cpp
		 test/test_broker.cpp
		 test/test_case.cpp
		 test/test_status.cpp
		 test/test_suite_visitor.cpp
		 test/test_suite.cpp
		 )
		 
add_library(${PROJECT_NAME} ${SOURCES})
