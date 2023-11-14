#include <iostream>
#include <cstdlib>

#pragma

template<class T>
class allocator {

    public:

        typedef T value_type;

        allocator() = default;

        template<class U>
        allocator(const allocator<U>& other) noexcept{}

        // Reserves a memory block with size "n" (no construction and no initialization) 
        // and returns the address of the beginning of the memory block
        T* allocate(size_t n)
        {
            std::cout<<"a block of memory reserved: "<< n*sizeof(T) << " [bytes]" <<std::endl;
            return static_cast<T*>(std::malloc(n*sizeof(T)));
        }

        // Creates an object of type "T" at position "ptr" by passing the corresponding arguments 
        // to the constructor of type "T". It involves no copy at construction (in-place construction)
        template<class... Args>
        void construct(T* ptr, Args... args)
        {
            std::cout<<"one object of type T is (in-place) constructed in memory address: "<<ptr<<std::endl;
            new ((void*)ptr) T(args...);
        }

        // Deallocate memory without destructing the stored objects
        void deallocate(T* ptr, size_t n) noexcept
        {
            std::cout<<"the reserved block of memory is freed"<<std::endl;
            std::free(ptr);
        }

        // Destruct an object in memory
        void destroy(T* ptr)
        {
            std::cout<<"one object of type T is destructed in memory address: "<<ptr<<std::endl;
            ptr->~T();
        }
};

