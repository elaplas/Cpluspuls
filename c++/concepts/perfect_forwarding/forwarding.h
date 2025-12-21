#ifndef PERFECT_FORWARDING_H_
#define PERFECT_FORWARDING_H_

#include "remove_reference.h"
#include "is_lvalue.h"

/**
 * perfect forwarding ensures arguments are passed with their original value categories 
 * (rvalue or lvalue). It preserves the rvalue-ness - and lvalue-ness of objects when they are
 * passed/forwarded in another function. 
 * 
 * 
 * intact, facilitating generic 
 * programming and efficient resource management without unnecessary copies or modifications
 * 
 */

namespace Example{

// Perfect forwarding: 

// If lvalue passed, T becomes U&, then T&& becomes U&&& collapsing to U& resulting in preserving lvalue-ness
template<class T>
T&& forward(typename remove_reference<T>::type& t)
{
    return static_cast<T&&>(t);
}

// If rvalue passed, T becomes U, then T&& becomes U&& resulting in preserving rvalue
// Hint: if T refers to lvalue (U&) then it throws an error
template<class T>
T&& forward(typename remove_reference<T>::type&& t)
{
    static_assert(!std::is_lvalue_reference<T>::value, "template argument"
		    " substituting T is an lvalue reference type");
    return static_cast<T&&>(t);
}

// Moving is not forwarding! 
//moving: casting from lvalue to rvalue 
//forwarding: preserving lvalue-ness and rvalue-ness

template<class T>
remove_reference<T>::type&& myMove(remove_reference<T>::type& t)
{
    return static_cast<remove_reference<T>::type&&>(t);
}

};

#endif