#include "hello/hello.hpp"
#include "ip_filter/ip_filter.hpp"
#include "simple_allocator/simple_allocator.hpp"
#include "matrix/matrix_old.hpp"
#include "log/logger.hpp"

//#include "tools/src/logger/logger.hpp"

int main(int argc, char *argv[])
{
  if (argc < 1) 
    exit(EXIT_FAILURE);
  std::string name = argv[1];

  if (name ==  "hello")
    std::ignore = pr::hello::process();
  else if (name == "ip_filter")
    std::ignore = pr::ip_filter::process();
  else if (name == "simple_allocator")
    pr::allocator::process();
  else if (name == "logger")
    pr::logger::process();
  else if (name == "matrix")
    pr::matrix::process();
  
  return 0;
}
