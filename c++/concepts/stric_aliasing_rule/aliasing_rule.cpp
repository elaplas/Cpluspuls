/**
 The Strict Aliasing Rule in C++ is a compiler optimization rule that assumes two pointers of different 
 types do not point to the same memory (i.e., they don’t alias).

 This rule allows compilers to generate faster code, but if you violate it,
 the behavior is undefined — meaning the program might crash, behave strangely, or silently fail.

 Aliasing means two different expressions access the same memory location.
*/


#include <iostream>

int main() {
    float f = 3.14f;
    int* p = (int*)&f;        // ❌ bad: reinterpret cast breaks strict aliasing
    *p = 42;                  // modifying as int

    std::cout << f << std::endl;  // Undefined behavior!
    return 0;
}