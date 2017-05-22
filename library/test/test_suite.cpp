#include "test_suite.h"
#include "test_case.h"
#include "test_suite_visitor.h"

#include <algorithm>

#define TEST_INLINE

namespace autotest {
namespace tree {

TEST_INLINE test_suite::test_suite( std::string name ) :
        name_( std::move( name ) )
{
}

TEST_INLINE const std::string& test_suite::get_name( ) const
{
  return name_;
}

TEST_INLINE bool test_suite::add_test( test_case test_case )
{
  cases_.emplace_back( std::move( test_case ) );

  return true;
}

TEST_INLINE tree::test_suite_ptr test_suite::get_suite( const std::string& name )
{
  auto search = std::find_if( suites_.begin( ), suites_.end( ), [&name](test_suite& suite)
  {
    return suite.get_name() == name;
  } );

  if ( search != suites_.end( ) )
  {
    return &*search;
  }
  else
  {
    suites_.emplace_back( name );
    return &suites_.back( );
  }
}

TEST_INLINE test_suites& test_suite::get_suites( )
{
  return suites_;
}

TEST_INLINE void test_suite::accept( tree::test_suite_visitor& visitor )
{
  visitor.test_suite_start( *this );
  visitor.visit( cases_ );
  visitor.test_suite_end( *this );
}

} // namespace tree
} // namespace autotest
