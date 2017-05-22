#include "listing_visitor.h"
#include "test_suite.h"
#include "test_case.h"

#include <iostream>
#include <string>

#define TEST_INLINE

namespace autotest {
namespace tree {

TEST_INLINE void ListingVisitor::test_suite_start_impl( tree::test_suite& test_suite )
{
  std::cout << std::string( level_, '|' ) << "Entering test suite: " << test_suite.get_name( ) << std::endl;
}

TEST_INLINE void ListingVisitor::test_suite_end_impl( tree::test_suite& test_suite )
{
  std::cout << std::string( level_, '|' ) << "Leaving test suite: " << test_suite.get_name( ) << std::endl;
}

TEST_INLINE void ListingVisitor::visit_impl( tree::test_cases& test_cases )
{
  for ( const auto & test_case : test_cases )
  {
    std::cout << std::string( level_, '|' ) << "Test case: " << test_case.get_name( ) << std::endl;
  }
}

} // namespace tree
} // namespace autotest
