#pragma once

#include "test_status.h"
#include "../check/check_result.h"
#include "../util/location.h"

#include <functional>
#include <string>

namespace autotest {
namespace tree {

using callback_t = std::function<void()>;

struct test_case
{
  test_case( std::string name,
            callback_t invoker,
            test_status_t status,
            util::Location location );

  const std::string& get_name( ) const;
  const util::Location& get_location( ) const;
  void run( );
  const check::check_results& get_results( ) const;
  test_status_e get_status( );

private:
  std::string name_;
  callback_t invoker_;
  test_status_t status_;
  util::Location location_;
  double duration_;
  check::check_results checks_;
};

} // namespace tree
} // namespace autotest
