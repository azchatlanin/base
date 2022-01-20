#include <array>
#include <vector>
#include <set> // multiset
#include <functional> // greater

#include "vendor/logger.hpp"
#include "vendor/tools.hpp"

template<std::size_t N>
using arr = std::array<unsigned int, N>;

// for example 
template<typename... Args>
using make_index = std::make_index_sequence<sizeof... (Args)>;

const std::size_t IP_SIZE = 4;

namespace pr
{
  struct ip 
  {
    ip(const tools::v_str& data)
    {
      if (data.size() != IP_SIZE) { ERROR_EXCEPTION("ip data dosn't contain nessesarry data"); }
      std::transform(data.cbegin(), data.cend(), parts.begin(), [](const std::string& ip_str) {
        auto ip = std::stoul(ip_str);
        if (ip > 255) { ERROR_EXCEPTION("ip went beyong the borders"); }
        return ip;
      });
    };

    friend bool operator> (const ip& l, const ip& r)
    {
      return l.parts > r.parts;
    }

    friend std::ostream& operator<< (std::ostream& out, const ip& node)
    {
      for(const auto& i: node.parts) 
        out << i << (i != *(node.parts.cend()- 1) ? '.' : '\n'); // node.parts[3]
      return out;
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

  int process(std::istream& in, std::ostream& out)
  {
    std::multiset<ip, std::greater<ip>> pool;

    try {
      for(std::string line; std::getline(in, line);)
        pool.emplace(tools::split_str(tools::split_str(line, '\t').at(0), '.'));

      using it = std::ostream_iterator<decltype(pool)::value_type>;
      std::copy(pool.cbegin(), pool.cend(), it{ out });
      std::copy_if(pool.cbegin(), pool.cend(), it{ out }, [](const ip& node) { return filter(node.parts, 1); });
      std::copy_if(pool.cbegin(), pool.cend(), it{ out }, [](const ip& node) { return filter(node.parts, 1); });
    } 
    catch (tools::error_exception& err) 
    {
      ERROR(err.message);
    }

    return 0;
  }
}



int main(int args, const char* argv[])
{
  return pr::process(std::cin, std::cout);
}
