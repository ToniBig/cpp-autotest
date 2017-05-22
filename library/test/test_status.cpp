#include "test_status.h"

#define TEST_INLINE

namespace autotest {
namespace tree {

TEST_INLINE test_status_t::test_status_t( ) :
        status_( test_status_e::RUN )
{
}

TEST_INLINE test_status_t::test_status_t( test_status_e status ) :
        status_( status )
{
}

TEST_INLINE const test_status_e& test_status_t::get_status( ) const
{
  return status_;
}

} // namespace tree
} // namespace autotest
