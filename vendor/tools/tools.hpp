#include <vector>
#include <string>

#define ERROR_EXCEPTION_1(msg) auto trace = std::string(LOGGER___TRACE_ON); \
                           throw tools::error_exception(msg, "internal system error", trace)
#define ERROR_EXCEPTION_2(msg, error) auto trace = std::string(LOGGER___TRACE_ON); \
                           throw tools::error_exception(msg, error, trace)
#define GET_MACRO(_1,_2,NAME, ...) NAME
#define ERROR_EXCEPTION(...) GET_MACRO(__VA_ARGS__, ERROR_EXCEPTION_2, ERROR_EXCEPTION_1)(__VA_ARGS__)

namespace tools
{
  using v_str = std::vector<std::string>;

  struct error_exception : public std::exception
  {
    error_exception(std::string msg, std::string error, std::string trace) : message{ msg }, error{ error }, trace{ trace } {};
    std::string message;
    std::string error;
    std::string trace;
    const char* what () const throw () { return message.c_str(); }
  };

  inline v_str split_str(const std::string& str, const char t)
  {
    v_str v;
    std::string::size_type begin = 0;
    std::string::size_type end = str.find_first_of(t);
    while(end != std::string::npos)
    {
      v.emplace_back(str.substr(begin, end - begin));
      begin = ++end;
      end = str.find_first_of(t, begin);
    }
    v.emplace_back(str.substr(begin));
    return v;
  }
}

