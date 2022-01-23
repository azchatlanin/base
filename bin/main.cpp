#include "hello/hello.hpp"
#include "ip_filter/ip_filter.hpp"

#include "vendor/logger/logger.hpp"

int main(int argc, char *argv[])
{
  if (argc < 1) 
    exit(EXIT_FAILURE);
  std::string name = argv[1];

  int result = 0;

  if (name ==  "hello")
    result = pr::hello::process();
  else if (name == "ip_filter")
    result = pr::ip_filter::process();
  
  return result;
}
