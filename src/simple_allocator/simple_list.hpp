#pragma once

#include <memory>
#include "tools/src/logger/logger.hpp"

namespace pr::list
{
  template<class T, class allocator_type = std::allocator<T>> 
  class simple_list
  {
    template<class U>
    class Node
    {
      public:
        Node() = default;
        template <class... Args>
        Node(Args&&... args) : next { nullptr }, value { std::forward<Args>(args)... } {}
        ~Node() { next = nullptr; }

      public:
        U& get() { return value; }
        Node<U>* get_next() { return next; }
        void set_next(Node<U>* ptr) { next = ptr; }
        
      private: 
        Node<U>* next { nullptr };
        U value;
    };

    using allocator = typename allocator_type::template rebind<Node<T>>::other;

    public:
      simple_list() : alloc { allocator{} } { tail = &head; }
      ~simple_list()
      { 
        auto node = head.get_next();
        while (node)
        {
          auto nextNode = node->get_next();
          alloc.deallocate(node, 1);
          alloc.destroy(node);
          node = nextNode;
        }
      }

    std::size_t size() const { return size_; }
    allocator_type get_allocator() { return allocator_type(*static_cast<const allocator*>(&this->alloc)); }

    template <class... Args>
    void push_back(Args&&... args)
    {
      auto n = alloc.allocate(1);
      alloc.construct(n, std::forward<Args>(args)...);
      tail->set_next(n);
      tail = n;
      size_++;
    }

    class iterator
    {
      public:
        iterator(Node<T>* ptr) : ptr { ptr } {}
        Node<T>* get_node() { return ptr; }
        iterator operator ++ () { ptr = ptr->get_next(); return *this; }
        T& operator * () { return ptr->get(); }
        bool operator != (const iterator& rhs) { return ptr != rhs.ptr; }
      private: 
        Node<T>* ptr;
    };

    iterator begin() { return iterator{ head.get_next() }; }
    iterator end() { return iterator{ tail->get_next() }; }

    private: 
      std::size_t size_ { 0 };
      Node<T>* tail { nullptr };
      Node<T> head;
      allocator alloc;
  };
}
