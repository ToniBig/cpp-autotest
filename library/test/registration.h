#pragma once

#include "../util/stringify.h"

namespace autotest {
namespace tree {

struct nil_fixture
{
};

} // namespace tree
} // namespace autotest

using AutoTestFixture = autotest::tree::nil_fixture;

static autotest::tree::test_suite_ptr _current_suite_ = autotest::tree::test_broker::get_master_test_suite( );

/// -----------------------------------------------------------------
/// Test suite macros
/// -----------------------------------------------------------------

#define _REGISTER_TEST_SUITE_IMPL(description)                              \
static autotest::tree::test_suite_ptr _parent_suite_ = _current_suite_;     \
static auto _namespace_suite_ = _parent_suite_->get_suite( #description );  \
static autotest::tree::test_suite_ptr _current_suite_ = _namespace_suite_;

#define TEST_SUITE(description)                 \
namespace CONCATENATE(Test_Suite_, description) \
{                                               \
_REGISTER_TEST_SUITE_IMPL(description)          \
}                                               \
namespace CONCATENATE(Test_Suite_, description) \

#define TEST_SUITE_WITH_FIXTURE(description, Fixture) \
namespace CONCATENATE(Test_Suite_, description)       \
{                                                     \
_REGISTER_TEST_SUITE_IMPL(description)                \
using AutoTestFixture = Fixture;                      \
}                                                     \
namespace CONCATENATE(Test_Suite_, description)

/// -----------------------------------------------------------------
/// Test case macros
/// -----------------------------------------------------------------

#define _TESTCASENAME(str)                         \
  CONCATENATE(Test_Case_, str)
#define _TESTCASEINVOKER(str)                      \
  CONCATENATE(_TESTCASENAME(str), _invoker)
#define _TESTCASEREGISTRAR(str)                    \
  CONCATENATE(_TESTCASENAME(str), _registrar)

#define _TEST_CASE_WITH_FIXTURE_IMPL(description, fixture, status)         \
    struct _TESTCASENAME(description) : fixture { void invoke(); };        \
    static void _TESTCASEINVOKER(description)()                            \
    {                                                                      \
      _TESTCASENAME(description) test_case;                                \
      test_case.invoke();                                                  \
    }                                                                      \
    static bool _TESTCASEREGISTRAR(description) __attribute__((unused)) =  \
            _current_suite_->add_test( {                                   \
            #description, _TESTCASEINVOKER(description),                   \
           autotest::tree::test_status_e(status),                          \
           {__FILE__, __LINE__} } );                                       \
    void _TESTCASENAME(description)::invoke()

#define TEST_CASE_WITH_FIXTURE(description, fixture) \
    _TEST_CASE_WITH_FIXTURE_IMPL(description, fixture, autotest::tree::test_status_e::RUN )

#define TEST_CASE(description) \
    _TEST_CASE_WITH_FIXTURE_IMPL(description, AutoTestFixture, autotest::tree::test_status_e::RUN )
