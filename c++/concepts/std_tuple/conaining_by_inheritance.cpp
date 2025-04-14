#include <iostream>


// Struct for storing one generic element
template<int I, class T>
struct element{
    T value;

    element(T val): value(val){};

    T get() {return value;};
};


// class A conains/includes three elements through inheritance and not aggregation!
struct A: element<0, int>, element<1, float>, element<2, double>
{
    A(int i, float f, double d):element<0, int>(i), element<1, float>(f), element<2, double>(d){}
};


// accessing the content/elements of A by casting it to its base types
template<int I, class T>
T get(element<I, T>& el)
{
    return el.get();
}


int main()
{
    A a(1, 1.5, 0.999999);

    std::cout<<get<0, int>(a)<<"\n";
    std::cout<<get<1, float>(a)<<"\n";
    std::cout<<get<2, double>(a)<<"\n";

    std::cout<<get<0>(a)<<"\n";
    std::cout<<get<1>(a)<<"\n";
    std::cout<<get<2>(a)<<"\n";

    return 0;
}