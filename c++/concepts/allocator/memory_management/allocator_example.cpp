

#include <cstdlib>
#include <iostream>


/***
 * Allocator class is used to create and destroy an object in the following steps:
 * 1- Allocates uninitialized memory using "malloc"
 * 2- Constructs and initializes the object in-place without copying it (passing directly the initializing arguments into constructor)
 * 3- Destroys and de-initializes the object by calling the object's destructor 
 * 4- deallocate the reserved memory using "free"
 * 
 *  One application of "Allocator" is to allocate and construct an object of any type in-place in heap memory
 * 
*/


template<class T>
class Allocator{

    public:

    T* allocate(int n)
    {
        std::cout<<"a block of memory reserved: "<< n*sizeof(T) << " [bytes]" <<std::endl;
        return static_cast<T*>(std::malloc(n*sizeof(T)));
    }

    template<class... Args>
    void construct(T* ptr, Args... args)
    {
        std::cout<<"one object of type T is (in-place) constructed in memory address: "<<ptr<<std::endl;
        new (ptr) T(args...);
    }

    void destruct(T* ptr)
    {
        if (ptr)
        {
            std::cout<<"one object of type T is destructed in memory address: "<<ptr<<std::endl;
            ptr->~T();
        }
    }

    void deallocate(T* ptr)
    {
        std::cout<<"the reserved block of memory is freed"<<std::endl;
        std::free(ptr);
    }

};



struct A{

    int a;
    float b;

    A(int x, float y): a(x), b(y)
    {
          std::cout<<"customer constructed\n";
    }

    A(){
        std::cout<<"default constructed\n";
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

    Allocator<A> allocator;

    std::cout<<" .............. allocation only (it uses only malloc) ........... \n";

    A* ptr1 = allocator.allocate(10);
    std::cout<<static_cast<A*>(ptr1)->a<<", "<<static_cast<A*>(ptr1)->b<<"\n";


    std::cout<<" .............. allocation and construction (it uses malloc and new) ........... \n";
    
    A* ptr = allocator.allocate(10);
    allocator.construct(ptr, 5, 5.5);
    allocator.construct(ptr+1, 6, 6.5);
    std::cout<<ptr->a<<", "<<ptr->b<<"\n";
    std::cout<<(ptr+1)->a<<", "<<(ptr+1)->b<<"\n";

    
    std::cout<<" ........... construction only....... (it uses only new) .... \n";
    
    A ptr1[10];
    allocator.construct(ptr1, 5, 5.5);
    allocator.construct(ptr+1, 6, 6.5);
    std::cout<<ptr1->a<<", "<<ptr1->b<<"\n";
    std::cout<<(ptr1+1)->a<<", "<<(ptr1+1)->b<<"\n";

    std::cout<<" .............. allocation, construction, destruction and de-allocation ........... \n";

    Allocator<B> allocatorB;
    int sizeArr = 3;
    auto arr = allocatorB.allocate(sizeArr);
    allocatorB.construct(arr, 1, 2, 3);
    allocatorB.construct(arr+1, 4, 5, 6);
    allocatorB.construct(arr+2, 7, 8, 9);
    
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

    allocatorB.destruct(arr);
    allocatorB.destruct(arr+1);
    allocatorB.destruct(arr+2);

    allocatorB.deallocate(arr);

    return 0;
}