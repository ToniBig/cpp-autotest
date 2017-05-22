#pragma once

#include "matcher.h"
#include "test_suite.h"
#include "options.h"

#include <functional>

namespace autotest {
namespace tree {

static const char master_suite_name[] = "master";

struct test_broker
{
  static tree::test_suite_ptr get_master_test_suite( );

  static void list_tests( std::string const & runner_name,
                          tree::matcher_t const & matcher = tree::matcher_t { } );

  static void run_tests( std::string const & runner_name,
                         tree::matcher_t const & matcher = tree::matcher_t { },
                         format_t format = format_t::PLAIN,
                         detail_t detail = detail_t::FAILURE );

  static void execute( int argc,
                       char ** argv );

private:
  test_broker( );

  static test_broker& get_instance( );

  tree::test_suite masterSuite_;
};

} // namespace tree
} // namespace autotest
