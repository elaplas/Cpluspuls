#include <iostream>




struct A{

    int x = 5;
    float y = 5.5;

};


class B
{
    public:
    using T = A*;

    B(const T& obj): m_obj(obj){}
    B(T&& obj): m_obj(obj){}

    void print()
    {
        std::cout<<"x: "<<m_obj->x<<" ,y: "<<m_obj->y<<"\n";
    }

    private:
    T m_obj;
};


class C
{
    public:
    using T = A*;

    C(T obj): m_obj(obj){}

    void print()
    {
        std::cout<<"x: "<<m_obj->x<<" ,y: "<<m_obj->y<<"\n";
    }

    private:
    T m_obj;
};

B* creator()
{
    A a;
    return new B(&a);
}

C* creator2()
{
    A a;
    return new C(&a);
}

int main()
{
    // rvalue reference of the pointer "A" is passed to the constructor "B"
    // once the rvalue reference of the pointer "A" is passed, it is turned to lvalue 
    // reference of pointer "A" and can be used
    auto ptr = creator();
    ptr->print();

    // rvalue reference of the pointer "A" is passed to the constructor "C"
    // once the rvalue reference of the pointer "A" is passed, it is turned to lvalue 
    // reference of pointer "A" and can be used
    auto ptr2 = creator2();
    ptr2->print();

    return 0;
}