#include "name_stack.h"
#include <iterator>
#include <sstream>

#define TEST_INLINE

namespace autotest {
namespace util {

TEST_INLINE void name_stack::push( std::string name )
{
  names_.emplace_back( std::move( name ) );
}

TEST_INLINE void name_stack::pop( )
{
  names_.pop_back( );
}

TEST_INLINE const std::string& name_stack::top( ) const
{
  return names_.back( );
}

TEST_INLINE size_t name_stack::size( ) const
{
  return names_.size( );
}

TEST_INLINE bool name_stack::empty( ) const
{
  return names_.empty( );
}

TEST_INLINE std::string name_stack::get_full_name( const char* delimiter ) const
{
  std::stringstream full_name;

  std::copy( names_.begin( ), names_.end( ), std::ostream_iterator<const std::string&>( full_name, delimiter ) );

  return full_name.str( );
}

} // namespace util
} // namespace autotest
