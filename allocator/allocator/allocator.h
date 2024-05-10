#pragma once

#include <type_traits>
#include <cstdlib>
#include <exception>

template<typename T>
class my_allocator
{
    static_assert(!std::is_same_v<T, void>, "Type of the allocator can't be void");

//Common interface for stl support
public:
    using value_type = T;

    template< class U >
    struct rebind
    {
        typedef my_allocator<U> other;
    };

public:

	explicit my_allocator(std::size_t N = 10) : m_elements(N), m_reserved(0){
         m_mem = static_cast<T*>(std::malloc(N * sizeof(value_type)));
         m_ptr = m_mem;
    };

    ~my_allocator() {
        std::free(m_mem);
    }

    my_allocator(const my_allocator& other) noexcept = default;

    template< class U >
    my_allocator(const my_allocator<U>& other) noexcept {};
    

    T* allocate(std::size_t n) {
        if (n + m_reserved > m_elements) {  // if the number of allocated elements is greater, then free space
            std::bad_alloc();
        }
        m_reserved += n;

        T* return_ptr = m_ptr;
        m_ptr += n;

        return return_ptr;
    }

    void deallocate(T* ptr, std::size_t n) {

    }

    template<typename U, typename... Args>
    void construct(U* ptr, Args&&... args)
    {
        new (reinterpret_cast<void*>(ptr)) U{ std::forward<Args>(args)... };
    }

    void destroy(T* p) {
        p->~T();
    }

    template<typename U>
    void destroy(U* ptr)
    {
        ptr->~U();
    }

private:
    std::size_t m_elements;
    std::size_t m_reserved;

    T* m_mem;
    T* m_ptr;
};

