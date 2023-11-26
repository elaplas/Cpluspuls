#include <iostream>


/**
 * A dangling pointer situation occurs when a pointer continues to point to a memory 
 * location that has been deallocated or has gone out of scope. Accessing 
 * or using such a pointer can lead to undefined behavior, as the memory it points to may 
 * have been reused for other purposes or might no longer hold valid data
 *  
 */


int* createInt() {
    int value = 10;
    int* ptr = &value; // Pointer pointing to a local variable

    return ptr;
}

struct A{

    int x = 5;
    float y = 5.5;

};


class C
{
    public:
    using T = A*;

    C(T obj): m_obj(obj){
        std::cout<<"C: constructor 1\n";
    }

    void print()
    {
        std::cout<<"x: "<<m_obj->x<<" ,y: "<<m_obj->y<<"\n";
    }

    private:
    T m_obj;
};

C* creator()
{
    A a;
    return new C(&a);
}

int main() {
    
    int* danglingPtr = createInt(); // Function returns a pointer to a local variable

    // At this point, danglingPtr points to a local variable that has gone out of scope
    // Attempting to access the value through the dangling pointer leads to undefined behavior
    std::cout << *danglingPtr << std::endl;

    auto ptr2 = creator();
    ptr2->print();

    return 0;
}