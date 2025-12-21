#include <iostream>


struct A{
    int x;
    int y;
    A() {}
    A(int a, int b):x(a), y(b){}
    A& operator=(const A& a)
    {
        std::cout<<"copy assignment"<<"\n";
    }
    A& operator=(A&& a)
    {
        std::cout<<"move assignment"<<"\n";
    }
    A(const A& a)
    {
        std::cout<<"copy assignment"<<"\n";
    }
    A(A&& a)
    {
        std::cout<<"move constructor"<<"\n";
    }
};

void work(A& )  { std::cout << "work(lvalue)\n"; }
void work(A&& ) { std::cout << "work(rvalue)\n"; }

template<class T>
void logger(T&& x)
{
    std::cout << "calling work...\n";
    work(std::forward<T>(x)); // perfect forwarding
}

void bad_logger(A& a){
    work(a);
}

void bad_logger(A&& a){
    work(a);
}

int main() {
    A a(1,2);
    logger(a);   // work(lvalue): T of templated logged_call replaced by U&, T&& becomes U&&& collapsing to U&, so we can pass lvalue
    logger(A(3,4));  // work(rvalue)

    std::cout<<"...............................\n";
    bad_logger(a);
    bad_logger(A(1,2));
    return 0;
}

/* From above example we can see by perfect forwarding there is no need to write 
overloading functions, the rvale-ness and lvalue-ness are preserved.


*/