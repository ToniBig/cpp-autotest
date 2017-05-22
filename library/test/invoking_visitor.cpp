#include "invoking_visitor.h"
#include "test_suite.h"
#include "test_case.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#define TEST_INLINE

namespace autotest {
namespace tree {

TEST_INLINE void InvokingVisitor::visit_impl( tree::test_cases& test_cases )
{
  for ( auto & test_case : test_cases )
  {
    auto status = test_case.get_status( );

    switch ( status )
    {
    case tree::test_status_e::RUN:
    {
      test_case.run( );

      auto assertions = test_case.get_results( );

      auto iter = std::stable_partition( assertions.begin( ), assertions.end( ), [](const check::check_result& result)
      {
        return result.passed== false;
      } );

      auto failed_checks = std::distance( assertions.begin( ), iter );
      auto passed_checks = std::distance( iter, assertions.end( ) );

      failed_assertion_count += failed_checks;
      passed_assertion_count += passed_checks;

      if ( failed_checks )
      {
        bool singular = failed_checks == 1;

        result_ << "\n";
        result_ << "Failure of " << failed_checks;
        result_ << " assertion" << ( singular ? "" : "s" ) << " in test case: ";
        result_ << names_.get_full_name( "/" ) << test_case.get_name( ) << std::endl;

        std::for_each( assertions.begin( ), iter, [this](const check::check_result& assertion)
        {
          result_ << assertion.location.file;
          result_ << "(" << assertion.location.line << "):";
          result_ << "check failed" << ": ";
          result_ << assertion.message;
          result_ << (assertion.severity==check::Severity::REQUIRED?" <-- required":"");
          result_ << std::endl;
        } );

        std::cout << "f";
        failed_test_count++;
      }
      else
      {
        std::cout << ".";
        passed_test_count++;
      }
    }
      break;
    case tree::test_status_e::SKIP:
    {
      auto location = test_case.get_location( );
      result_ << "Skipped test case: " << names_.get_full_name( "/" ) << test_case.get_name( );
      result_ << location.file << "(" << location.line << ")" << std::endl;

      std::cout << "s";
      skipped_test_count++;
    }
      break;
    case tree::test_status_e::TODO:
    {
      auto location = test_case.get_location( );
      result_ << "Need to implement test case: " << names_.get_full_name( "/" ) << test_case.get_name( );
      result_ << location.file << "(" << location.line << ")" << std::endl;

      std::cout << "t";
      failed_test_count++;
    }
      break;
    default:
      break;
    }
  }
}

TEST_INLINE std::string InvokingVisitor::summary( )
{
  auto totalTestCount = failed_test_count + passed_test_count;
  auto totalAssertionCount = failed_assertion_count + passed_assertion_count;

  std::stringstream summary;

  if ( failed_test_count )
  {
    summary << "\n\n";
    summary << "FAILURE in " << failed_test_count << " test" << ( failed_test_count == 1 ? "" : "s" );
    summary << " (Ran " << totalTestCount << " test" << ( totalTestCount == 1 ? "" : "s" );
    summary << " with " << totalAssertionCount << " assertion" << ( totalAssertionCount == 1 ? "" : "s" );
    summary << ")\n";
    summary << result_.str( );
  }
  else
  {
    summary << "\n\n";
    summary << "SUCCESS";
    summary << " (Ran " << totalTestCount << " test" << ( totalTestCount == 1 ? "" : "s" );
    summary << " with " << totalAssertionCount << " assertion" << ( totalAssertionCount == 1 ? "" : "s" );
    summary << ")\n";
  }

  return std::move( summary.str( ) );
}

} // namespace tree
} // namespace autotest
