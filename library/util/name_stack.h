#pragma once

#include <string>
#include <vector>

namespace autotest {
namespace util {

struct name_stack
{
  void push( std::string name );
  void pop( );

  const std::string& top( ) const;
  size_t size( ) const;
  bool empty( ) const;

  std::string get_full_name( const char* delimiter ) const;

private:
  std::vector<std::string> names_;
};

} // namespace util
} // namespace autotest
