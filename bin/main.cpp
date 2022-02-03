#include "hello/hello.hpp"
#include "ip_filter/ip_filter.hpp"
#include "simple_allocator/simple_allocator.hpp"

#include "tools/src/logger/logger.hpp"

int main(int argc, char *argv[])
{
  if (argc < 1) 
    exit(EXIT_FAILURE);
  std::string name = argv[1];

  if (name ==  "hello")
    pr::hello::process();
  else if (name == "ip_filter")
    pr::ip_filter::process();
  else if (name == "simple_allocator")
    pr::allocator::process();
  
  return 0;
}
