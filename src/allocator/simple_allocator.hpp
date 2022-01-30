#include <bitset>
#include <map>

#include "tools/src/logger/logger.hpp"

namespace pr
{
  namespace allocator
  {
    template <typename T, std::size_t TotalSize>
    class simple_allocator 
    {
      public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;

      private:
        pointer area = nullptr;
        std::size_t allocated_size = 0;
        std::bitset<TotalSize> memory_map;

        void init() 
        {
          area = static_cast<pointer>(std::malloc(TotalSize * sizeof(value_type)));
          if (area == nullptr) 
            throw std::bad_alloc();
          memory_map.reset();
        }

      public:
        simple_allocator() = default;
        ~simple_allocator() 
        {
          if (area != nullptr)
            std::free(area);
        }

        template <typename U>
        struct rebind 
        {
          using other = simple_allocator<U, TotalSize>;
        };

        pointer allocate(std::size_t n) 
        {
          if (area == nullptr)
            init();

          if (TotalSize < n + allocated_size)
            throw std::bad_alloc();

          std::size_t lo = 0, hi = 0;
          for (std::size_t i = 0; i < TotalSize; ++i) 
          {
            if (memory_map.test(i))
              continue;

            std::size_t j = i + 1;
            for (; j < TotalSize && !memory_map.test(j) && j - i + 1 <= n; ++j) {}
            if (j - i == n) 
            {
              lo = i;
              hi = j;
              break;
            }
          }
          if (lo == 0 && hi == 0)
            throw std::bad_alloc();

          for (std::size_t i = lo; i < hi; ++i)
            memory_map.flip(i);

          allocated_size += n;
          return area + lo;
        }

        void deallocate(pointer p, std::size_t n) 
        {
          std::size_t from = p - area;
          for (std::size_t i = 0; i < n; ++i, ++p) 
            memory_map.set(from + i, false);
          allocated_size -= n;
        }

        template <typename U, typename... Args>
        void construct(U* p, Args&&... args)
        {
          new (p) U(std::forward<Args>(args)...);
        }

        void destroy(T* p)
        {
          p->~T();
        }
    };

    inline void process()
    {
      LOG("run: simple allocator task");

      std::map<int, int, std::less<int>, simple_allocator<std::pair<const int, int>, 11>> m;

      std::array<int, 3> arr { 1, 2, 3 };

      for (int i = 0; i < 3; ++i) {
          m.emplace(i, arr[i]);
      }

      for (const auto& p : m)
        LOG("m", p.first, p.second);
    }
  }
}
