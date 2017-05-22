#pragma once

#include "check_result.h"

namespace autotest {
namespace check {

struct check_broker
{
  static const check::check_results& get_results( );

  static void reset( );

  static void add_result( const check::check_result& result );

private:
  check_broker( ) = default;

  static check_broker& get_instance( );

  check::check_results check_results_;
};

} // namespace check
} // namespace autotest
