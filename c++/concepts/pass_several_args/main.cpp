#include <iostream>

void print(int i, float x)
{
    std::cout<<"int: "<<i<<" , float: "<<x<<std::endl;
}

void print(int i, float x, char c)
{
    std::cout<<"int: "<<i<<" , float: "<<x<< " , char: "<<c<<std::endl;
}

// variadic templates
template<class... T>
void func(T&... args)
{
    print(args...);
}

int main()
{
    int i= 9;
    float x = 5.5;
    char c = 't';


    func(i, x);
    func(i, x, c);

    return 0;
}