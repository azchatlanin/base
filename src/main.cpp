#include "vendor/logger.hpp"
#include "config.hpp"

int main(int argc, const char* argv[]) 
{
  LOG("Hello World!");
  LOG(cfg::get_version());

  return 0;
}
