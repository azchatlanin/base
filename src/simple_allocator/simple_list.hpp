#pragma once

#include <memory>
#include "tools/src/logger/logger.hpp"

template<typename T, typename allocator_type = std::allocator<T>>
class simple_list 
{
  public:
    simple_list() = default;
    ~simple_list() = default;

    void add(T value) 
    {
      auto n = allocator.allocate(1);
      n->value = value;
      if (n) 
      {
        if (!node) 
        {
          node = n;
          tmp = n;
        } 
        else 
        {
          tmp->next = n;
          tmp = n;
        }
      }
    }

    struct Node 
    {
      Node() = default;
      explicit Node(const T& value_): value(value_), next(nullptr) {};
      T value;
      Node* next;
    };

    class Iterator
    {
      public:
        Iterator(Node* element) : current(element) {}
        Iterator operator++() 
        {
          current = current->next;
          return current;
        }
        auto operator*() { return current->value; }
        bool operator!=(const Iterator& rhs) { return current != rhs.current; }

      private:
        Node* current;
    };

    Iterator begin()
    {
      return Iterator(this->node);
    }

    Iterator end()
    {
      if (this->tmp)
        return Iterator(this->tmp->next);
      return Iterator(nullptr);
    }

    using Allocator = typename allocator_type::template rebind<Node>::other;
    Allocator get_allocator() { return allocator; };

  private:
    Node* node = nullptr;
    Node* tmp = nullptr;
    Allocator allocator;
};
