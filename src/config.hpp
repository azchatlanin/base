#include <string>
#include <memory>

namespace cfg
{
  std::string run(std::string cmd)
  {
    std::string result;
    std::array<char, 128> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) 
      throw std::runtime_error("popen() failed!");
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) 
    {
      result = buffer.data();
    }
    
    return result;
  }

  std::string get_version()
  {
    return run("git describe --abbrev=0");
  }
} // cfg

