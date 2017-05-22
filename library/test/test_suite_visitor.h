#pragma once

#include "matcher.h"
#include "../util/name_stack.h"

#include <stack>

namespace autotest {
namespace tree {

struct test_suite;
struct test_case;
using test_cases = std::vector<test_case>;

struct test_suite_visitor
{
  test_suite_visitor( matcher_t && matcher ) :
          matcher_( std::move( matcher ) )
  {
  }

  virtual ~test_suite_visitor( ) = default;
  void test_suite_start( test_suite& test_suite );
  void test_suite_end( test_suite& test_suite );
  void visit( test_cases& test_cases );

protected:
  virtual void test_suite_start_impl( test_suite& ) { }
  virtual void test_suite_end_impl( test_suite& ) { }
  virtual void visit_impl( test_cases& test_cases ) = 0;

  size_t level_ = 0;
  util::name_stack names_;
  matcher_t matcher_;
  std::stack<matcher_t::match_result_t> match_results_;
};

} // namespace tree
} // namespace autotest
