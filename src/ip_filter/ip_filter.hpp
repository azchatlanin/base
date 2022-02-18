#pragma once

#include <array>
#include <algorithm>
#include <vector>
#include <set>        // multiset
#include <functional> // greater

#include "tools/src/logger/logger.hpp"
#include "tools/src/exception/simple_error.hpp"
#include "tools/src/func/split_str.hpp"

template<std::size_t N>
using arr = std::array<unsigned int, N>;

template<typename... Args>
using make_index = std::make_index_sequence<sizeof... (Args)>;

using v_str = std::vector<std::string>;
const std::size_t IP_SIZE = 4;

namespace pr::ip_filter
{
  struct ip 
  {
    ip(const v_str& data)
    {
      if (data.size() != IP_SIZE) { ERROR_EXCEPTION("ip data dosn't contain nessesarry data"); }
      std::transform(data.cbegin(), data.cend(), parts.begin(), [](const std::string& ip_str) {
        auto ip = std::stoul(ip_str);
        if (ip > 255) { ERROR_EXCEPTION("ip went beyong the borders"); }
        return ip;
      });
    };

    friend bool operator< (const ip& l, const ip& r)
    {
      return l.parts < r.parts;
    }

    friend bool operator> (const ip& l, const ip& r)
    {
      return l.parts > r.parts;
    }

    friend std::ostream& operator<< (std::ostream& out, const ip& node)
    {
      out << node.parts[0] << '.'
          << node.parts[1] << '.' 
          << node.parts[2] << '.'
          << node.parts[3] << '\n';
      return out;
    }

    friend bool operator== (const ip& l, const ip& r)
    {
      return l.parts == r.parts;
    }

    arr<IP_SIZE> parts;
  };

  constexpr auto filter_end()
  {
    return true;
  }

  template<typename... Args>
  constexpr auto filter_end(bool h, Args... args)
  {
    return h && filter_end(args...);
  }

  template<typename Array, std::size_t... idx, typename... Args>
  constexpr auto filter_begin(Array& parts, std::index_sequence<idx...>, Args... args)
  {
    return filter_end((parts[idx] == args)...);
  }

  template<typename... Args, typename I = make_index<Args...>>
  constexpr auto filter(const arr<IP_SIZE>& parts, Args... args)
  {
    static_assert(IP_SIZE == 4);                                       
    static_assert(sizeof...(Args) <= IP_SIZE, "don't compliance size");
    return filter_begin(parts, I{}, args...);
  }

  inline std::vector<ip> process()
  {
    std::istream& in = std::cin; 
    std::ostream& out = std::cout;

    std::vector<ip> pool;
    std::vector<ip> transform;

    try {
      for(std::string line; std::getline(in, line);)
        pool.emplace_back(tools::func::split_str(tools::func::split_str(line, '\t').at(0), '.'));
        
      std::sort(pool.begin(), pool.end(), std::greater<ip>());
      
      using it = std::back_insert_iterator<std::vector<ip>>;
      std::copy_if(pool.cbegin(), pool.cend(), it(transform), [](const ip& node) { return filter(node.parts, 1u); });
      std::copy_if(pool.cbegin(), pool.cend(), it(transform), [=](const ip& node) { return filter(node.parts, 46u, 70u); });

      const int n = 46u;
      auto any_of = [=](const ip& node) {
        return std::any_of(node.parts.cbegin(), node.parts.cend(), [=](const auto& p) { return p == n; });
      };
      std::copy_if(pool.cbegin(), pool.cend(), it(transform), any_of);

      pool.insert(pool.cend(),transform.cbegin(), transform.cend());
      std::copy(pool.cbegin(), pool.cend(), std::ostream_iterator<decltype(pool)::value_type>{ out });
    } 
    catch (tools::error::error_exception& err) 
    {
      ERROR(err.message);
    }
    catch(std::invalid_argument &e)
    {
      ERROR("invalid argument in array IP");
    }

    return pool;
  }
}
