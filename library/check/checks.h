#pragma once

#include "../check/check_broker.h"
#include "../check/required_check_exception.h"

#include "../test/test_broker.h"
#include "../test/test_case.h"
#include "../test/registration.h"

#include "../util/signal.h"
#include "../util/stringify.h"

#include <cmath>
#include <sstream>

namespace autotest {
namespace check {
namespace detail {
static __attribute__((unused)) bool initializedSignalHandler = util::signal_handler_t::initialize( );
} // namespace detail

static void check_forward( bool passed,
                           const std::string& input,
                           const util::Location& location,
                           check::Severity severity )
{
  check::check_broker::add_result( { passed, input, location, severity } );

  util::signal_handler_t::set_checkpoint_location( location );

  if ( severity == check::Severity::REQUIRED and not passed )
  {
    throw check::required_check_failed_exception { };
  }
}

static void check_predicate( bool predicate,
                             const char* argument,
                             util::Location location,
                             check::Severity severity )
{
  std::stringstream stream;
  const char* equal = predicate ? "==" : "!=";

  stream << argument << " " << equal << " " << "true";

  check_forward( predicate, stream.str( ), location, severity );
}

template<typename T>
void check_equal( T lhs,
                  T rhs,
                  const char* lhs_argument,
                  const char* rhs_argument,
                  util::Location location,
                  check::Severity severity )
{
  std::stringstream stream;
  auto passed = lhs == rhs;
  const char* equal = passed ? "==" : "!=";

  stream << lhs_argument << "(" << lhs << ") " << equal << " " << rhs_argument << "(" << rhs << ")";

  check_forward( passed, stream.str( ), location, severity );
}

template<typename T>
void check_close( T lhs,
                  T rhs,
                  double tolerance,
                  const char* lhs_argument,
                  const char* rhs_argument,
                  util::Location location,
                  check::Severity severity )
{
  auto delta = std::abs( lhs - rhs );
  auto passed = delta < tolerance;
  std::stringstream stream;

  const char* status = passed ? "within" : "exceeds";
  const char* equal = passed ? "==" : "!=";

  stream << "difference(" << delta << ") ";
  stream << status << " tolerance(" << tolerance << "), ";
  stream << lhs_argument << "(" << lhs << ") " << equal << " " << rhs_argument << "(" << rhs << ")";

  check_forward( passed, stream.str( ), location, severity );
}

template<typename Callback>
void check_throws_impl( bool check_throw,
                        Callback callback,
                        const char* statement,
                        util::Location location,
                        check::Severity severity )
{
  bool throws = not check_throw;

  try
  {
    callback( );
  }
  catch ( ... )
  {
    throws = not throws;
  }

  std::stringstream stream;

  bool action_flag = throws;

  if ( not check_throw )
  {
    action_flag = not action_flag;
  }

  const char* action = action_flag ? "throws" : "does not throw";
  stream << "statement " << action << " an exception: " << statement;

  check_forward( throws, stream.str( ), location, severity );
}

template<typename Exception, typename Callback>
void check_throws_exception( Callback callback,
                             const char* statement,
                             const char* exception,
                             util::Location location,
                             check::Severity severity )
{
  bool throws = false;

  try
  {
    callback( );
  }
  catch ( Exception& e )
  {
    throws = true;
  }
  catch ( ... )
  {
  }

  std::stringstream stream;
  const char* action = throws ? "throws" : "does not throw";
  stream << "statement " << action << " an exception of type " << exception << ": " << statement;

  check_forward( throws, stream.str( ), location, severity );
}

} // namespace check
} // namespace autotest

/// -----------------------------------------------------------------
/// Check macros
/// -----------------------------------------------------------------

#define CHECK(predicate) \
  autotest::check::check_predicate(predicate, #predicate, autotest::util::Location{__FILE__, __LINE__}, autotest::check::Severity::CHECK)
#define CHECK_EQUAL(lhs, rhs) \
  autotest::check::check_equal(lhs, rhs, #lhs, #rhs, autotest::util::Location{__FILE__, __LINE__}, autotest::check::Severity::CHECK)
#define CHECK_CLOSE(lhs, rhs, tolerance) \
  autotest::check::check_close(lhs, rhs, tolerance, #lhs, #rhs, autotest::util::Location{__FILE__, __LINE__}, autotest::check::Severity::CHECK)
#define CHECK_THROWS_ANY(statement) \
  autotest::check::check_throws_impl(true, [&,this](){statement;}, #statement, autotest::util::Location{__FILE__, __LINE__}, autotest::check::Severity::CHECK)
#define CHECK_THROWS_NOT(statement) \
  autotest::check::check_throws_impl(false, [&,this](){statement;}, #statement, autotest::util::Location{__FILE__, __LINE__}, autotest::check::Severity::CHECK)
#define CHECK_THROWS_EXCEPTION(statement, exception) \
  autotest::check::check_throws_exception<exception>([&,this](){statement;}, #statement, #exception, autotest::util::Location{__FILE__, __LINE__}, autotest::check::Severity::CHECK)

/// -----------------------------------------------------------------
/// Require macros
/// -----------------------------------------------------------------

#define REQUIRE(predicate) \
  autotest::check::check_predicate(predicate, #predicate, autotest::util::Location{__FILE__, __LINE__}, autotest::check::Severity::REQUIRED)
#define REQUIRE_EQUAL(lhs, rhs) \
  autotest::check::check_equal(lhs, rhs, #lhs, #rhs, autotest::util::Location{__FILE__, __LINE__}, autotest::check::Severity::REQUIRED)
#define REQUIRE_CLOSE(lhs, rhs, tolerance) \
  autotest::check::check_close(lhs, rhs, tolerance, #lhs, #rhs, autotest::util::Location{__FILE__, __LINE__}, autotest::check::Severity::REQUIRED)
#define REQUIRE_THROWS_ANY(statement) \
  autotest::check::check_throws_impl(true, [&,this](){statement;}, #statement, autotest::util::Location{__FILE__, __LINE__}, autotest::check::Severity::REQUIRED)
#define REQUIRE_THROWS_NOT(statement) \
  autotest::check::check_throws_impl(true, [&,this](){statement;}, #statement, autotest::util::Location{__FILE__, __LINE__}, autotest::check::Severity::REQUIRED)
#define REQUIRE_THROWS_EXCEPTION(statement, exception) \
  autotest::check::check_throws_exception<exception>([&,this](){statement;}, #statement, #exception, autotest::util::Location{__FILE__, __LINE__}, autotest::check::Severity::REQUIRED)
