#include <gtest/gtest.h>

#include "simple_allocator/simple_allocator.hpp"

TEST(simple_allocator, check__memory_control)
{
  using allocator = pr::allocator::simple_allocator<std::pair<const int, int>, 11>;
  std::map<int, int, std::less<int>, allocator> m;
  for (int i = 0; i < 3; ++i)
    m.emplace(i, i+1);
    
  ASSERT_EQ(m.get_allocator().memory_control, 3);
}

TEST(simple_allocator, check__construct_control)
{
  using allocator = pr::allocator::simple_allocator<std::pair<const int, int>, 11>;
  std::map<int, int, std::less<int>, allocator> m;
  for (int i = 0; i < 3; ++i)
    m.emplace(i, i+1);
    
  ASSERT_EQ(m.get_allocator().construct_control, 1);
}

TEST(simple_allocator, check__stack_overflow)
{
  try 
  {
    using allocator = pr::allocator::simple_allocator<std::pair<const int, int>, 11>;
    std::map<int, int, std::less<int>, allocator> m;
    for (int i = 0; i < 3333; ++i)
      m.emplace(i, i+1);
  }
  catch(std::exception const & err) {
    EXPECT_EQ(err.what(), std::bad_alloc().what());
  }
  catch(...) {
    FAIL() << "Expection not define";
  }
}
