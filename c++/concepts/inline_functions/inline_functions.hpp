

/***
 * 
 * The main idea behind inline functions is to reduce the overhead of function calls, especially for small and frequently used functions.
 * When the function is called in the main function, the compiler replaces the function call with the actual function code, effectively inlining it.
 * 
 * Not all functions should be declared as inline. Generally, functions with larger or complex bodies might not be good candidates for inlining.
 * Modern compilers are often capable of automatically determining whether a function should be inlined, even without the inline keyword.
 * Inline functions are typically defined in header files to ensure that the function's definition is available at the call site.
*/



#include <iostream>

// Declaration of an inline function
inline int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(5, 3);  // The function is expanded here

    std::cout << "Result: " << result << std::endl;

    return 0;
}
