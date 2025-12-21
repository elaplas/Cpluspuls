#include <cstdlib>
#include <iostream>

// In the following an object is not created using "new" and it is not a safe code

struct A{
    int x = 5;
    float y = 6;
    A(int a, int b): x(a), y(b){}
};

unsigned char buffer[8];
void* ptr = static_cast<void*>(buffer);
A* ptr1 = static_cast<A*>(ptr);
A* ptr2 = reinterpret_cast<A*>(buffer);

// safe way: ptr = new (buffer) A;
int main()
{
    *ptr2 = A(6,7);
    std::cout<<ptr2->x<<"\n";
    std::cout<<ptr2->y<<"\n";

    *ptr1 = A(8,9);
    std::cout<<ptr1->x<<"\n";
    std::cout<<ptr1->y<<"\n";

    return 0;
}