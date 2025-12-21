/**
 *  a static function is a member function (method) of a class that is associated with the class itself rather than with a 
 *  specific instance (object) of the class. This means that you can call a static function using the class name, without needing 
 *  to create an object of that class.
 * 
 *  Here are some key points about static functions in C++:
 * 
 *  1- Belongs to the Class: Static functions are defined within the class definition but are not tied to any specific instance of the class.
 *  They are shared among all instances of the class.
 *
 *   2- No Access to Instance Data: Since static functions are not tied to any instance, 
 *   they do not have access to instance-specific data members or methods. They can only access static data members and other static functions.
 *
 *   3- Cannot Use 'this' Pointer: Since there is no specific instance associated with a static function, 
 *   you cannot use the 'this' pointer inside a static function.
 *
 *   4- Can Access Static Members: Static functions can access static data members and other static functions of the same class directly.
 *
 *   5- Can Be Called Without an Object: Static functions are called using the class name, not an object instance. For example, 
 *   if you have a class named MyClass with a static function staticFunc, you can call it as MyClass::staticFunc().
 * 
 *   use cases:
 * 
 *   1- Utility functions and mathematical operations where the functions are related to the class but they don't need to access to 
 *   the instance-specific data members
 *   
 *   2- They are used in factory (object creation of class) and singelton (ensuring there is only one instance of class) design patterns 
 * 
 */

#include <iostream>


class BasicCalcs{

    public:

    static constexpr double PI = 3.14;

    static float add(float x, float y)
    {
        return x+y;
    }

    static float add(float x, float y, float z)
    {
        return add(x,y)+z;
    }

    static float circumference(float r)
    {
        return 2*PI*r;
    }

};


/* Static method cannot access non-static data member because it is an instance specific related member

class BasicCalcs{

    public:

    float PI = 3.14;

    static float circumference(float r)
    {
        return 2*PI*r;
    }

};
*/



int main()
{
    std::cout<<"circumference: "<<BasicCalcs::circumference(5);

    return 0;
}