#include <gtest/gtest.h>

#include "hello/hello.hpp"

TEST(Hello, check__func)
{
  ASSERT_EQ(pr::hello::process(), 0);
}
