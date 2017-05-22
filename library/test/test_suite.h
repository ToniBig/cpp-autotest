#pragma once

#include <string>
#include <vector>

namespace autotest {
namespace tree {

struct test_suite;
struct test_case;
struct test_suite_visitor;

using test_suites = std::vector<test_suite>;
using test_cases = std::vector<test_case>;
using test_suite_ptr = test_suite *;

struct test_suite
{
  test_suite( std::string name );

  const std::string& get_name( ) const;
  bool add_test( test_case test_case );
  test_suite_ptr get_suite( const std::string& name );
  test_suites& get_suites( );
  void accept( test_suite_visitor& visitor );

private:
  std::string name_;
  test_suites suites_;
  test_cases cases_;
};

} // namespace tree
} // namespace autotest
