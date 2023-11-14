#include <iostream>

/** AspectRation is preferred to ASPECT_RATIO because
   * 1- saves replacement action
   * 2- ASPECT_RATIO (define consts) can not been seen sometimes by compilers
   */
#define ASPECT_RATIO 1.777
const float AspectRation = 1.777;

void printIt(float a) {
  std::cout << a << std::endl;
}


/// const std::string is preferable to const char* const
const char* const myString1 = "Ebrahim";
const std::string myString2{"Goodarzi"};

void PrintString(){
  std::cout << myString1 << std::endl;
  std::cout << myString2 << std::endl;
}


/** The const is defined in a class to
 * 1- To limit the scope of a const to class
 * 2- The const member variable is shared with outside of class, so it has to be static
 * 3- To make sure there is only one copy of const variable, it shall be static
 * 4- only one instance of static const variable is shared among all instances of class
 * 5- To be able to pass it in functions with pass-by-reference value, it shall be defined in impl scope of class
 * 6- non-integral static const e.g. static const float cannot be initialized in declaration scope of class
 */

class A{
 public:
  static const float AspectRatio_;
};

const float A::AspectRatio_ = 1.777;


/** in C++ everything has to be defined before it is used but the integral types are exceptions
 *  if we wanna use consts in declaration scope, they shall be defined as following otherwise it cannot be compiled
 *  1- static constexpr ...
 *  2- enum{..}
 */

/*class B{
 public:
  const int mySize = 20;
  float myArray[mySize];   //cannot be compiled
};*/

class B{
 public:
  static constexpr int mySize = 20;
  float myArray[mySize];
};

class C{
 public:
  enum{ mySize = 20}; /// this is also called enum hack technique
  float myArray[mySize];
};

/** static consts are defined inside a struct because
 * 1- To limit the scope to the struct
 * 2- To be used outside of struct, they are declared as static
 * 3- They shall not be initialized and defined in declaration scope
 */
struct MyData{
  static const float X ;
  static const float Y ;
};

const float MyData::X = 1.11;
const float MyData::Y = 2.22;



/** The small functions are declared and defined as function-like Macro or inline function to
 *   save the overhead of processor for switching between caller and callee because the execution overhead of function
 *   is less than the switching cost. when a function is Macro or inline, the callee is replaced by the instruction code
 *   of function by compiler to save switching cost.
 *
 * Prefer inline function to function-like Macros because
 * 1- We gain the same efficiency (saving switching cost)
 * 2- Passing expression in function-like Macro leads to unpredictable behaviours
 */

#define MAX(a, b) a>b ? a:b

template<typename T>
T Max (T a, T b){
  return a>b ? a:b ;
};


int main() {

  printIt(ASPECT_RATIO);   /// ASPECT_RATIO is replaced with 1.777 in compilation time
  printIt(AspectRation); ///  AspectRation_ is initialized once in declaration point and it is used ( not replacement overhead)

  PrintString();  /// print const strings


  printIt(A::AspectRatio_); /// if A::AspectRatio_ is not defined in line 37, it cannot be complied

  printIt(MyData::X);
  printIt(MyData::Y);

  float a = 10;
  float b = 5;

  printIt(Max(a,b));
  printIt(MAX(++a,b)); // variable "a" is incremented twice!


  return 0;
}
