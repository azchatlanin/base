#include <gtest/gtest.h>

#include "simple_allocator/simple_allocator.hpp"
#include "simple_allocator/simple_list.hpp"


TEST(simple_allocator, check__memory_control)
{
  using allocator = pr::allocator::simple_allocator<std::pair<const int, int>, 11>;
  std::map<int, int, std::less<int>, allocator> m; 
  for (int i = 0; i < 3; ++i)
    m.emplace(i, i+1);

  ASSERT_EQ(m.get_allocator().count_allocate, 3);
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

TEST(simple_allocator, check__simple_list)
{
  simple_list<int, pr::allocator::simple_allocator<int, 11>> sl;
  sl.push_back(1);
  sl.push_back(2);
  sl.push_back(3);
  ASSERT_EQ(sl.get_allocator().count_allocate, 3);
}
