

#include <iostream>


/**
 * "alginof" returns the number of memory blocks needed b/w the memory addresses of an object.
 * If it is used for an struct or class the returned value will be the number of memory blocks
 * required b/w the biggest members. The memory block of smaller members will be zero-padded.  
 * 
 * "alignas" set the alignment requirement for a type.
 * 
 */


// objects of type Foo must be allocated at 4-byte boundaries
// because Foo.i must be allocated at 4-byte boundaries
// because int's alignment requirement is 4 bytes.
// for Foo.c three bytes of memory are zero-padded
// therefore the size of foo is 8, and its alignment is 4 
struct Foo
{
    int   i;  // size: 4, alignment: 4
    char  c;  // size: 1, alignment: 1, three bytes of padding bits
}; 


// alignment requirement is set to "4" bytes. the size "char" 
// is less than 4 but it is zero padded, so  it is not a problem
struct  alignas(alignof(int)) Bar
{
    char a;
    int b;
};

// alignment requirement is set to "4" bytes. the size "double" 
// is bigger than 4, so  the following Bar struct cannot be compiled
/*struct  alignas(alignof(int)) Bar
{
    int b;
    double c;
};*/

// alignof of array will return the number of memory blocks in bytes needed b/w two elements
// sizeof will return the size of array in bytes 
int A[10];

// Note 8 bytes are required for storing the address of memory

int main()
{
    std::cout << "Alignment of"  "\n"
        "- char            : " << alignof(char)    << "\n"
        "- int pointer         : " << alignof(double*)    << "\n"
        "- float pointer         : " << alignof(float*)    << "\n"
        "- class Foo       : " << alignof(Foo)     << "\n"
        "- array A       : " << alignof(A)     << "\n";


    std::cout << "Size of"  "\n"
        "- char            : " << sizeof(char)    << "\n"
        "- int pointer         : " << sizeof(double)    << "\n"
        "- float pointer         : " << sizeof(float*)    << "\n"
        "- class Foo       : " << sizeof(Foo)     << "\n"
        "- array A       : " << sizeof(A)     << "\n";

    return 0;
}