#include <memory>
#include <vector>

namespace motivation {

	template <typename T>
	struct MyAllocator {
		using value_type = T;

		MyAllocator() = default;

		template <typename U>
		MyAllocator(const MyAllocator<U>&) {}

		T* allocate (std::size_t n) { 
			auto p = std::malloc(n * sizeof(T));
			if (!p)
				throw std::bad_alloc();
			return reinterpret_cast<T *>(p);
		}
		
		void deallocate (T* p, std::size_t) {
			std::free(p);
		}
	};

	void calculations(const std::vector<int>& ) {
		// some code here
	}

	void someFunction() {
		std::vector<int> values1{0, 1, 2, 3, 4, 5};
		calculations(values1); // Ok

		std::vector<int, MyAllocator<int>> values2{5, 4, 3, 2, 1};
		//calculations(values2); // Error

		std::vector<int> values3{10, 9, 8, 7, 6, 5};
		values1 = values3; // Ok

		// values1 = values2; // Error
	}
}

#include <memory_resource>
namespace solution {

	template <typename T>
	struct MyAllocator : public std::pmr::memory_resource {
		using value_type = T;

		MyAllocator() = default;

		void * do_allocate(size_t n, size_t ) override {
			auto p = std::malloc(n * sizeof(T));
			if (!p)
				throw std::bad_alloc();
			return p;
		}
		void do_deallocate(void * p, size_t, size_t) override {
			std::free(p);
		}
		bool do_is_equal(const std::pmr::memory_resource& ) const noexcept override {
			return false;
		}
	};

	// pmr::vector?? 
	void calculations(const std::pmr::vector<int>& ) {
		// some code here
	}

	void someFunction() {
		std::pmr::vector<int> values1{0, 1, 2, 3, 4, 5};
		calculations(values1); // Ok

		MyAllocator<int> myAllocator;
		std::pmr::vector<int> values2(&myAllocator);
		calculations(values2); // Ok now!

		std::pmr::vector<int> values3{10, 9, 8, 7, 6, 5};
		values1 = values3; // Ok

		values1 = values2; // Ok
	}

}

int main() {

	return 0;
}