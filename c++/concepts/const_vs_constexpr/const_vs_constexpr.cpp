#include <iostream>

/**
 * Both PI1 and PI2 are constant, meaning you can not modify them. However only PI2 is a compile-time constant. 
 * It shall be initialized at compile time. PI1 may be initialized at compile time or run time.
 * Furthermore, only PI2 can be used in a context that requires a compile-time constant. For example:
 */

const     double PI1 = 3.141592653589793;
constexpr double PI2 = 3.141592653589793;

/*
Static assert is used to make assertions at compile time. When the static assertion fails, the program simply doesn't compile
*/


constexpr double PI3 = PI1;  // error


constexpr double PI3 = PI2;  // ok


static_assert(PI1 == 3.141592653589793, "");  // error



static_assert(PI2 == 3.141592653589793, "");  // ok



class A{

public:

// error: non-integral types cannot use in-class initialization with const
static const double x = 5.5;

};


class A{

public:

// integral types can use in-class initialization with const
static const int x = 5;

};

class A{

public:

// non-integral types can use in-class initialization with constexpr
static constexpr double x = 5.5;

};

/**
 * const: (variable's value should not be modified after initialization)
 *  - Used to create constant variables or pointers to constants. (declares sth that cannot be changed after initialization)
    - The value of a const variable is known and evaluated at runtime.
    - Can be applied to variables, pointers, references, member functions and function parameters.
    - Can't be used for compile-time computations.
    - Is useful for expressing intent and preventing accidental modifications.**/

    //1. Prevent accidental modifications
    void printValue(const int x) {
    // x = 10; // ❌ Error: can't modify
    std::cout << x << '\n';
    }

    //2. Read-only global or local variable
    const double pi = 3.14159;

    //3. Pointer immutability
    int value = 42;
    const int* ptr = &value;

/**
  constexpr: (to declare that an expression or a function can be evaluated at compile time, allowing for compile-time computations and optimizations)

    - Used to create variables, functions, and expressions that are evaluated at compile time.
    - The value of a constexpr variable or expression is evaluated at compile time.
    - Can be used for defining compile-time constants and functions.
    - Is evaluated by the compiler during compilation.
    - Useful for enabling compile-time computations and improving performance.
 *
 * both const and constexpr variables must be initialized at declaration time.
 */

  /**
   * Feature                   | const                     | constexpr
    Known when?                | Runtime                   | Compile-time
    Modifiable?                | No                        | No
    Can be used as array size? | ❌ No (in some contexts)  | ✅ Yes
    Guarantees evaluation?     | ❌ Maybe runtime          | ✅ Must be compile-time
  */

  //1. Compile-time math or logic
  constexpr int square(int x) {
    return x * x;
  }

  int arr[square(4)]; // ✅ Compile-time size

  //2. Constant expression variables
  constexpr double gravity = 9.8;

  //3. Constant constructors 
  struct Vec2 {
    double x, y;
    constexpr Vec2(double x_, double y_) : x(x_), y(y_) {}
};

constexpr Vec2 v(1.0, 2.0);

constexpr int dotOp(Vec2 v1, Vect v2)
{
  return v1.x * v2.x + v1.y + v2.y;
}

int arr1[dotOp(Vec2(2,3), Vec2(5,6))];









