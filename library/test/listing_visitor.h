#pragma once

#include "test_suite_visitor.h"

namespace autotest {
namespace tree {

struct ListingVisitor : tree::test_suite_visitor
{
  ListingVisitor( tree::matcher_t matcher ) :
          tree::test_suite_visitor( std::move( matcher ) )
  {
  }

  void test_suite_start_impl( tree::test_suite& test_suite ) override;
  void test_suite_end_impl( tree::test_suite& test_suite ) override;
  void visit_impl( tree::test_cases& test_cases ) override;
};

} // namespace tree
} // namespace autotest
