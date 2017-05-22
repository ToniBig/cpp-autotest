#pragma once

#ifndef AUTOTEST_CREATE_MAIN
#include "check/checks.h"
#else
#include "test/test_broker.h"

int main( int argc,
          char **argv )
{
  autotest::tree::test_broker::execute(argc, argv);
}
#endif
