
#include <iostream>


class A{
    public:
    int a = 1;
};


class B: public A{
    public:
    int b = 5;
};


class C{
    public:
    int a = 1;
    virtual void func(){}
};


class D: public C{
    public:
    int b = 5;
    virtual void func() override{ std::cout<<"fuck\n";}
};




int main()
{
    // down-casting 

    //A* ptr = new B;
    //std::cout<<dynamic_cast<B*>(ptr)->b<<"\n";  // error: A and B are not polymorphic classes because they dont have any virtual functions
    //std::cout<<static_cast<B*>(ptr)->b<<"\n";  // error: A and B are not the same type because it is down-casting and they are not polymorphic

    C* ptr = new D;
    std::cout<<dynamic_cast<D*>(ptr)->b<<"\n"; 
    std::cout<<static_cast<D*>(ptr)->b<<"\n";

    

    // up-casting

    A* ptr1 = static_cast<A*>(new B()); // no error because the derived class has the same type as base class (up-casting)
    A* ptr2 = dynamic_cast<A*>(new B()); // no error because the derived class has the same type as base class (up-casting)

    return 0;
}