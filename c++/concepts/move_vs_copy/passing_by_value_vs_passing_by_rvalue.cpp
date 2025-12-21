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

class B1{
    public:
        B1(){}
        // this constrcutor supports passing by rvalue ref but not passing by value 
        B1(A&& a) // once the a is inside the function, it is turned to a lvalue ref, so we need to
        {         // move it again to assign the rvalue of it to "m_a" and avoid copy assignment (copying)
            m_a = std::move(a);
        }

    private:
    A m_a;
};

class B2{
    public:
        B2(){}

        // this constrcutor supports only passing by value but not passing by rvalue ref
        B2(A a)
        {   // we need to move it to assign the rvalue of it to "m_a" because the argument a is lvalue 
            // hint: passing by value is lvalue
            m_a = std::move(a); // a will be moved and no copying
        }

    private:
    A m_a;
};

class B3{
    public:
        B3(){}

        B3(A a)
        {
            // copy assignment is called to put "a" to "m_a" so a will be copied. 
            m_a = a;
        }

    private:
    A m_a;
};

/* having two constuctors like the following will lead to ambigity (two identical overloded
functions from compiler point of view)
class B4{
    public:
        B2(){}

        B1(A&& a)
        {
            m_a = std::move(a);
        }

        B2(A a)
        {
            m_a = a;
        }

    private:
    A m_a;
};*/

int main()
{
    std::cout<<".......................................\n";
    A a(2,3);
    B1 b1(std::move(a));
    B1 b2(A(4,5));
    std::cout<<".......................................\n";
    A a1(6,7);
    B2 b4(a1); // becaue a1 is lvalue, a copy of it by copy constructor is created and passed to B2 constructor 
    B2 b6(std::move(a1)); // becaue a1 is rvalue since it is moved, a copy of it by move constructor is created and passed to B2 constructor
    B2 b7(A(1,1)); // compiler turn rvalue ref to a lvalue copy (optimization) and then the copy is passed to B2 constructor
    std::cout<<"........................................\n";
    return 0;
    B2 b3(A(1, 2));
    std::cout<<"........................................\n";
    return 0;
}