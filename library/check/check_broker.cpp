#include "check_broker.h"

namespace autotest {
namespace check {

const check::check_results& check_broker::get_results( )
{
  return get_instance( ).check_results_;
}

void check_broker::reset( )
{
  get_instance( ).check_results_.clear( );
}

void check_broker::add_result( const check::check_result& result )
{
  get_instance( ).check_results_.push_back( result );
}

check_broker& check_broker::get_instance( )
{
  static check_broker instance;
  return instance;
}

} // namespace check
} // namespace autotest
