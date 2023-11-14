

#include <cstdlib>
#include <iostream>




template<class T>
class Allocator{

    public:

    T* allocate(int n)
    {
        return static_cast<T*>(std::malloc(n*sizeof(T)));
    }

    template<class... Args>
    void construct(T* ptr, Args... args)
    {
        new (ptr) T(args...);
    }

    void destruct(T* ptr)
    {
        if (ptr)
        {
            ptr->~T();
        }
    }

    void deallocate(T* ptr)
    {
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



int main()
{

    Allocator<A> allocator;

    std::cout<<" .............. using malloc ........... \n";
    
    A* ptr = allocator.allocate(10);
    allocator.construct(ptr, 5, 5.5);
    allocator.construct(ptr+1, 6, 6.5);
    std::cout<<ptr->a<<", "<<ptr->b<<"\n";
    std::cout<<(ptr+1)->a<<", "<<(ptr+1)->b<<"\n";

    
    std::cout<<" ........... not using malloc ........... \n";
    
    A ptr1[10];
    allocator.construct(ptr1, 5, 5.5);
    allocator.construct(ptr+1, 6, 6.5);
    std::cout<<ptr1->a<<", "<<ptr1->b<<"\n";
    std::cout<<(ptr1+1)->a<<", "<<(ptr1+1)->b<<"\n";


    unsigned char ptr2[8];
    auto objPtr = new (static_cast<void*>(ptr2)) A(5, 5.5);

    //allocator.construct(static_cast<A*>(static_cast<void*>(ptr2)), 5, 5.5);
    //allocator.construct(ptr2+1, 6, 6.5);
    std::cout<<objPtr->a<<", "<<objPtr->b<<"\n";
    //std::cout<<(ptr1+1)->a<<", "<<(ptr1+1)->b<<"\n";


    return 0;
}