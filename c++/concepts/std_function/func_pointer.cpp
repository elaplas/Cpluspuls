
#include <iostream>

/**
 * general:
 * 
 * If a function is defined and then assign to a variable, then the variable
 * should be a pointer to store it. When a function is assign to a function pointer, a copy of it is 
 * passed!
*/

/**
 * how to define function pointers:
*/

typedef int (*TFunc)(int, int); // <output_type> (*<your_chosen_name>)(<input_type1>, <input_type2>);
typedef void (*TFunc1)(float); // <output_type> (*<your_chosen_name>)(<input_type>);

int func(int x, int y)
{
    return x+y;
}


int main()
{
    int value = 5;
    auto fn = [value](int i) mutable {std::cout<<i<<" :"<<"value: "<<value++<<"\n";};
    auto fn1 = fn; // copies function pointer, so fn1 is independent of fn
    auto* fn2 = &fn; // copies the reference/pointer of function pointer, so fn and fn2 are the same!
    fn(0);
    fn(0);
    fn(0);
    (*fn2)(1);
    fn1(2);

    // the usage of function pointer type, as you see the "*" in type definition is an indication that "TFunc"
    // is a pointer
    TFunc func1 = func;
    std::cout<<"func: "<<func1(4,5)<<"\n";

    return 0;
}