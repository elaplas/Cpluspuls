#include<iostream>



class A{

    public:

    A()
    {
        std::cout<<"default constructor is called!"<<std::endl;
    }


    A(const A&)
    {
        std::cout<<"copy constructor is called!"<<std::endl;
    }

    A(A&&)
    {
        std::cout<<"move constructor is called!"<<std::endl;
    }
};


void func1(A&& a)
{
    
}


void func2(A a)
{
    
}

int main()
{
    // The rvalue is passed by rvalue reference. The rvalue is turned to lvalue inside function.
    func1(A());

    // The rvalue is passed by value. It is expected that the compiler first makes a copy of rvalue and then passes that copy 
    // to the function but the compiler performs some optimizations and passes directly the rvalue.
    func2(A());

    // The rvalue is passed by value. The compiler first makes a copy of rvalue and then passes that copy 
    // to the function. The copy of rvalue is an lvalue.
    A a;
    func2(std::move(a));

    return 0;
}