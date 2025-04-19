/**
 * Why Use decltype?
Type deduction: Lets you declare variables or function return types based on the type of an expression, 
preserving references and constness.

Template programming: Essential for writing generic code where types may not be known in advance.

Safer and more concise code: Avoids manual type declarations and errors due to type mismatches.
 * 
*/

// 1. Basic Type Deduction
int x = 10;
decltype(x) y = 20; // y is int

// 2. Preserving References
// auto strips references, but decltype preserves them
int x = 42;
int& ref_x = x;

auto a = ref_x;        // a is int (reference is not preserved)
decltype(ref_x) b = x; // b is int& (reference is preserved)

//3. Use with Expressions

struct S { double d; };
const S* s_ptr = new S();

decltype(s_ptr->d) val1;      // val1 is double
decltype((s_ptr->d)) val2 = s_ptr->d; // val2 is const double& (because of extra parentheses)

// 4. Function Return Types in Templates
template<typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

// Using decltype(auto)
int x = 5;
int& y = x;
decltype(auto) z = (y); // z is int&, preserves reference

