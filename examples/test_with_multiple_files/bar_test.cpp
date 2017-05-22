#include "autotest.hpp"

TEST_SUITE(Bar_Test_Suite) {
struct Fixture
{
  int a = 4;
  double b = 1.23;
};

TEST_SUITE_WITH_FIXTURE(Bar_with_Fixture, Fixture) {

TEST_CASE(Bar_Test_1)
{
  CHECK_EQUAL( a, 4 );
}

TEST_CASE(Bar_Test_2)
{
  CHECK_CLOSE( b, 1.22, 1e-1 );
}

} // Bar_with_Fixture

TEST_CASE_WITH_FIXTURE(Bar_Test_Case, Fixture)
{
  CHECK_EQUAL( a, 4 );
  CHECK_CLOSE( b, 1.22, 1e-1 );
}

} // Bar_Test_Suite
