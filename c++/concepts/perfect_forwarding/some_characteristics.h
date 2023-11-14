#ifndef SOME_CHARACTERISTICS_H_
#define SOME_CHARACTERISTICS_H_

#include <type_traits>
#include <iostream>

namespace Example{

// We need first to be aware of two important characteristics of "C++" in order to understand "perfect forwarding" and "remove reference"

// 1) if a type definition (either by using "typedef" or in "template argument") contains already "const" or "&", adding more "const" and "&" expressions 
// will not change the type it already had

// Example
typedef const int ConstInt;
typedef const ConstInt ConstConstInt;
typedef const ConstConstInt ConstConstConstInt;

typedef int& intRef;
typedef intRef& intRefRef;
typedef intRef&& intRefRValRef;
typedef intRefRef& intRefRefRef;

// rvalue: it has no name, it has no identifiable address, it appears usually on the right hand side of an operator
// lvalue: it has name, it has identifiable address, it appears usually on the left side of an operator

// 2) A rvalue reference is converted to lvalue reference when it is passed to a function because it gets a name inside of the function

// If "t" is a rvalue reference, it is mutated to non-const lvalue reference inside of the function
template<class T>
void func_a(T&& t)
{
    auto& ref = t;
    std::cout << std::boolalpha;
    std::cout<<"type of ref is non-const lvalue reference? "<<std::is_same<decltype(ref), T&>::value <<std::endl;
}

// If "t" is a rvalue reference, it is mutated to const lvalue reference inside of the function
template<class T>
void func_b(const T& t)
{
    auto& ref = t;
    std::cout << std::boolalpha;
    std::cout<<"type of ref is const lvalue reference? "<<std::is_same<decltype(ref), const T&>::value<<std::endl;
}

template<class A, class B, int call>
void is_same()
{
    std::cout << std::boolalpha;
    std::cout<<"call: "<<call<<", both types are the same? "<<std::is_same<A, B>::value<<std::endl;
}


};

#endif