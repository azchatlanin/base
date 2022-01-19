#pragma once

#include"vendor/logger.hpp"

#define ERROR_EXCEPTION_1(msg) auto trace = std::string(LOGGER___TRACE_ON); \
                             throw error_exception(msg, "internal system error", trace)

#define ERROR_EXCEPTION_2(msg, error) auto trace = std::string(LOGGER___TRACE_ON); \
                             throw error_exception(msg, error, trace)

#define GET_MACRO(_1,_2,NAME, ...) NAME
#define ERROR_EXCEPTION(...) GET_MACRO(__VA_ARGS__, ERROR_EXCEPTION_2, ERROR_EXCEPTION_1)(__VA_ARGS__)

namespace pr
{
  struct error_exception : public std::exception
  {
    error_exception(std::string msg, std::string error, std::string trace) : message{ msg }, error{ error }, trace{ trace } {};
     
    std::string message;
    std::string error;
    std::string trace;

    const char* what () const throw ()
    {
      return message.c_str();
    }
  };
} // namespace pr

