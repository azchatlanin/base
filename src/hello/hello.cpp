#include "hello.hpp"

#include "vendor/logger/logger.hpp"

namespace pr 
{
  namespace hello 
  {
    int process() 
    {
      LOG("Hello world!");
      return 0;
    }
  }
}
