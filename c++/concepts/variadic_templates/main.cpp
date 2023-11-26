
/**
 * variadic templates are used when an API is going to be called without knowing how many arguments and which types of 
 * arguments should be passed into it. For example when the constructor of an unkown type T is called. 
 * 
 * 
 */


#include <iostream>

// implementations of API "print"
void print(int i, float x)
{
    std::cout<<"int: "<<i<<" , float: "<<x<<std::endl;
}

void print(int i, float x, char c)
{
    std::cout<<"int: "<<i<<" , float: "<<x<< " , char: "<<c<<std::endl;
}

// variadic template is used because the API "print" is called inside "func"
// without knowing upfront which types or how many arguments should be passed into "print".
// The assumption is that we don't know anything about "print" parameters. 
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