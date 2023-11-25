

/**
 * static_cast:

The static_cast operator is used for performing safe and implicit conversions between compatible types during compile-time. 
It's commonly used for basic type conversions, such as numerical types, pointers, references, and casting up the inheritance 
hierarchy when you are confident about the type relationships. Here are the key aspects of static_cast:

    - Used for compile-time type conversions.
    - Used when you are confident that the conversion is valid and there is no runtime overhead for checking.
    - Performs basic type conversions and is useful for casting between related types.
    - Not suitable for casting between unrelated types 



 The dynamic_cast operator is used for performing type conversions that involve polymorphic classes (classes with virtual functions)
 and are checked at runtime. It's used when you need to ensure the correctness of the conversion and need runtime type checking. 
 Here are the key aspects of dynamic_cast:

    - Used for runtime type conversions in polymorphic class hierarchies.
    - Used when you need to ensure the validity of the conversion, especially when casting pointers or references of base classes to derived classes.
    - Requires the classes involved to have at least one virtual function (polymorphic behavior).
    - Performs a check at runtime to verify whether the conversion is valid.
    - Returns a null pointer if the conversion fails (for pointers) or throws a std::bad_cast exception  
 * 
 * 
 * 
 */

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

    A* ptrA = new B;
    //std::cout<<dynamic_cast<B*>(ptrA)->b<<"\n";  // error: A and B are not polymorphic classes because they dont have any virtual functions
    std::cout<<static_cast<B*>(ptrA)->b<<"\n";  // no error but wrong usage of static_cast: A and B are not the same type and polymorphic (down-casting). The behavior is undefined. 

    C* ptr = new D;
    std::cout<<dynamic_cast<D*>(ptr)->b<<"\n"; // no error and correct usage because C and D are polymorphic
    std::cout<<static_cast<D*>(ptr)->b<<"\n"; // no error but wrong usage of static_cast since A and B are not the same type

    

    // up-casting

    A* ptr1 = static_cast<A*>(new B()); // no error and correct usage because the derived class has the same type as base class (up-casting)
    A* ptr2 = dynamic_cast<A*>(new B()); // no error because the derived class has the same type as base class (up-casting)

    return 0;
}