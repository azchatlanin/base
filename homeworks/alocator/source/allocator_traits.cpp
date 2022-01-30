#include <iostream>
#include <memory>
#include <vector>

template <typename T>
struct MyAllocator {
	using value_type = T;

	MyAllocator();

	template <typename U>
	MyAllocator(const MyAllocator<U>&);

	T* allocate (std::size_t n);
	
	void deallocate (T* p, std::size_t n);
};

template <typename T>
MyAllocator<T>::MyAllocator() {
}

template <typename T>
template <typename U>
MyAllocator<T>::MyAllocator(const MyAllocator<U>& ) {
	// should we make a copy of the rhs.m_buffer ?
	// No, we should not!
}

template <typename T>
T* MyAllocator<T>::allocate (std::size_t n) {
	auto p = std::malloc(n * sizeof(T));
	if (!p)
		throw std::bad_alloc();
	return reinterpret_cast<T *>(p);
}

template <typename T>
void MyAllocator<T>::deallocate (T* p, std::size_t ) {
	std::free(p);
}

template <class T, class U>
constexpr bool operator== (const MyAllocator<T>&, const MyAllocator<U>&) noexcept {
	return false;
}

template <class T, class U>
constexpr bool operator!= (const MyAllocator<T>&, const MyAllocator<U>&) noexcept {
	return false;
}

int main() {

	std::vector<int, MyAllocator<int>> vector;

	for (int i = 0; i < 10; ++i) {
		vector.push_back(i);
	}

	for (const auto& v : vector) {
		std::cout << v << ' ';
	}
	std::cout << std::endl;

	auto other = vector;

	for (const auto& v : other) {
		std::cout << v << ' ';
	}
	std::cout << std::endl;

	return 0;
}