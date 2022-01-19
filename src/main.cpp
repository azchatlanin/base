#include "vendor/logger.hpp"

#include <vector>
#include <array>
#include <set>
#include <functional>

#include "error_exception.hpp"

using v_str = std::vector<std::string>;

namespace pr 
{
  struct ip
  {
    explicit ip(const v_str& ip_data)
    {
      if (ip_data.size() != 4) { ERROR_EXCEPTION("ip_data dosn't contain nessesarry data"); }

      std::transform(ip_data.begin(), ip_data.end(), parts.begin(), [](std::string ip_str) {
        auto ip = std::stoul(ip_str);
        if (ip > 255) { ERROR_EXCEPTION("ip went beyong the borders"); }
        return ip;
      });
    }

    std::array<unsigned int, 4> parts;

    friend bool operator> (const ip& lip, const ip& rip)
    {
      return lip.parts > rip.parts;
    }

    friend std::ostream& operator<< (std::ostream& out, const ip& node)
    {
      for(const auto& i : node.parts)
        out << i << (i != *(node.parts.cend() - 1) ? '.' : '\n'); // node.parts[3]
      return out;
    }
  };

  constexpr auto filter_end()
  {
    return true;
  }

  template<typename Head, typename... Args>
  constexpr auto filter_end(Head h, Args... args)
  {
    return h && filter_end(args...);
  }

  template<typename Array, std::size_t... idx, typename... Args>
  constexpr auto filter_begin(Array& parts, std::index_sequence<idx...>, Args... args)
  {
    return filter_end((parts[idx] == args)...);
  }


  template<typename T, std::size_t N, typename... Args, typename Indices = std::make_index_sequence<sizeof...(Args)>>
  constexpr auto filter_impl(const std::array<T, N>& parts, Args... args)
  {
    const int i = 4;
    static_assert(i == 4); // simple check for own example here. never mind.

    static_assert(N >= sizeof...(Args));
    static_assert(sizeof...(Args) != 0);

    return filter_begin(parts, Indices{}, args...);
  }

  int process(std::ostream& out, std::istream& in)
  {
    std::multiset<ip, std::greater<ip>> pool;
    using it = std::ostream_iterator<decltype(pool)::value_type>;


    auto split = [](const std::string& line, const char c) {
      v_str v;
      std::string::size_type begin = 0;
      std::string::size_type end = line.find_first_of(c);
      while(end != std::string::npos)
      {
        v.push_back(line.substr(begin, end - begin));
        begin = end + 1;
        end = line.find_first_of(c, begin);
      }
      v.push_back(line.substr(begin));
      return v;
    };

    try
    {
      for(std::string line; std::getline(in, line);)
      {
        pool.emplace(split(split(line, '\t').at(0), '.'));
      }

      std::copy(pool.cbegin(), pool.cend(), it{ out });
      std::copy_if(pool.cbegin(), pool.cend(), it{ out }, [](const ip& node) { return filter_impl(node.parts, 1); }); 
      std::copy_if(pool.cbegin(), pool.cend(), it{ out }, [](const ip& node) { return filter_impl(node.parts, 46, 70); }); 
      std::copy_if(pool.cbegin(), pool.cend(), it{ out }, [](const ip& node) { return std::any_of(node.parts.cbegin(), node.parts.cend(), [](const auto& part) { return part == 46; }); }); 
    }
    catch (error_exception& e) 
    {
      ERROR(e.trace, e.message, e.error);
    }

    return 0;
  }
}

int main(int argc, const char* argv[]) 
{
  return pr::process(std::cout, std::cin);
}
