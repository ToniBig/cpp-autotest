#pragma once

#include <chrono>

namespace autotest {
namespace util {

struct Timer
{
  Timer( );
  void tic( );
  double toc( );
private:
  using clock = std::chrono::high_resolution_clock;
  std::chrono::time_point<clock> reference_;
};

} // namespace util
} // namespace autotest
