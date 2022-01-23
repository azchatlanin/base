#include <gtest/gtest.h>

#include "ip_filter/ip_filter.hpp"

TEST(ip_filter, check__func)
{
  ASSERT_EQ(pr::ip_filter::process(), 0);
}
