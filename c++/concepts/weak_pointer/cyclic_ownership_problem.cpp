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

a points to b and b points back to a.

Both have shared_ptrs → reference count never reaches 0 → destructors never called.

a owns b

b owns a → cycle

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

    return 0;
}