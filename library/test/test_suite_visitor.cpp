#include "test_suite_visitor.h"
#include "test_suite.h"

#define TEST_INLINE

namespace autotest {
namespace tree {

TEST_INLINE void test_suite_visitor::test_suite_start( test_suite& test_suite )
{
  names_.push( test_suite.get_name( ) );
  auto path = names_.get_full_name( "/" );
  match_results_.push( matcher_( path ) );

  if ( match_results_.top( ) == matcher_t::NO_MATCH ) return;

  test_suite_start_impl( test_suite );
  level_++;
}

TEST_INLINE void test_suite_visitor::test_suite_end( test_suite& test_suite )
{
  for ( auto & suite : test_suite.get_suites( ) )
  {
    suite.accept( *this );
  }

  names_.pop( );
  auto last_match = match_results_.top( );
  match_results_.pop( );

  if ( last_match == matcher_t::NO_MATCH ) return;

  level_--;
  test_suite_end_impl( test_suite );
}

TEST_INLINE void test_suite_visitor::visit( test_cases& test_cases )
{
  if ( match_results_.top( ) == matcher_t::FULL_MATCH )
  {
    visit_impl( test_cases );
  }
}

} // namespace tree
} // namespace autotest
