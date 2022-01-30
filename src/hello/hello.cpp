#include "hello.hpp"

#include "tools/src/logger/logger.hpp"

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
