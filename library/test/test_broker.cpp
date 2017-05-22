#include "test_broker.h"
#include "test_case.h"
#include "listing_visitor.h"
#include "invoking_visitor.h"

#include <algorithm>
#include <iostream>
#include <string>

#define TEST_INLINE

namespace autotest {
namespace tree {

TEST_INLINE test_broker& test_broker::get_instance( )
{
  static test_broker instance; // Meyers Singleton
  return instance;
}

TEST_INLINE void test_broker::list_tests( std::string const & runner_name,
                                          tree::matcher_t const & matcher )
{
  std::cout << std::string( 100, '=' ) << std::endl;
  std::cout << "Listing tests for" << runner_name << std::endl;
  std::cout << std::string( 100, '-' ) << std::endl;
  ListingVisitor visitor { matcher };
  get_instance( ).masterSuite_.accept( visitor );
  std::cout << std::string( 100, '=' ) << std::endl;
}

static std::pair<std::string, std::string> get_key_value_pair( std::string const & token )
{
  std::string key { };
  std::string value { };

  auto pivot = token.find( '=' );

  if ( pivot != std::string::npos )
  {
    value = token.substr( pivot + 1 );
  }

  key = token.substr( 0, pivot );

  return std::make_pair( key, value );
}

void fail( const std::string & key_name,
           const std::string& value )
{
  std::cout << "ERROR: " << key_name << " \"" << value << "\" is not defined" << std::endl;
  std::exit( 1 );
}

static void exit_if_key_not_valid( std::string const & key )
{
  std::string valid_keys[] = { "--list", "--run", "--format", "--detail" };
  auto iter = std::find( std::begin( valid_keys ), std::end( valid_keys ), key );

  if ( iter != std::end( valid_keys ) ) return;

  fail( "Key", key );
}

format_t get_format( std::string const & value )
{
  if ( value == "plain" ) return format_t::PLAIN;
  if ( value == "xml" ) return format_t::XML;
  fail( "Format", value );
  return format_t::PLAIN;
}

detail_t get_detail( std::string const & value )
{
  if ( value == "failure" ) return detail_t::FAILURE;
  if ( value == "all" ) return detail_t::ALL;
  fail( "Detail", value );
  return detail_t::FAILURE;
}

TEST_INLINE void test_broker::execute( int argc,
                                       char ** argv )
{
  std::string runner_name { argv[0] };

  if ( argc == 1 ) // No extra arguments
  {
    run_tests( runner_name, tree::matcher_t { } );
    return;
  }

  std::vector < std::string > arguments;
  arguments.reserve( argc );

  action_t action = action_t::RUN;
  format_t format = format_t::PLAIN;
  detail_t detail = detail_t::FAILURE;

  std::string root = master_suite_name;

  std::string key;
  std::string value;

  tree::matcher_t matcher;

  for ( int i = 1; i < argc; ++i )
  {
    std::string current { argv[i] };
    std::tie( key, value ) = get_key_value_pair( current );

    exit_if_key_not_valid( key );

    if ( key == "--run" ) action = action_t::RUN;
    if ( key == "--list" ) action = action_t::LIST;

    if ( key == "--format" ) format = get_format( value );
    if ( key == "--detail" ) detail = get_detail( value );

    matcher = tree::matcher_t( value );

  } // end of i-loop

  switch ( action )
  {
  case action_t::RUN:
  {
    run_tests( runner_name, matcher, format, detail );
  }
    break;
  case action_t::LIST:
  {
    list_tests( runner_name, matcher );
  }
    break;
  default:
    break;
  }

}

TEST_INLINE void test_broker::run_tests( std::string const & runner_name,
                                         tree::matcher_t const & matcher,
                                         format_t format,
                                         detail_t detail )
{
  std::cout << "Running tests for " << runner_name << std::endl;
  std::cout << std::string(100,'-') << "\n";

  InvokingVisitor visitor { matcher, format, detail };
  get_instance( ).masterSuite_.accept( visitor );
  std::cout << visitor.summary( );
}

TEST_INLINE tree::test_suite_ptr test_broker::get_master_test_suite( )
{
  return &get_instance( ).masterSuite_;
}

TEST_INLINE test_broker::test_broker( ) :
        masterSuite_( master_suite_name )
{
}

} // namespace tree
} // namespace autotest
