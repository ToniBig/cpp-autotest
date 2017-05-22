namespace autotest {
namespace tree {

enum class test_status_e
{
  RUN, SKIP, TODO
};

struct test_status_t
{
  test_status_t( );
  test_status_t( test_status_e status );

  const test_status_e& get_status( ) const;

private:
  test_status_e status_;
};

} // namespace tree
} // namespace autotest
