#pragma once

#include <cstddef>

namespace autotest {
namespace util {

struct Location
{
  const char* file;
  size_t line;
};

} // namespace util
} // namespace autotest
