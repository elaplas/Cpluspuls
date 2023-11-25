#include <iostream>


// using const for preventing the unintentional modifications

const float pi = 3.14;   // pi is a run-time constant
const float* ptr = &pi; // pointer to  a float constant
float func(const float& x) // a constant function parameter
{
    return 2*x;
}

// using constexpr for improving the performance by compile-time computations

constexpr int factorial(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else if (n <= 0)
    {
        return 0;
    }
    else
    {
        return n*factorial(n-1);
    }
}

constexpr int x = factorial(4);

int main(int argc, char **argv)
{
    static_assert( x == 24, "x has not been calculated correctly");
    
    return 0;
}