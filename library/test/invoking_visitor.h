#pragma once

#include "test_suite_visitor.h"
#include "options.h"

#include <sstream>

namespace autotest {
namespace tree {

struct InvokingVisitor : tree::test_suite_visitor
{
  InvokingVisitor( tree::matcher_t matcher,
                   format_t format,
                   detail_t detail ) :
          tree::test_suite_visitor( std::move( matcher ) ),
          format_( format ),
          detail_( detail )
  {
  }

  size_t passed_test_count = 0;
  size_t failed_test_count = 0;
  size_t skipped_test_count = 0;
  size_t passed_assertion_count = 0;
  size_t failed_assertion_count = 0;

  void visit_impl( tree::test_cases& test_cases ) override;

  std::string summary( );

private:
  std::stringstream result_;
  format_t format_;
  detail_t detail_;
};

} // namespace tree
} // namespace autotest
