/**
 *  a const member function is a function declared within a class that will not modify the state
 *  of the calling object. This is a way to provide a guarantee that the member function won't change 
 *  the object's internal data members. 
 * 
 * Here are some key points about const member functions:
 * 
 *  1- Syntax: The const keyword is placed after the parentheses of the member function declaration, 
 *  both in the class definition and in its implementation.

    2- Access to Members: Inside a const member function, you are not allowed to modify the non-static data members of the class, 
    except for those members that are declared as mutable.

    3- Use with Objects: const member functions are called on a const object. 
    This ensures that the function doesn't accidentally modify the object's state.

    4- Overloading: You can provide both const and non-const versions of member functions, 
    allowing you to call the appropriate version based on whether the object is const or not.

    5- Return Value: If a member function doesn't modify the object's state and only provides read-only access, 
    it should be declared as const. This allows you to call that function on const objects and get meaningful results.

  Use case:
   Using const member functions is a good practice because it helps enforce the principle of not modifying objects
   unintentionally and enhances the safety and clarity of your code.


 */
#include <iostream>

class A{

    public:

    const int& getX() const {
        std::cout<<"const version of getX is called\n";
        return x;
    };

    int& getX() {
        std::cout<<"non-const version of getX is called\n";
        return x;
    };

    void modifyY(int y) const{
        std::cout<<"const version of modifyY is called\n";
        Y = y;
    };

    void modifyY(int y){
        std::cout<<"non-const version of modifyY is called\n";
        Y = y;
    };

    static float Y;

    private:
    int x;
};

float A::Y = 3.5;



int main()
{
    //Hint: const member functions are called on const reference of class object
    //Hint: const member function can modify static data members
    A a;
    const A& constRefA = a;
    constRefA.getX();
    constRefA.modifyY(6.2);
    std::cout<<"the value of static data member Y: "<<A::Y<<"\n";
    A& refA = a;
    refA.getX();
    refA.modifyY(7.3);
    std::cout<<"the value of static data member Y: "<<A::Y<<"\n";

    return 0;
}