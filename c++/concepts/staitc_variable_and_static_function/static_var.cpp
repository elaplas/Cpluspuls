/**
 * In C++, a static data member (also known as a static member variable) is a class member that belongs to the class itself rather than 
 * to any specific instance (object) of the class. This means that all instances of the class share the same static data member. 
 * Static data members are declared using the static keyword within the class definition.

Here are some important points about static data members in C++:

1.Shared Among Instances: Static data members are shared among all instances of the class. This means that any changes
 made to the static data member through one instance will affect the value of the static data member for all other instances as well.

2.One Copy: There is only one copy of a static data member that is shared among all instances of the class.
 This is in contrast to regular (non-static) data members, where each instance has its own separate copy.

3. Initialization: Static data members can be initialized at the point of declaration, just like regular data members.

4. Access: Static data members can be accessed directly using the class name, followed by the scope resolution operator (::). 
They can also be accessed using the class's objects, but this is less common and not recommended.

5. Memory Allocation: The memory for a static data member is allocated separately from the objects of the class. 
It is typically stored in the static memory area.

6. Lifetime: The lifetime of a static data member extends for the entire duration of the program.

Use cases:

    1. Shared Information: Static data members allow you to maintain information that needs to be shared among all instances of the class. 
    For example, you might use a static data member to keep track of the total number of instances created from the class.

    2. Class-Level Configuration: If you have configuration settings or constants that are applicable to the entire class, 
    you can use static data members to store them. This avoids duplication and ensures consistent behavior across all instances.

    3. Resource Management: Static data members can be used to manage resources that need to be shared among all objects. 
    For instance, a static data member might hold a shared database connection or a shared resource pool.

    4.Performance Optimization: In some cases, using a static data member can help optimize memory usage and improve performance by 
    sharing data among instances instead of duplicating it.
  
 * 
 * 
*/

#include <iostream>

// Static data member used for sharing and updating the current number of instances of class
class Pointer{

    public:

    Pointer(int* ptr): m_ptr(ptr){
        ++counter;
        std::cout<< "number of instances: "<<counter<<"\n";
    }

    static int counter;

    private:
    int* m_ptr;
};

int Pointer::counter = 0;

// Static data member used for sharing a constant among all class instances
class Circle{

    public:

    static constexpr float PI = 3.14;

    Circle(int r): m_r(r){}

    float circumference(){return 2*PI*m_r;}

    float area(){return PI*m_r*m_r;}

    private:
    float m_r;
};

int main(int argc, char** argv)
{
    
    auto rawPtr1 = new int(4);
    auto rawPtr2 = new int(5);

    Pointer ptr1(rawPtr1);
    Pointer ptr2(rawPtr2);

    Circle circle(1.0);

    std::cout<<"circumference: "<<circle.circumference()<<"\n";
    std::cout<<"area: "<<circle.area()<<"\n";

    return 0;
}