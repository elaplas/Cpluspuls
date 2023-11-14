#include <cstddef>
#include <iostream>

// std::ptrdiff_t is the signed integer type for the result of subtracting two pointers.
// std::ptrdiff_t is used for pointer arithmetic and array indexing. Programs that use other 
// types, such as int, may fail on, e.g. 64-bit systems when the index exceeds INT_MAX or 
// if it relies on 32-bit modular arithmetic.

// When working with the C++ container library, the proper type for the difference between
// iterators is the member typedef difference_type, which is often synonymous with 
// std::ptrdiff_t. 



int main()
{
    const unsigned int arrSize = 10;
    int* startPtr = new int[arrSize];
    int* endPtr = &startPtr[arrSize];

    for (std::ptrdiff_t i = arrSize; i > 0; --i)
    {
        *(endPtr - i) = i;
        std::cout<<*(endPtr - i)<<std::endl;
    }
    return 0;
}