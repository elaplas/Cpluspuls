
#include <iostream>

// Recursive template 
template<int N>
struct Factorial{

    static constexpr int value = N * Factorial<N-1>::value;
};

// Without base case the recursion will continue untill it exceeds the maximum depth
template<>
struct Factorial<1>
{
    static constexpr int value = 1;
};


int main()
{

    std::cout<<"Factorial: "<<Factorial<5>::value<<"\n";
    return 0;
}