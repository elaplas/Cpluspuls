#include <iostream>
#include <memory>

class B; // Forward declaration

class A {
public:
    std::shared_ptr<B> b_ptr;
    ~A() { std::cout << "A destroyed\n"; }
};

class B {
public:
    std::weak_ptr<A> a_ptr; // Weak reference to A
    ~B() { std::cout << "B destroyed\n"; }
};


/*
✅ Both objects are destroyed because there is no ownership cycle. If we used shared_ptr
 instead of weak_ptr for b->a_ptr, it would result in a memory leak.
[a] --shared_ptr--> [b]

[b] --weak_ptr----> [a]

a owns b

b refers to a non-owningly → no cycle

*/
int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();

    a->b_ptr = b;
    b->a_ptr = a; // This is a weak_ptr now

    return 0;
}