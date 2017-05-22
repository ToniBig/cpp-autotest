#pragma once

#include <iostream>
#include <csignal>

namespace autotest {
namespace util {

struct signal_handler_t
{

  static void signal_handler( int )
  {
    auto& checkpoint_location = get_instance( ).checkpoint_location;

    std::cout << "Segmentation fault detected! Last checkpoint: ";
    std::cout << checkpoint_location.file << "(" << checkpoint_location.line << ")" << std::endl;

    std::exit (EXIT_FAILURE);
  }

  static void set_checkpoint_location( const util::Location& location )
  {
    auto& checkpoint_location = get_instance( ).checkpoint_location;
    checkpoint_location = location;
  }

  static bool initialize( )
  {
    get_instance( );

    return true;
  }

private:
  signal_handler_t( ) :
          checkpoint_location { "...", 0 }
  {
    std::signal( SIGSEGV, signal_handler );
  }

  static signal_handler_t& get_instance( )
  {
    static signal_handler_t instance;
    return instance;
  }

  util::Location checkpoint_location;
};

} // namespace util
} // namespace autotest

