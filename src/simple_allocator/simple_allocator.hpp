#include <bitset>
#include <map>
#include <new>

#include "tools/src/index.hpp"

#include "simple_list.hpp"

namespace pr
{
  namespace allocator
  {
    template <typename T, auto allocate_size = 128> // auto --> std::size_t
    class simple_allocator 
    {
      public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        int construct_control = 0;
        int memory_control = 0;

      private:
        pointer memory = nullptr;
        std::size_t used_size = 0;
        std::bitset<allocate_size> memory_map;

      public:
        simple_allocator()
        {
          memory = static_cast<pointer>(std::malloc(allocate_size * sizeof(value_type)));
          if (memory == nullptr) 
            throw std::bad_alloc();
          memory_map.reset();
          ++construct_control;
        }
        ~simple_allocator() 
        {
          if (memory != nullptr)
            std::free(memory);
          --construct_control;
        }
    
        template<typename U>
        explicit simple_allocator(const simple_allocator<U, allocate_size>& t) : construct_control { t.construct_control}, 
                                                                                 memory_control { t.memory_control } {}

        template <typename U>
        struct rebind { typedef simple_allocator<U, allocate_size> other; };

        pointer allocate(std::size_t n) 
        {
          if (allocate_size < n + used_size)
            throw std::bad_alloc();

          std::size_t index = 0;
          for (std::size_t i = 0; i < allocate_size; ++i) 
          {
            if (memory_map.test(i))
              continue;
            index = i;
            break;
          }
          memory_map.flip(index);
          used_size += n;
          ++memory_control;
          return memory + index;
        }
        
        void deallocate(pointer p, std::size_t n) 
        {
          auto f = p - memory;
          for (std::size_t i = 0; i < n; ++i) 
            memory_map.reset(f + i);
          used_size -= n;
          --memory_control;
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
      try
      {
        // using allocator = simple_allocator<std::pair<const int, int>, 11>;
        // std::map<int, int, std::less<int>, allocator> m;
        // for (int i = 0; i < 3; ++i)
        //   m.emplace(i, i+1);
        // for (const auto& p : m)
        //   LOG("m", p.first, p.second);

        using allocator_list = simple_allocator<int, 11>;
        simple_list<int, allocator_list> sl;
        sl.add(1);
        sl.add(2);
        sl.add(3);
        for (const auto& p : sl) 
          LOG("sl", p);
        LOG(sl.get_allocator().memory_control);
      }
      catch(std::exception& e)
      {
        ERROR(e.what());
      }
    }
  }
}
