#include "timer.h"

namespace autotest {
namespace util {

Timer::Timer( ) :
        reference_( clock::now( ) )
{
}

void Timer::tic( )
{
  reference_ = clock::now( );
}

double Timer::toc( )
{
  auto now = clock::now( );
  std::chrono::duration<double> diff = now - reference_;
  return diff.count( );
}

} // namespace util
} // namespace autotest
