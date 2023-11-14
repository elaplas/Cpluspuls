#include <iostream>

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
    // Reserve 8 bytes of memory
    unsigned char ptr2[8];
    // remove the type of reserved memory pointer and pass it to "new"
    auto objPtr = new (static_cast<void*>(ptr2)) A(5, 5.5);
    // Check the correctness of the allocation and construction 
    std::cout<<objPtr->a<<", "<<objPtr->b<<"\n";

    return 0;
}