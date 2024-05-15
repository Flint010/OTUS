#pragma once

#include <type_traits>
#include <cstdlib>
#include <exception>


template<size_t N_byte>
struct Memory {
    std::size_t m_reserved = 0;
    char m_mem[N_byte] = { 0 };
};

template<typename T, size_t N>
class my_allocator
{
    static_assert(!std::is_same_v<T, void>, "Type of the allocator can't be void");

//Common interface for stl support
public:
    using value_type = T;

    template<typename U, size_t N>
    friend class my_allocator;

    template< class U >
    struct rebind
    {
        typedef my_allocator<U, N> other;
    };

public:

    explicit my_allocator(): m_memory(new Memory<sizeof(value_type) * N>){
        
    };

    ~my_allocator() {
        delete m_memory;
        m_memory = nullptr;
    }

    my_allocator(const my_allocator& other) noexcept
        : m_memory(other.m_memory) {}

    template< typename U >
    my_allocator( my_allocator<U, N>& other) noexcept 
       {}

    value_type* allocate(std::size_t n) {
        if (m_memory == nullptr) {
            m_memory = new Memory<sizeof(value_type) * N>;
        }

        //if (m_reserved == 0) {
        //    //reserved();
        //}

        if (n + m_memory->m_reserved > N) {  // if the number of allocated elements is greater, then free space
           throw std::bad_alloc();
        }

        //m_reserved += n;

        //T* return_ptr = m_ptr;
        //m_ptr += n;
        
        value_type* return_ptr = reinterpret_cast<value_type*>(&(m_memory->m_mem[m_memory->m_reserved]));
        m_memory->m_reserved += n;

        return return_ptr;
    }

    void deallocate(T* ptr, std::size_t n) {
        
    }

    template<typename U, typename... Args>
    void construct(U* ptr, Args&&... args)
    {
        new (reinterpret_cast<void*>(ptr)) U{ std::forward<Args>(args)... };
    }

    void my_deallocate() {
        delete m_memory;
    }

    template<typename U>
    void destroy(U* ptr)
    {
        ptr->~U();
    }

private:
    Memory<sizeof(value_type)*N>* m_memory = nullptr;
};
