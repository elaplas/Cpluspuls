#ifndef REMOVE_REFERENCE_H_
#define REMOVE_REFERENCE_H_

namespace Example{

    // this struct can be used to remove the lvalue reference or rvalue reference from a type
    // Usage: When we want to ensure that the parameter signatures of a templated function are certain types regardless of template argument being 
    // lvalue reference "T&", rvalue reference "T&&" or its type "T"

    // remove_reference is for making the function signature types deterministic 

    
    // Forwarding Reference Problem: if "T" is "int" then the parameter signature is rvalue reference "int&&" but if "T" is "int&" 
    // then the parameter signature is lvalue reference "int&"
    // Hint: the passed argument "t" can be lvalue reference or rvalue reference
    template<class T>
    void problem(T&& t)
    {};

    template<class T>
    struct remove_reference
    {
        typedef T type;
    };

    template<class T>
    struct remove_reference<T&>
    {
        typedef T type;
    };

    template<class T>
    struct remove_reference<T&&>
    {
        typedef T type;
    };

    // Solution: no matter if "T" is "int" or "int&", the parameter signature is always rvalue reference "int&&"
    // Hint: the passed argument "t" can only be rvalue reference
    template<class T>
    void solution(typename remove_reference<T>::type&& t)
    {};

};

#endif