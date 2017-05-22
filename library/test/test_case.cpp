#include "test_case.h"
#include "../check/check_broker.h"
#include "../check/required_check_exception.h"
#include "../util/timer.h"

#define TEST_INLINE

namespace autotest {
namespace tree {

TEST_INLINE test_case::test_case( std::string name,
                                  callback_t invoker,
                                  test_status_t status,
                                  util::Location location ) :
        name_( name ),
        invoker_( invoker ),
        status_( std::move( status ) ),
        location_( location ),
        duration_( 0.0 )
{
}

TEST_INLINE const std::string& test_case::get_name( ) const
{
  return name_;
}

TEST_INLINE void test_case::run( )
{
  check::check_broker::reset( );
  util::Timer timer;
  try
  {
    invoker_( );
  }
  catch ( check::required_check_failed_exception& e )
  {
  }
  duration_ = timer.toc( );
  checks_ = check::check_broker::get_results( );
}

TEST_INLINE const util::Location& test_case::get_location( ) const
{
  return location_;
}

TEST_INLINE test_status_e test_case::get_status( )
{
  return status_.get_status( );
}

TEST_INLINE const check::check_results& test_case::get_results( ) const
{
  return checks_;
}

} // namespace tree
} // namespace autotest
