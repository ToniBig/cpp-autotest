#pragma once

#include <exception>

namespace autotest {
namespace check {

struct required_check_failed_exception : public std::exception
{
  const char* what( ) const noexcept
  {
    return "Required check failed: ";
  }
};

} // namespace check
} // namespace autotest
