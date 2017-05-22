#include "autotest.hpp"

TEST_SUITE(Foo_Test_Suite) {
struct Fixture
{
  int a = 4;
  double b = 1.23;
};

TEST_SUITE_WITH_FIXTURE(Foo_with_Fixture, Fixture) {

TEST_CASE(Foo_Test_1)
{
  CHECK_EQUAL( a, 4 );
}

TEST_CASE(Foo_Test_2)
{
  CHECK_CLOSE( b, 1.22, 1e-1 );
}

TEST_CASE(Here_goes)
{
  CHECK( false );
  CHECK_CLOSE( 1.23, 1.1, 1e-2 );
  CHECK_EQUAL( 2, 3 );
  CHECK_THROWS_ANY( );
  CHECK_THROWS_EXCEPTION( throw 4, std::exception );
  CHECK_THROWS_EXCEPTION(, std::exception );
  CHECK_THROWS_NOT( throw std::exception( ) );
  REQUIRE( false );
}

} // Foo_with_Fixture

TEST_CASE_WITH_FIXTURE(Foo_Test_Case, Fixture)
{
  CHECK_EQUAL( a, 4 );
  CHECK_CLOSE( b, 1.22, 1e-1 );
}

} // Foo_Test_Suite
