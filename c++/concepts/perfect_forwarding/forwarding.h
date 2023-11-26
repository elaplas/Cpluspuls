#ifndef PERFECT_FORWARDING_H_
#define PERFECT_FORWARDING_H_

#include "remove_reference.h"

/**
 * perfect forwarding is a powerful mechanism that ensures arguments
 *  are passed with their original value categories intact, facilitating generic 
 * programming and efficient resource management without unnecessary copies or modifications
 * 
 */

// Perfect forwarding: 

// 1) For passing "t" as lvalue reference if "T" is a lvalue reference and "t" is lvalue reference 
// 2) For passing "t" as rvalue reference if "T" is not a lvalue reference and "t" is a lvalue reference

namespace Example{

template<class T>
T&& forward(typename remove_reference<T>::type& t)
{
    return static_cast<T&&>(t);
}

// 3) For passing "t" as rvalue reference if "T" is not a lvalue reference and "t" is a rvalue reference
// 4) if "t" is a rvalue reference and "T" is lvalue reference, then it fails and cannot be converted to "lvalue"

template<class T>
T&& forward(typename remove_reference<T>::type&& t)
{
    static_assert(!std::is_lvalue_reference<T>::value, "template argument"
		    " substituting T is an lvalue reference type");
    return static_cast<T&&>(t);
}

// Move a variable ---> casting from lvalue to rvalue 

template<class T>
remove_reference<T>::type&& myMove(remove_reference<T>::type& t)
{
    return static_cast<remove_reference<T>::type&&>(t);
}


};

#endif