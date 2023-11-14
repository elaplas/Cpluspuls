
#include <iostream>
#include <cstdlib>



/* One application of allocator is to construct an array elements in-place without copying e.g.
   calling copy constructor
*/



template<class T>
class Allocator{
public:
    T* allocate(int n) {
        auto objPtr = std::malloc(sizeof(T)*n);
        return static_cast<T*>(objPtr);
    }

    template<class... Args>
    void construct(T* objPtr, Args... args)
    {
        new (objPtr) T(args...);
    }

    void deallocate(T* ptr)
    {
        std::free(ptr);
    }

    void destruct(T* ptr)
    {
        ptr->~T();
    }
};


struct B
{
    int x;
    int y;
    int z;

    B(int x1, int y1, int z1): 
    x(x1),
    y(y1),
    z(z1)
    {}
};


int main()
{
    Allocator<B> allocator;
    int sizeArr = 3;
    auto arr = allocator.allocate(sizeArr);
    allocator.construct(arr, 1, 2, 3);
    allocator.construct(arr+1, 4, 5, 6);
    allocator.construct(arr+2, 7, 8, 9);
    
    std::cout<<".....first element in array..."<<std::endl;
    std::cout<<arr->x<<std::endl;
    std::cout<<arr->y<<std::endl;
    std::cout<<arr->z<<std::endl;

    std::cout<<".....second element in array..."<<std::endl;
    std::cout<<arr[1].x<<std::endl;
    std::cout<<arr[1].y<<std::endl;
    std::cout<<arr[1].z<<std::endl;

    std::cout<<".....third element in array..."<<std::endl;
    std::cout<<arr[2].x<<std::endl;
    std::cout<<arr[2].y<<std::endl;
    std::cout<<arr[2].z<<std::endl;

    allocator.destruct(arr);
    allocator.destruct(arr+1);
    allocator.destruct(arr+2);

    allocator.deallocate(arr);
    
    return 0;
}