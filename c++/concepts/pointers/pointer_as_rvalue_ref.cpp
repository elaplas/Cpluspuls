#include <iostream>




struct A{

    int x = 5;
    float y = 5.5;

};


class B
{
    public:
    using T = A*;

    B(const T& obj): m_obj(obj){
        std::cout<<"B: constructor 1\n";
    }
    B(T&& obj): m_obj(obj){
         std::cout<<"B: constructor 2\n";
    }

    void print()
    {
        std::cout<<"x: "<<m_obj->x<<" ,y: "<<m_obj->y<<"\n";
    }

    private:
    T m_obj;
};

int main()
{
    // rvalue reference of the pointer "A" is passed to the constructor "B"
    // once the rvalue reference of the pointer "A" is passed, it is turned to lvalue 
    // reference of pointer "A" and can be used.

    // Hint: &a returns an rvalue of pointer of class object "a"
    // Hint: rvalue of  pointer of class object "a" is a copy of pointer of "a" that has no identifiable memory location

    A a;
    auto ptrB = new B(&a);
    ptrB->print();

    return 0;
}