#include <iostream>

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

    A& operator=(const A&)
    {
        std::cout<<"copy asignment is called!"<<std::endl;
        return *this;
    }

    A& operator=(A&&)
    {
        std::cout<<"move asignment is called!"<<std::endl;
        return *this;
    }
};


int main()
{
   A a;
   A b = a;
   A c(a);
   b = a; 
   A d = std::move(a);
   A e(std::move(b));
   A f;
   f = std::move(c);
   A g = A(); 
}

/* results:
default constructor is called!
copy constructor is called!
copy constructor is called!
copy asignment is called!
move constructor is called!
move constructor is called!
default constructor is called!
move asignment is called!
default constructor is called! // reason: Most C++14 compilers perform copy/move elision for 
//simple temporary initialization, so the temporary A() is constructed directly in the storage 
of g, and no move or copy occurs. Without compiler optimization, first the rvalue of A is connstructed 
by default constructor and then the move constructor is called. 
*/