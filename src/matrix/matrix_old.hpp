#pragma once

#include <memory>
#include <vector>
#include <tuple>
#include <algorithm>

#include "tools/src/index.hpp"

namespace pr::matrix 
{
  template<typename T, std::size_t N>
  struct generate_tuple 
  {
    using type = decltype (std::tuple_cat(typename generate_tuple<T, N - 1>::type{}, std::tuple<T>{}));
    // <int, 3>
    // type decltype (generate_tuple<int, 2>::type{}, std::tuple<int>{});
    // type decltype (std::tuple<int>{}, std::tuple<int>{});
    // result: type decltype (std::tuple<int>{}, std::tuple<int>{}, std::tuple<int>{});
  };

  template<typename T>
  struct generate_tuple<T, 1> 
  {
    typedef std::tuple<T> type;
  };

  template <typename... T, std::size_t... I>
  auto subtuple_(const std::tuple<T...>& t, std::index_sequence<I...>) 
  {
    return std::tuple(std::get<I>(t)...);
  }

  template <typename... T>
  auto subtuple(const std::tuple<T...>& t) 
  {
    return subtuple_(t, std::make_index_sequence<sizeof...(T) - 1>());
  }

  template<typename T, std::size_t dimensions>
  class Matrix
  {
   public:
    using index_t = typename generate_tuple<T, dimensions>::type;
    using storage_t = std::vector<decltype(std::tuple_cat(index_t{}, std::tuple<T>{}))>;

    Matrix() : local_storage{ new storage{} } {}

    int size() const
    {
      return local_storage->size();
    }

    auto operator[](std::size_t index)
    {
      return proxy<storage, std::tuple<std::size_t>>{ local_storage, std::tuple<std::size_t>(index) };
    }
    
    auto begin() noexcept
    {
      return local_storage->values.begin();
    }

    auto begin() const noexcept
    {
      return local_storage->values.begin();
    }

    auto end() noexcept
    {
      return local_storage->values.end();
    }

    auto end() const noexcept
    {
      return local_storage->values.end();
    }

    auto cbegin() const noexcept
    {
      return local_storage->values.cbegin();
    }

    auto cend() const noexcept
    {
      return local_storage->values.cend();
    }

   private:
    struct storage
    {
      void set_value(const index_t& index, const T& v)
      {
        auto value = std::tuple_cat(index, std::tuple<T>(v));
        values.push_back(value);
      }

      auto get_value(const index_t& index)
      {
        auto it = std::find_if(values.begin(), values.end(), [&](auto a) { return subtuple(a) == index; });
        //if (it == values.end()) return 0;
        return std::get<dimensions>(*it);
      }

      int size() const
      {
        return values.size();
      }

      storage_t values;
    };

    template<typename storage_t, typename index_t>
    class proxy
    {
      using next_index_t = decltype(std::tuple_cat(index_t{}, std::tuple<std::size_t>{}));

      public:
        proxy(const std::weak_ptr<storage_t>& local_storage, const index_t& index) : local_storage{ local_storage }, index{ index } {};

        auto operator[](std::size_t i) const
        {
          return proxy<storage_t, next_index_t>{ local_storage, std::tuple_cat(index, std::tuple<std::size_t>(i)) };
        }

        auto& operator=(const T& value)
        {
          std::shared_ptr<storage>(local_storage)->set_value(index, value);
          return *this;
        }

        operator T() const
        {
          std::shared_ptr<storage_t> m = local_storage.lock();
          return m->get_value(index);
        }

        auto operator==(const T& value) const
        {
          std::shared_ptr<storage_t> m{ local_storage };
          return value == m->get_value(index);
        }

        friend bool operator==(const T& lhs, const proxy& rhs)
        {
          return rhs == lhs;
        }

      private:
        std::weak_ptr<storage_t> local_storage;
        index_t index;
    };

    private:
      std::shared_ptr<storage> local_storage;
  };

  inline void process()
  {

    Matrix<float, 3> matrix{};
    matrix[2][2][2] = 1223.4f;
    LOG("element =", matrix[2][2][2]);

    for (const auto& matrix_element : matrix)
      LOG(matrix_element);
  };
}
