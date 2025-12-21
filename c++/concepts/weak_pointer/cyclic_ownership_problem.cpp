#include <iostream>
#include <memory>

/*
A std::weak_ptr in C++ is a smart pointer that provides non-owning access to an object 
managed by a std::shared_ptr. It helps break cyclic references, which can prevent memory from being freed.
*/


class B; // Forward declaration

class A {
public:
    std::shared_ptr<B> b_ptr;
    ~A() { std::cout << "A destroyed\n"; }
};

class B {
public:
    std::shared_ptr<A> a_ptr; // ❌ shared_ptr causes cycle!
    ~B() { std::cout << "B destroyed\n"; }
};

/*

No output!!!

❗ Why?

becaue when shared_ptr of A goes out of scope, the reference count is decremented by 1
but the reference count is still not zero to execute "delete A pointer" and consequently
to call the destructor of A and to cause the shared_ptr of B to decrement its reference 
count by 1. So the shared_ptr of A never runs "delete A pointer" and destructor of A.   

Both have shared_ptrs → reference count never reaches 0 → destructors never called.

*/

struct D;
struct C{
    D* ptr_d;
    ~C(){
        std::cout << "C destroyed\n";
    }
};
struct D{
    C* ptr_c;
    ~D(){
        std::cout << "D destroyed\n";
    }
};

int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    std::cout<<a.use_count()<<"\n";

    a->b_ptr = b;
    b->a_ptr = a;

    std::cout<<a.use_count()<<"\n";

    C c;
    D d;
    c.ptr_d = &d;
    d.ptr_c = &c;

    // what happens when a1 goes out of scope:
    // a1 goes out of scope and calls its destructor and it doesn't exist any more. Thus
    // the shared_ptr of B goes out of scope and calls its destructor decremeting the 
    // reference count by one. The reference count becomes zero, so " delete B pointer"
    // is executed and the destructor of B is called. Since B contains a shared_ptr of A
    // and goes out of scope, the destructor of A shared_ptr is called but it doesn't have any 
    // effect because the reference count is decremented and become zero but the A raw
    // pointer is already nullptr.  
    A a1; 
    a1.b_ptr = std::make_shared<B>();

    return 0;
}