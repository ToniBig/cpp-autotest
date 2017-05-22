#pragma once

#include <string>

namespace autotest {
namespace tree {

struct matcher_t
{
  enum match_result_t
  {
    NO_MATCH, PARTIAL_MATCH, FULL_MATCH
  };

  matcher_t( ) :
          has_pattern_( false ),
          pattern_( )
  {
  }

  matcher_t( std::string const & pattern ) :
          has_pattern_( pattern.empty( ) == false ),
          pattern_( pattern )

  {
    if ( pattern_.back( ) == '/' ) pattern_.pop_back( );
  }

  match_result_t operator()( std::string const & string )
  {
    if ( not has_pattern_ )
      return FULL_MATCH;
    else
    {
      return get_match( string );
    }
  }

  match_result_t get_match( const std::string& string )
  {
    match_result_t match { NO_MATCH };
    if ( pattern_.length( ) < string.length( ) )
    {
      auto iters = std::mismatch( pattern_.begin( ), pattern_.end( ), string.begin( ) );
      if ( iters.first == pattern_.end( ) ) match = FULL_MATCH;
    }
    else
    {
      auto iters = std::mismatch( string.begin( ), string.end( ), pattern_.begin( ) );
      if ( iters.first == string.end( ) ) match = PARTIAL_MATCH;
    }
    return match;
  }

private:
  bool has_pattern_;
  std::string pattern_;
};

} // namespace tree
} // namespace autotest
