/**
 * 
 * To resolve the diamond problem, C++ introduced the concept of "virtual inheritance." 
 * By declaring the inheritance from A in B and C as virtual, you ensure that there's only
 * one instance of the common base class A in the hierarchy. Here's how it would look:
 * 
 */


#include <iostream>

class A {
public:
    void foo() { std::cout << "A::foo()" << std::endl; }
};

class B : virtual public A {};

class C : virtual public A {};

class D : public B, public C {};

int main() {
    D d;
    d.foo();  // No ambiguity, calls A::foo()
    return 0;
}